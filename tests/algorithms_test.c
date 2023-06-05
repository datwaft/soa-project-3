#include <criterion/criterion.h>
#include <stddef.h>

#include "algorithms.h"
#include "step.h"
#include "task.h"

// ======
// calc_µ
// ======

Test(calc_µ, example_1) {
  task_t const tasks[] = {
      task_new(1, 8),
      task_new(2, 5),
      task_new(2, 10),
  };

  double µ = calc_µ(tasks, 3);

  cr_expect_float_eq(µ, 0.725, 1e-3);
}

Test(calc_µ, example_2) {
  task_t const tasks[] = {
      task_new(3, 10),   task_new(1, 100), task_new(7, 35),
      task_new(45, 500), task_new(2, 8),
  };

  double µ = calc_µ(tasks, 5);

  cr_expect_float_eq(µ, 0.85, 1e-3);
}

Test(calc_µ, example_3) {
  task_t const tasks[] = {
      task_new(3, 6),
      task_new(4, 9),
  };

  double µ = calc_µ(tasks, 2);

  cr_expect_float_eq(µ, 0.944, 1e-3);
}

// =========
// calc_U_RM
// =========

Test(calc_U_RM, example_1) {
  size_t size = 3;

  double U = calc_U_RM(size);

  cr_expect_float_eq(U, 0.7797, 1e-4);
}

Test(calc_U_RM, example_2) {
  size_t size = 5;

  double U = calc_U_RM(size);

  cr_expect_float_eq(U, 0.7435, 1e-4);
}

// ========
// steps_RM
// ========

Test(steps_RM, example_1) {
  step_t expected[] = {
      {.task_id = 1, .duration = {.start = 0, .finish = 1}},
      {.task_id = 2, .duration = {.start = 1, .finish = 2}},
      {.task_id = 1, .duration = {.start = 2, .finish = 3}},
      {.task_id = 2, .duration = {.start = 3, .finish = 4}},
      {.task_id = 1, .duration = {.start = 4, .finish = 5}},
      {.task_id = 3, .duration = {.start = 5, .finish = 6}},
  };

  task_t tasks[] = {
      task_new(1, 2),
      task_new(1, 3),
      task_new(1, 6),
  };
  size_t tasks_size = 3;

  step_vec_t result = steps_RM(tasks, tasks_size);

  cr_expect_eq(kv_size(result), 6);
  cr_expect_arr_eq_cmp(result.a, expected, kv_size(result), step_cmp);
}
