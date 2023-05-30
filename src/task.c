#include "task.h"

static int64_t counter = 0;

task_t task_new(int64_t execution, int64_t period) {
  counter += 1;
  return (task_t){.id = counter, .execution = execution, .period = period};
}

bool task_valid(task_t const *task) {
  return (task->id >= 0) && (task->execution >= 0) && (task->period >= 0) &&
         (task->period >= task->execution);
}
