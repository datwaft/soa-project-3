#include <criterion/criterion.h>

#include "task.h"

// ========
// task_new
// ========

Test(task_new, valid) {
  task_t task = task_new(1, 10);

  cr_expect_eq(task.execution, 1);
  cr_expect_eq(task.period, 10);
}

// ==========
// task_valid
// ==========

Test(task_valid, valid) {
  task_t task = task_new(1, 10);

  cr_expect(task_valid(&task));
}

Test(task_valid, invalid_by_id) {
  task_t task = task_new(1, 10);
  task.id = -1;

  cr_expect_not(task_valid(&task));
}

Test(task_valid, invalid_by_execution) {
  task_t task = task_new(-1, 10);

  cr_expect_not(task_valid(&task));
}

Test(task_valid, invalid_by_period) {
  task_t task = task_new(1, -10);

  cr_expect_not(task_valid(&task));
}

Test(task_valid, invalid_by_execution_greater_than_period) {
  task_t task = task_new(10, 1);

  cr_expect_not(task_valid(&task));
}
