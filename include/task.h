#ifndef TASK_H
#define TASK_H

#include <stdbool.h>
#include <stdint.h>

typedef struct task_st {
  int64_t id;
  int64_t execution;
  int64_t period;
} task_t;

task_t task_new(int64_t execution, int64_t period);

bool task_valid(task_t const *task);

#endif // !TASK_H
