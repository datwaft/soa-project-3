#ifndef TEX_H
#define TEX_H
#include <stdio.h>
#include <stdlib.h>

#define BEAMER_TEX_TEMPLATE "latex/beamer-template.tex"
#define BEAMER_TEX_FRAMES "latex/frames/uber-frames.tex"
#define PDFLATEX_OUT "latex/out/"

void compile_tex(void);

void gen_timeline(FILE *fp, const char *algorithm);

void gen_frame(FILE *fp, const char *frame_title, const char *algorithm);

void draw_task(FILE *fp, int task_id, int start, int finish);

void execute_n_display_all_in_one(const char *frame_title, int rm_active,
                                  int edf_active, int llf_active);

void execute_n_display_separate(int rm_active, int edf_active, int llf_active);

void gen_tex(void);

#endif // !TEX_H
