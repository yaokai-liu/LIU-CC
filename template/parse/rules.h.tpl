${license}

#ifndef PARSE_REDUCES_H
#define PARSE_REDUCES_H

#include "parse/target.h"
#include "parse/context.h"

typedef void *fn_reduce(Token argv[], ParseContext *, const Allocator *);

enum PARSE_PRODUCT_RULE_ENUM {
  ${enum_reduces}
};

${reduces}

#endif  // PARSE_REDUCES_H
