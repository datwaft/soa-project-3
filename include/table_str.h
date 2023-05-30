#ifndef TABLE_STR_H
#define TABLE_STR_H

#include <stddef.h>

#include "task.h"

#define TASK_TBL_ROW_LENGTH 46

// `buffer` must be at least `TASK_TBL_ROW_LENGTH * (tasks_length + 4)`
// characters wide
void tasks_to_tbl(char buffer[], task_t const tasks[], size_t tasks_length);

#endif /* !TABLE_STR_H */
