#include "table_str.h"

#include <stdio.h>

void tasks_to_tbl(char buffer[], task_t const tasks[], size_t tasks_length) {
  buffer += sprintf(buffer, "+------+----+----+\n");
  buffer += sprintf(buffer, "| "
                            "\x1b[1m"
                            "Task"
                            "\x1b[22m"
                            " | "
                            "\x1b[1m"
                            "cᵢ"
                            "\x1b[22m"
                            " | "
                            "\x1b[1m"
                            "pᵢ"
                            "\x1b[22m"
                            " |"
                            "\n");
  buffer += sprintf(buffer, "+------+----+----+\n");
  for (size_t i = 0; i < tasks_length; ++i) {
    buffer += sprintf(buffer,
                      "| "
                      "\x1b[1m"
                      "%4lld"
                      "\x1b[22m"
                      " | %2lld | %2lld |"
                      "\n",
                      tasks[i].id, tasks[i].execution, tasks[i].period);
  }
  buffer += sprintf(buffer, "+------+----+----+"
                            "\n");
}
