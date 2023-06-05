#include "math_utils.h"

#include <stdbool.h>

int64_t least_common_multiple(int64_t a, int64_t b) {
  int64_t i = (a > b) ? a : b;
  while (true) {
    if ((i % a == 0) && (i % b == 0))
      break;
    i += 1;
  }
  return i;
}

int64_t least_common_multiple_for_array(int64_t const array[],
                                        size_t array_size) {
  if (array_size < 2) {
    return -1;
  } else if (array_size == 2) {
    return least_common_multiple(array[0], array[1]);
  } else {
    return least_common_multiple(
        array[0], least_common_multiple_for_array(array + 1, array_size - 1));
  }
}
