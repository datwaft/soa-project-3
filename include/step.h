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

#endif /* !STEP_H */
