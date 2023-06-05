#include "step.h"

int step_cmp(step_t const *step_1, step_t const *step_2) {
  if (step_1->task_id == step_2->task_id &&
      step_1->duration.start == step_2->duration.start &&
      step_1->duration.finish == step_2->duration.finish)
    return 0;
  return -1;
}
