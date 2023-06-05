#ifndef STEP_H
#define STEP_H

#include <stddef.h>
#include <stdint.h>

#define STEP_SERIALIZE_LENGTH 172

typedef struct step_st {
  int64_t task_id;
  struct {
    int64_t start;
    int64_t finish;
  } duration;
} step_t;

int step_cmp(step_t const *step_1, step_t const *step_2);

// `buffer` must have a size of at least `STEP_SERIALIZE_LENGTH + 1`
void step_serialize(char buffer[], step_t const *step);

#endif /* !STEP_H */
