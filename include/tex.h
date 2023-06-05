#ifndef TEX_H
#define TEX_H
#include "step.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>

#define BEAMER_TEX_TEMPLATE "resources/beamer-template.tex"
#define BEAMER_TEX_FRAMES "build/uber-frames.tex"
#define PDFLATEX_OUT "build/"

void compile_tex(void);

void gen_timeline(FILE *fp, const char *algorithm, step_t *steps, int steps_n,
                  task_t *tasks, int task_n);

void gen_frame(FILE *fp, const char *frame_title, const char *algorithm,
               step_t *steps, int steps_n, task_t *tasks, int task_n);

void draw_task(FILE *fp, int task_id, int start, int finish);

void execute_n_display_all_in_one(task_t *tasks, int task_n,
                                  const char *frame_title, int rm_active,
                                  int edf_active, int llf_active);

void execute_n_display_separate(task_t *tasks, int task_n, int rm_active,
                                int edf_active, int llf_active);

void gen_tex(void);

#endif // !TEX_H
