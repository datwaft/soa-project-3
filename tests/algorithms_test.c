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

  steps_t result = steps_RM(tasks, tasks_size);
  step_vec_t steps = result.steps;
  bool ended_early = result.ended_early;

  cr_expect_arr_eq_cmp(steps.a, expected, kv_size(steps), step_cmp);
  cr_expect_not(ended_early);
}

Test(steps_RM, example_2) {
  step_t expected[] = {
      {.task_id = 1, .duration = {.start = 0, .finish = 1}},
      {.task_id = 2, .duration = {.start = 1, .finish = 2}},
      {.task_id = 3, .duration = {.start = 2, .finish = 3}},
  };

  task_t tasks[] = {
      task_new(1, 3),
      task_new(1, 3),
      task_new(1, 3),
  };
  size_t tasks_size = 3;

  steps_t result = steps_RM(tasks, tasks_size);
  step_vec_t steps = result.steps;
  bool ended_early = result.ended_early;

  cr_expect_arr_eq_cmp(steps.a, expected, kv_size(steps), step_cmp);
  cr_expect_not(ended_early);
}

Test(steps_RM, example_3) {
  step_t expected[] = {
      {.task_id = 2, .duration = {.start = 0, .finish = 1}},
      {.task_id = 3, .duration = {.start = 1, .finish = 3}},
      {.task_id = 2, .duration = {.start = 3, .finish = 4}},
      {.task_id = 1, .duration = {.start = 4, .finish = 6}},
      {.task_id = 2, .duration = {.start = 6, .finish = 7}},
      {.task_id = 3, .duration = {.start = 7, .finish = 9}},
      {.task_id = 2, .duration = {.start = 9, .finish = 10}},
      {.task_id = 1, .duration = {.start = 10, .finish = 12}},
  };

  task_t tasks[] = {
      task_new(4, 12),
      task_new(1, 3),
      task_new(2, 6),
  };
  size_t tasks_size = 3;

  steps_t result = steps_RM(tasks, tasks_size);
  step_vec_t steps = result.steps;
  bool ended_early = result.ended_early;

  cr_expect_arr_eq_cmp(steps.a, expected, kv_size(steps), step_cmp);
  cr_expect_not(ended_early);
}

Test(steps_RM, example_4) {
  step_t expected[] = {
      {.task_id = 1, .duration = {.start = 0, .finish = 1}},
      {.task_id = 2, .duration = {.start = 1, .finish = 3}},
      {.task_id = 3, .duration = {.start = 3, .finish = 6}},
      {.task_id = 1, .duration = {.start = 6, .finish = 7}},
      {.task_id = 3, .duration = {.start = 7, .finish = 9}},
      {.task_id = 2, .duration = {.start = 9, .finish = 11}},
      {.task_id = 3, .duration = {.start = 11, .finish = 12}},
      {.task_id = 1, .duration = {.start = 12, .finish = 13}},
  };

  task_t tasks[] = {
      task_new(1, 6),
      task_new(2, 9),
      task_new(6, 18),
  };
  size_t tasks_size = 3;

  steps_t result = steps_RM(tasks, tasks_size);
  step_vec_t steps = result.steps;
  bool ended_early = result.ended_early;

  cr_expect_arr_eq_cmp(steps.a, expected, kv_size(steps), step_cmp);
  cr_expect_not(ended_early);
}

Test(steps_RM, example_5) {
  step_t expected[] = {
      {.task_id = 1, .duration = {.start = 0, .finish = 3}},
      {.task_id = 2, .duration = {.start = 3, .finish = 6}},
      {.task_id = 1, .duration = {.start = 6, .finish = 9}},
  };

  task_t tasks[] = {
      task_new(3, 6),
      task_new(4, 9),
  };
  size_t tasks_size = 2;

  steps_t result = steps_RM(tasks, tasks_size);
  step_vec_t steps = result.steps;
  bool ended_early = result.ended_early;

  cr_expect_arr_eq_cmp(steps.a, expected, kv_size(steps), step_cmp);
  cr_expect(ended_early);
}

Test(steps_RM, example_6) {
  step_t expected[] = {
      {.task_id = 1, .duration = {.start = 0, .finish = 10}},
      {.task_id = 2, .duration = {.start = 10, .finish = 20}},
      {.task_id = 3, .duration = {.start = 20, .finish = 30}},
      {.task_id = 1, .duration = {.start = 30, .finish = 40}},
      {.task_id = 2, .duration = {.start = 40, .finish = 50}},
      {.task_id = 3, .duration = {.start = 50, .finish = 52}},
      {.task_id = 3, .duration = {.start = 52, .finish = 60}},
      {.task_id = 1, .duration = {.start = 60, .finish = 70}},
      {.task_id = 3, .duration = {.start = 70, .finish = 74}},
      {.task_id = 2, .duration = {.start = 80, .finish = 90}},
  };

  task_t tasks[] = {
      task_new(10, 30),
      task_new(10, 40),
      task_new(12, 52),
  };
  size_t tasks_size = 3;

  steps_t result = steps_RM(tasks, tasks_size);
  step_vec_t steps = result.steps;
  bool ended_early = result.ended_early;

  cr_expect_arr_eq_cmp(steps.a, expected, 10, step_cmp);
  cr_expect(ended_early);
}

// =========
// steps_EDF
// =========

Test(steps_EDF, example_1) {
  step_t expected[] = {
      {.task_id = 1, .duration = {.start = 0, .finish = 1}},
      {.task_id = 2, .duration = {.start = 1, .finish = 3}},
      {.task_id = 3, .duration = {.start = 3, .finish = 5}},
      {.task_id = 1, .duration = {.start = 5, .finish = 6}},
      {.task_id = 3, .duration = {.start = 6, .finish = 8}},
      {.task_id = 2, .duration = {.start = 8, .finish = 10}},
      {.task_id = 1, .duration = {.start = 10, .finish = 11}},
      {.task_id = 3, .duration = {.start = 11, .finish = 13}},
      {.task_id = 1, .duration = {.start = 15, .finish = 16}},
      {.task_id = 2, .duration = {.start = 16, .finish = 18}},
      {.task_id = 3, .duration = {.start = 19, .finish = 20}},
      {.task_id = 1, .duration = {.start = 20, .finish = 21}},
      {.task_id = 3, .duration = {.start = 21, .finish = 24}},
      {.task_id = 2, .duration = {.start = 24, .finish = 25}},
  };

  task_t tasks[] = {
      task_new(1, 5),
      task_new(2, 8),
      task_new(6, 19),
  };
  size_t tasks_size = 3;

  steps_t result = steps_EDF(tasks, tasks_size);
  step_vec_t steps = result.steps;
  bool ended_early = result.ended_early;

  cr_expect_arr_eq_cmp(steps.a, expected, 14, step_cmp);
  cr_expect_not(ended_early);
}
