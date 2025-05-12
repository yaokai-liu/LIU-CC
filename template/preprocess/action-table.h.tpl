${license}

#ifndef LIU_CC_PREPROCESS_ACTION_TABLE_GEN_H
#define LIU_CC_PREPROCESS_ACTION_TABLE_GEN_H

#include <stdint.h>

enum PREPROCESS_STATE_ENUM {
  ${state_enum}
};

const struct grammar_action *getPreprocessParseAction(uint32_t _state, uint32_t ahead);

int32_t preprocessParseJumpState(uint32_t _state, uint32_t current);

uint32_t getPreprocessParseStateCurrentTokenType(int32_t state);

uint32_t getPreprocessStateExpectedTokenType(int32_t _state, uint32_t *token_types);

#endif  // LIU_CC_PREPROCESS_ACTION_TABLE_GEN_H