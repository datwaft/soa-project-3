#include <stdio.h>
#include <stdlib.h>

#include "step.h"
#include "table_str.h"
#include "task.h"

int main(int argc, char **argv) {
  step_t expected[] = {
      {.task_id = 1, .duration = {.start = 0, .finish = 2}},
      {.task_id = 2, .duration = {.start = 2, .finish = 4}},
      {.task_id = 3, .duration = {.start = 4, .finish = 6}},
      {.task_id = 3, .duration = {.start = 6, .finish = 7}},
      {.task_id = 1, .duration = {.start = 7, .finish = 8}},
      {.task_id = 1, .duration = {.start = 8, .finish = 9}},
      {.task_id = 2, .duration = {.start = 9, .finish = 10}},
      {.task_id = 2, .duration = {.start = 10, .finish = 11}},
      {.task_id = 3, .duration = {.start = 11, .finish = 12}},
      {.task_id = 1, .duration = {.start = 12, .finish = 14}},
      {.task_id = 3, .duration = {.start = 14, .finish = 16}},
      {.task_id = 2, .duration = {.start = 16, .finish = 18}},
      {.task_id = 1, .duration = {.start = 18, .finish = 20}},
      {.task_id = 3, .duration = {.start = 20, .finish = 23}},
  };
  for (int i = 0; i < 14; ++i) {
    char buffer[STEP_SERIALIZE_LENGTH + 1];
    step_serialize(buffer, &expected[i]);
    printf("%s\n", buffer);
  }

  return EXIT_SUCCESS;
}
