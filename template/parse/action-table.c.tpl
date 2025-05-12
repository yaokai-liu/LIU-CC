${license}

#include "action.h"
#include "generated/tokens.gen.h"
#include "action-table.gen.h"
#include "rules.gen.h"

struct state {
  const uint16_t ndx_base;
  const uint16_t goto_base;
  const uint16_t token_base;
  const uint16_t n_tokens;
};
struct unit {
  uint8_t type;
  uint8_t offset;
};

const struct grammar_action PARSE_ACTIONS[];
const uint16_t PARSE_JUMPS[];
const struct unit PARSE_UNITS[];
const struct state PARSE_STATES[];
const uint32_t PARSE_CURRENT_TOKENS[];

const struct unit *getParseUnit(const struct state *state, uint32_t look);

const struct grammar_action PARSE_ACTIONS[] = {
  ${actions}
};

const uint16_t PARSE_JUMPS[] = {
  ${jumps}
};

const struct unit PARSE_UNITS[] = {
  ${units}
};

const struct state PARSE_STATES[] = {
  ${states}
};

const uint32_t PARSE_CURRENT_TOKENS[] = {
  ${currents}
};

inline const struct unit *getParseUnit(const struct state *state, uint32_t look) {
  const struct unit *unit, *base = &PARSE_UNITS[state->token_base];
  int32_t left = 0, right = state->n_tokens - 1;
  int32_t u_idx = (left + right) / 2;
  unit = &base[u_idx];
  while (unit->type != look && left < right) {
    if (unit->type < look) {
      left = u_idx + 1;
    } else {
      right = u_idx - 1;
    }
    u_idx = (left + right) / 2;
    unit = &base[u_idx];
  }
  if (unit->type != look) { return nullptr; }
  return unit;
}


inline const struct grammar_action *getParseAction(uint32_t _state, uint32_t ahead) {
    const struct state *state = &PARSE_STATES[_state];
    const struct unit *unit = getParseUnit(state, ahead);
    if (!unit) { return nullptr; }
    const struct grammar_action *act = &PARSE_ACTIONS[state->ndx_base + unit->offset];
    return act;
}

inline int32_t parseJumpState(uint32_t _state, uint32_t current) {
    const struct state *state = &PARSE_STATES[_state];
    const struct unit *unit = getParseUnit(state, current);
    if (!unit) { return -1; }
    return PARSE_JUMPS[state->goto_base + unit->offset];
}

inline uint32_t getParseStateCurrentTokenType(int32_t _state) {
  return PARSE_CURRENT_TOKENS[_state];
}

inline uint32_t getParseStateExpectedTokenType(int32_t _state, uint32_t *token_types) {
  const struct state *state = &PARSE_STATES[_state];
  const struct unit *base = &PARSE_UNITS[state->token_base];
  if (token_types) {
    for (uint32_t i = 0; i < state->n_tokens; i++) {
      token_types[i] = base[i].type;
    }
  }
  return state->n_tokens;
}
