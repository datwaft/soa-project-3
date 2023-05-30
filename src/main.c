#include <stdio.h>
#include <stdlib.h>

#include "table_str.h"
#include "task.h"

int main(int argc, char **argv) {
  task_t const tasks[] = {
      task_new(1, 8),
      task_new(2, 5),
      task_new(3, 10),
  };

  char buffer[TASK_TBL_ROW_LENGTH * (3 + 4)];
  tasks_to_tbl(buffer, tasks, 3);
  puts(buffer);

  return EXIT_SUCCESS;
}
