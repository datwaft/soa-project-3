#ifndef TEX_H
#define TEX_H
#include <stdio.h>
#include <stdlib.h>

void compile_tex(void);
void gen_timeline(FILE *fp, const char *algorithm);
void gen_frame(FILE *fp, const char *frame_title, const char *algorithm);
void draw_task(FILE *fp, int task_id, int start, int finish);
void gen_frame_multiple_timeline(FILE *fp, const char *frame_title);
void gen_frame_single_timeline(FILE *fp, const char *frame_title);
void gen_tex(void);

#endif // !TEX_H
