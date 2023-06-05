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
