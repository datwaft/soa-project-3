#ifndef TEX_H
#define TEX_H

#include <stdio.h>
#include <stdlib.h>

#include "step.h"
#include "task.h"

#define BEAMER_TEX_TEMPLATE "resources/beamer-template.tex"
#define BEAMER_TEX_FRAMES "build/uber-frames.tex"
#define PDFLATEX_OUT "build/"

// Draw a single processing time.
void draw_task(FILE *fp, int task_id, int start, int finish);

// Generate single timeline for an algorithm
void gen_timeline(FILE *fp, const char *algorithm, step_t *steps, int steps_n,
                  task_t *tasks, int task_n);

// Generate a single frame (slide)
void gen_frame(FILE *fp, const char *frame_title, const char *algorithm,
               step_t *steps, int steps_n, task_t *tasks, int task_n);

// Generate multiple algorithm timeline in a single frame (slide)
void execute_n_display_all_in_one(task_t *tasks, int task_n,
                                  const char *frame_title, int rm_active,
                                  int edf_active, int llf_active);

// Generate multiple frames with single timelines
void execute_n_display_separate(task_t *tasks, int task_n, int rm_active,
                                int edf_active, int llf_active);

void compile_tex(void);

#endif // !TEX_H
