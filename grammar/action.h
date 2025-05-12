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
 * Project Name: liu-cc
 * Module Name: grammar
 * Filename: action.h
 * Creator: Yaokai Liu
 * Create Date: 2025-05-12
 * Copyright (c) 2025 Yaokai Liu. All rights reserved.
 **/

#ifndef LIU_CC_ACTION_H
#define LIU_CC_ACTION_H

#include <stdint.h>
enum GRAMMAR_ACTION_ENUM : uint8_t {
  Preprocess_action_stack = 1,
  Preprocess_action_reduce = 2,
  Parse_action_stack = Preprocess_action_stack,
  Parse_action_reduce = Preprocess_action_reduce,
};

struct grammar_action {
  const uint8_t type; // target type <enum TOKEN_TYPE_ENUM>
  const uint8_t action: 4; // <enum GRAMMAR_ACTION_ENUM>
  const uint8_t count: 4; // product rule argument count
  const uint16_t offset; // product rule id or next state
};

#endif //LIU_CC_ACTION_H
