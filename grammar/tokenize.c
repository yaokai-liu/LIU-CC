/* License
 *
 * ${PROJ_DESCRIPTION}
 * Copyright (C) 2025 Yaokai Liu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 *
 * Project Name: LIU-CC
 * Module Name: grammar
 * Filename: tokenize.c
 * Creator: Yaokai Liu
 * Create Date: 2025-05-03
 * Copyright (c) 2025 Yaokai Liu. All rights reserved.
 **/

#include "tokenize.h"

#include "terminal.h"
#include "allocator.h"

#define lenof(str_literal) ((sizeof str_literal) - 1)
#define max(a, b)          ((a) > (b) ? (a) : (b))
#define min(a, b)          ((a) < (b) ? (a) : (b))

#define startswithDigital(pText) ('0' <= (pText)[0] && (pText)[0] <= '9')
#define startswithLetter(pText) (('a' <= (pText)[0] && (pText)[0] <= 'z') || ('A' <= (pText)[0] && (pText)[0] <= 'Z'))

#define fn_try_keyword(_kw, _type)                                                           \
  inline uint32_t try_keyword_##_kw(                                                         \
      const char_t * const input, Terminal * const result, const Allocator * const allocator \
  ) {                                                                                        \
    const char_t pattern[] = string_t(#_kw);                                                 \
    for (uint32_t i = 2; i < sizeof(pattern) - 1; i++) {                                     \
      if (input[i - 2] != pattern[i]) { goto __failed_kw_##_kw; }                            \
    }                                                                                        \
    const char_t * const tail = &input[sizeof(pattern) - 3];                                 \
    if (startswithLetter(tail) || *tail == '_') { goto __failed_kw_##_kw; }                  \
    result->type = enum_##_type;                                                             \
    result->value = nullptr;                                                                 \
    result->length = lenof(#_kw);                                                            \
    return lenof(#_kw);                                                                      \
    __failed_kw_##_kw : return t_IDENTIFIER(input - 2, result, allocator);                   \
  }
#define fn_try_keyword_val(_kw, _type, val)                                                  \
  inline uint32_t try_keyword_##_kw(                                                         \
      const char_t * const input, Terminal * const result, const Allocator * const allocator \
  ) {                                                                                        \
    const char_t pattern[] = string_t(#_kw);                                                 \
    for (uint32_t i = 2; i < sizeof(pattern) - 1; i++) {                                     \
      if (input[i - 2] != pattern[i]) { goto __failed_kw_##_kw; }                            \
    }                                                                                        \
    const char_t * const tail = &input[sizeof(pattern) - 3];                                 \
    if (startswithLetter(tail) || *tail == '_') { goto __failed_kw_##_kw; }                  \
    result->type = enum_##_type;                                                             \
    result->value = (void *) val;                                                            \
    result->length = lenof(#_kw);                                                            \
    return lenof(#_kw);                                                                      \
    __failed_kw_##_kw : return t_IDENTIFIER(input - 2, result, allocator);                   \
  }


uint32_t t_IDENTIFIER(const char_t *input, Terminal *result, const Allocator *allocator);
uint32_t t_NUMBER_adic16(const char_t *input, Terminal *result, const Allocator *allocator);
uint32_t t_NUMBER_adic10(const char_t *input, Terminal *result, const Allocator *allocator);
uint32_t t_NUMBER_adic8(const char_t *input, Terminal *result, const Allocator *allocator);
uint32_t t_NUMBER_adic2(const char_t *input, Terminal *result, const Allocator *allocator);

uint32_t pass_whitespace(const char *input);


inline uint32_t t_NUMBER_adic16(
    const char_t * const input, Terminal * const result,
    const Allocator * const
) {
  const char_t *pText = input;
  uint64_t value = 0LL;
  while (true) {
    if ('0' <= *pText && *pText <= '9') {
      value = (value << 4) + (*pText++ - '0');
    } else if ('a' <= *pText && *pText <= 'f') {
      value = (value << 4) + (*pText++ - 'a' + 0xa);  // NOLINT(*-magic-numbers)
    } else if ('A' <= *pText && *pText <= 'F') {
      value = (value << 4) + (*pText++ - 'A' + 0xA);  // NOLINT(*-magic-numbers)
    } else if (('g' <= *pText && *pText <= 'z') || ('G' <= *pText && *pText <= 'Z')
               || ('_' == *pText)) {
      result->location.length = pText - input;
      return 0;
    } else if (*pText == '\'') {
      pText++;
    } else {
      break;
    }
  }
  result->type = enum_NUMBER;
  result->value = (void *) value;
  result->location.length = pText - input;
  return result->location.length;
}

inline uint32_t t_NUMBER_adic10(
    const char_t * const input, Terminal * const result,
    const Allocator * const
) {
  const char_t *pText = input;
  uint64_t value = 0;
  while (true) {
    if (startswithDigital(pText)) {
      value = (value * 10) + (*pText++ - '0');  // NOLINT(*-magic-numbers)
      continue;
    }
    if (startswithLetter(pText)) {
      result->location.length = pText - input;
      return 0;
    }
    if (*pText == '\'') {
      pText++;
    } else {
      break;
    }
  }
  result->type = enum_NUMBER;
  result->value = (void *) value;
  result->location.length = pText - input;
  return result->location.length;
}

inline uint32_t t_NUMBER_adic8(
    const char_t * const input, Terminal * const result,
    const Allocator * const
) {
  const char_t *pText = input;
  uint64_t value = 0;
  while (true) {
    if ('0' <= *pText && *pText <= '7') {
      value = (value << 3) + (*pText++ - '0');
      continue;
    }
    if (('8' == *pText) || ('9' == *pText) || startswithLetter(pText)) {
      result->location.length = pText - input;
      return 0;
    }
    if (*pText == '\'') {
      pText++;
    } else {
      break;
    }
  }
  result->type = enum_NUMBER;
  result->value = (void *) value;
  result->location.length = pText - input;
  return result->location.length;
}

inline uint32_t t_NUMBER_adic2(
    const char_t * const input, Terminal * const result,
    const Allocator * const
) {
  const char_t *pText = input;
  uint64_t value = 0;
  while (true) {
    if ('0' == *pText || *pText == '1') {
      value = (value << 1) + (*pText++ - '0');
      continue;
    }
    if (('2' <= *pText && *pText <= '9') || startswithLetter(pText)) {
      result->location.length = pText - input;
      return 0;
    }
    if (*pText == '\'') {
      pText++;
    } else {
      break;
    }
  }
  result->type = enum_NUMBER;
  result->value = (void *) value;
  result->location.length = pText - input;
  return result->location.length;
}


