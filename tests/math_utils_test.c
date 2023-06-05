#include <criterion/criterion.h>

#include "math_utils.h"

// =====================
// least_common_multiple
// =====================

Test(least_common_multiple, example1) {
  int64_t result = least_common_multiple(72, 120);

  cr_expect_eq(result, 360);
}

// ===============================
// least_common_multiple_for_array
// ===============================

Test(least_common_multiple_for_array, two_elements) {
  int64_t array[] = {72, 120};
  size_t array_size = 2;

  int64_t result = least_common_multiple_for_array(array, array_size);

  cr_expect_eq(result, 360);
}

Test(least_common_multiple_for_array, three_elements) {
  int64_t array[] = {100, 23, 98};
  size_t array_size = 3;

  int64_t result = least_common_multiple_for_array(array, array_size);

  cr_expect_eq(result, 112700);
}
