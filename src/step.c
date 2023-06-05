#include "step.h"
#include <stdio.h>

int step_cmp(step_t const *step_1, step_t const *step_2) {
  if (step_1->task_id == step_2->task_id &&
      step_1->duration.start == step_2->duration.start &&
      step_1->duration.finish == step_2->duration.finish)
    return 0;
  return -1;
}

void step_serialize(char buffer[], step_t const *step) {
  sprintf(buffer,
          "{ "
          "\x1b[1m"
          "task_id"
          "\x1b[22m"
          ": "
          "\x1b[34m"
          "%lld"
          "\x1b[39m"
          ", "
          "\x1b[1m"
          "start"
          "\x1b[22m"
          ": "
          "\x1b[32m"
          "%lld"
          "\x1b[39m"
          ", "
          "\x1b[1m"
          "finish"
          "\x1b[22m"
          ": "
          "\x1b[31m"
          "%lld"
          "\x1b[39m"
          " }",
          step->task_id, step->duration.start, step->duration.finish);
}
