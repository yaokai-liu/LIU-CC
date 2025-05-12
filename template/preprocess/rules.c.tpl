${license}

#include "generated/preprocess/rules.gen.h"

typedef void *fn_preprocess_reduce(Token argv[], PreprocessContext *, const Allocator *);

fn_reduce * const PREPROCESS_PRODUCTS[] = {
  ${assign_reduces}
};
