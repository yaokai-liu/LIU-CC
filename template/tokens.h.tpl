${license}

#ifndef LIU_CC_TOKENS_H
#define LIU_CC_TOKENS_H

#include "char_t.h"
#include <stdint.h>

enum TOKEN_TYPE_ENUM: uint32_t {
  enum_BAD_TOKEN = 0,

  // real token's type always increase from 1
  ${enums},

  // extend tokens
  enum_PLACE_HOLDER,

  // end of tokens
  MAX_TOTAL_TOKEN,
};

extern const char_t *TOKEN_NAMES[];

#endif  // LIU_CC_TOKENS_H
