${license}

#include "generated/parse/rules.gen.h"

typedef void *fn_parse_reduce(Token argv[], ParseContext *, const Allocator *);

fn_reduce * const PARSE_PRODUCTS[] = {
  ${assign_reduces}
};
