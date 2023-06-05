#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <stddef.h>
#include <stdint.h>

#include "deps/kvec.h"
#include "step.h"
#include "task.h"

typedef kvec_t(step_t) step_vec_t;

double calc_µ(task_t const tasks[], size_t tasks_size);

double calc_U_RM(size_t size);

// WARNING: the return value must be freed by the caller.
step_vec_t steps_RM(task_t const tasks[], size_t tasks_size);

#endif /* !ALGORITHMS_H */
