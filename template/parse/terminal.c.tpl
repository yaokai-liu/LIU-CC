${license}

#include "terminal.h"
#include "generated/tokens.gen.h"
const char_t PARSE_TERMINALS[] = {
  ${terminals}
};

const char_t * PARSE_TERMINAL_STRINGS[] = {
  ${strings}
};

const uint32_t PARSE_TERMINAL_STRING_LENS[] = {
  ${string_lens}
};

const int32_t N_PARSE_TERMINAL = sizeof(PARSE_TERMINALS);