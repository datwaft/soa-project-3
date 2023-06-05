#include "algorithms.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "deps/hashmap.h"
#include "deps/kvec.h"
#include "math_utils.h"
#include "task.h"

double calc_µ(task_t const tasks[], size_t tasks_size) {
  double sum = 0;
  for (size_t i = 0; i < tasks_size; ++i) {
    sum += (double)tasks[i].execution / (double)tasks[i].period;
  }
  return sum;
}

double calc_U_RM(size_t size) { return size * (pow(2.0, 1.0 / size) - 1.0); }

steps_t steps_RM(task_t const tasks[], size_t tasks_size) {
  task_t const *task; // Used for iteration

  HASHMAP(task_t, void) ready_queue;
  hashmap_init(&ready_queue, task_hash, task_cmp);

  int64_t execution_time[tasks_size];
  for (size_t i = 0; i < tasks_size; i++) {
    execution_time[i] = 0;
  }

  step_vec_t steps;
  kv_init(steps);

  // We need to calculate the tasks' period LCM
  int64_t periods[tasks_size];
  for (size_t i = 0; i < tasks_size; ++i) {
    periods[i] = tasks[i].period;
  }
  int64_t periods_LCM = least_common_multiple_for_array(periods, tasks_size);

  task_t const *current_task = NULL;
  step_t current_step;
  bool has_ready_queue_changed = false;
  for (int64_t tick = 0; tick <= periods_LCM; ++tick) {
    int64_t current_task_last_executed_time =
        (current_task == NULL) ? 0 : execution_time[current_task->id - 1];

    // Check if any existing task is due
    hashmap_foreach_key(task, &ready_queue) {
      if (tick % task->period == 0) {
        current_step.duration.finish = tick;
        kv_push(step_t, steps, current_step);
        hashmap_cleanup(&ready_queue);
        return (steps_t){.steps = steps, .ended_early = true};
      }
    }
    // Check if current task is due
    if (current_task != NULL && tick % current_task->period == 0 &&
        current_task_last_executed_time != current_task->execution) {
      current_step.duration.finish = tick;
      kv_push(step_t, steps, current_step);
      hashmap_cleanup(&ready_queue);
      return (steps_t){.steps = steps, .ended_early = true};
    }
    // If current task has finished execution
    if (current_task != NULL &&
        current_task->execution == current_task_last_executed_time) {
      execution_time[current_task->id - 1] = 0;
      current_step.duration.finish = tick;
      kv_push(step_t, steps, current_step);
      current_task = NULL;
    }
    // Populate the ready queue
    for (size_t i = 0; i < tasks_size; ++i) {
      if (tick % tasks[i].period == 0) {
        hashmap_put(&ready_queue, &tasks[i], (void *)1);
        has_ready_queue_changed = true;
      }
    }
    // Select a new task from the ready queue if necessary
    if (current_task == NULL || has_ready_queue_changed) {
      task_t const *next_task = NULL;
      hashmap_foreach_key(task, &ready_queue) {
        if (next_task == NULL) {
          next_task = task;
        } else if (task->period < next_task->period) {
          next_task = task;
        } else if (task->period == next_task->period &&
                   task->id < next_task->id) {
          next_task = task;
        }
      }

      if (next_task != NULL) {
        if (current_task != NULL && current_task->id != next_task->id) {
          hashmap_put(&ready_queue, current_task, (void *)1);
          current_step.duration.finish = tick;
          kv_push(step_t, steps, current_step);
        }
        hashmap_remove(&ready_queue, next_task);
        current_task = next_task;
        current_step.task_id = current_task->id;
        current_step.duration.start = tick;
      }
    }
    has_ready_queue_changed = false;
    if (current_task != NULL) {
      execution_time[current_task->id - 1] += 1;
    }
  }
  hashmap_cleanup(&ready_queue);
  return (steps_t){.steps = steps, .ended_early = false};
}

steps_t steps_EDF(task_t const tasks[], size_t tasks_size) {
  task_t const *task; // Used for iteration

  HASHMAP(task_t, void) ready_queue;
  hashmap_init(&ready_queue, task_hash, task_cmp);

  int64_t execution_time[tasks_size];
  for (size_t i = 0; i < tasks_size; i++) {
    execution_time[i] = 0;
  }

  step_vec_t steps;
  kv_init(steps);

  // We need to calculate the tasks' period LCM
  int64_t periods[tasks_size];
  for (size_t i = 0; i < tasks_size; ++i) {
    periods[i] = tasks[i].period;
  }
  int64_t periods_LCM = least_common_multiple_for_array(periods, tasks_size);

  task_t const *current_task = NULL;
  step_t current_step;
  bool has_ready_queue_changed = false;
  for (int64_t tick = 0; tick <= periods_LCM; ++tick) {
    int64_t current_task_last_executed_time =
        (current_task == NULL) ? 0 : execution_time[current_task->id - 1];

    // Check if any existing task is due
    hashmap_foreach_key(task, &ready_queue) {
      if (tick % task->period == 0) {
        current_step.duration.finish = tick;
        kv_push(step_t, steps, current_step);
        hashmap_cleanup(&ready_queue);
        return (steps_t){.steps = steps, .ended_early = true};
      }
    }
    // Check if current task is due
    if (current_task != NULL && tick % current_task->period == 0 &&
        current_task_last_executed_time != current_task->execution) {
      current_step.duration.finish = tick;
      kv_push(step_t, steps, current_step);
      hashmap_cleanup(&ready_queue);
      return (steps_t){.steps = steps, .ended_early = true};
    }
    // If current task has finished execution
    if (current_task != NULL &&
        current_task->execution == current_task_last_executed_time) {
      execution_time[current_task->id - 1] = 0;
      current_step.duration.finish = tick;
      kv_push(step_t, steps, current_step);
      current_task = NULL;
    }
    // Populate the ready queue
    for (size_t i = 0; i < tasks_size; ++i) {
      if (tick % tasks[i].period == 0) {
        hashmap_put(&ready_queue, &tasks[i], (void *)1);
        has_ready_queue_changed = true;
      }
    }
    // Select a new task from the ready queue if necessary
    if (current_task == NULL || has_ready_queue_changed) {
      task_t const *next_task = NULL;
      hashmap_foreach_key(task, &ready_queue) {
        if (next_task == NULL) {
          next_task = task;
        } else if (((tick - (tick % task->period)) + task->period) <
                   ((tick - (tick % next_task->period)) + next_task->period)) {
          next_task = task;
        } else if (((tick - (tick % task->period)) + task->period) ==
                       ((tick - (tick % next_task->period)) +
                        next_task->period) &&
                   task->id < next_task->id) {
          next_task = task;
        }
      }

      if (next_task != NULL) {
        if (current_task != NULL && current_task->id != next_task->id) {
          hashmap_put(&ready_queue, current_task, (void *)1);
          current_step.duration.finish = tick;
          kv_push(step_t, steps, current_step);
        }
        hashmap_remove(&ready_queue, next_task);
        current_task = next_task;
        current_step.task_id = current_task->id;
        current_step.duration.start = tick;
      }
    }
    has_ready_queue_changed = false;
    if (current_task != NULL) {
      execution_time[current_task->id - 1] += 1;
    }
  }
  hashmap_cleanup(&ready_queue);
  return (steps_t){.steps = steps, .ended_early = false};
}
