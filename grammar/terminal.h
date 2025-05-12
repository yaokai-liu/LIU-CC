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
 * Filename: terminal.h
 * Creator: Yaokai Liu
 * Create Date: 2025-05-03
 * Copyright (c) 2025 Yaokai Liu. All rights reserved.
 **/

#ifndef LIU_CC_TERMINAL_H
#define LIU_CC_TERMINAL_H


#include <stdint.h>
#include "char_t.h"

/// location of a Token in a file
typedef struct TokenLoc {
  /// Offset in src string
  uint32_t offset;
  /// line number in src file
  uint32_t lineno;
  /// column offset in the line in src file
  uint32_t column;
  /// length of the token (size in bytes)
  uint32_t length;
} TokenLoc;

typedef struct Terminal {
  TokenLoc location;
  /// Token Type
  uint32_t type;
  /// Version in standard: [0] enable; [1] deprecated.
  uint16_t mark[2];
  /// value of the token
  void *value;
} Terminal, Token;

typedef char_t Identifier;

#endif //LIU_CC_TERMINAL_H
