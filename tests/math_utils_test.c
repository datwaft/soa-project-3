#include <criterion/criterion.h>

#include "math_utils.h"

// =====================
// least_common_multiple
// =====================

Test(least_common_multiple, example1) {
  int64_t result = least_common_multiple(72, 120);
  cr_expect_eq(result, 360);
}
