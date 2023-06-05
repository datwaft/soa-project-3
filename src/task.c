#include "task.h"
#include "deps/hashmap_base.h"

static int64_t counter = 0;

task_t task_new(int64_t execution, int64_t period) {
  counter += 1;
  return (task_t){.id = counter, .execution = execution, .period = period};
}

bool task_valid(task_t const *task) {
  return (task->id >= 0) && (task->execution >= 0) && (task->period >= 0) &&
         (task->period >= task->execution);
}

int task_cmp(task_t const *task_1, task_t const *task_2) {
  if (task_1->id == task_2->id && task_1->execution == task_2->execution &&
      task_1->period == task_2->period)
    return 0;
  return -1;
}

size_t task_hash(task_t const *task) {
  return hashmap_hash_default(task, sizeof(task_t));
}
