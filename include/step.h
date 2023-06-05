#ifndef STEP_H
#define STEP_H

#include <stddef.h>
#include <stdint.h>

typedef struct step_st {
  int64_t task_id;
  struct {
    int64_t start;
    int64_t finish;
  } duration;
} step_t;

int step_cmp(step_t const *step_1, step_t const *step_2);

#endif /* !STEP_H */
