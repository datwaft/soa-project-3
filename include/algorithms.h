#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "deps/kvec.h"
#include "step.h"
#include "task.h"

typedef kvec_t(step_t) step_vec_t;

typedef struct steps_st {
  step_vec_t steps;
  bool ended_early;
} steps_t;

double calc_µ(task_t const tasks[], size_t tasks_size);

double calc_U_RM(size_t size);

// WARNING: the return value must be freed by the caller.
steps_t steps_RM(task_t const tasks[], size_t tasks_size);

// WARNING: the return value must be freed by the caller.
steps_t steps_EDF(task_t const tasks[], size_t tasks_size);

// WARNING: the return value must be freed by the caller.
steps_t steps_LLF(task_t const tasks[], size_t tasks_size);

#endif /* !ALGORITHMS_H */
