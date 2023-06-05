#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <stddef.h>
#include <stdint.h>

int64_t least_common_multiple(int64_t a, int64_t b);

int64_t least_common_multiple_for_array(int64_t const array[],
                                        size_t array_size);

#endif /* !MATH_UTILS_H */
