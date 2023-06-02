#ifndef TEX_H
#define TEX_H
#include <stdio.h>
#include <stdlib.h>

void gen_timeline(FILE *fp);
void gen_frame(FILE *fp, const char *frame_title);
void gen_all_frames(void);

#endif // !TEX_H
