#include "tex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Draw a single processing time.
*/
void draw_task(FILE *fp, int task_id, int start, int finish) {
  int color = task_id; // 1 to 9 as defined in latex/beamer-template.tex
  // task fill
  fprintf(fp,
          "\\fill[color=color%d!20] rectangle ($(%d,0)$) -- ($(%d,0)$) -- "
          "($(%d,1)$) -- ($(%d,1)$);\n",
          color, start, finish, finish, start);

  // task fill, middle task name placement
  fprintf(fp,
          "\\draw ($(%d,0)+(%f,0.5)$) "
          "node[activity,color%d,font=\\fontsize{6}{0}\\selectfont] {%d};\n",
          start, ((finish - start) / 2.0), color, task_id);
}

/*
Generate single timeline for an algorithm
 */
void gen_timeline(FILE *fp, const char *algorithm) {

  fprintf(fp, "\\begin{tikzpicture}[very thick, black, scale=.7]\n");
  fprintf(fp, "\\small\n");

  fprintf(fp, "\\draw ($(0,2)$) node[activity, black] {%s};\n", algorithm);

  draw_task(fp, 1, 0, 2);
  draw_task(fp, 1, 6, 8);
  draw_task(fp, 2, 2, 4);
  draw_task(fp, 2, 8, 10);

  // period
  int task_period = 6;
  fprintf(fp,
          "\\draw[<-,thick,color=black] ($(%d,0)$) -- ($(%d,1.5)$) node "
          "[above=0pt,align=center,black,font=\\fontsize{7}{0}\\selectfont]"
          " {p1};\n",
          task_period, task_period);

  // timeline
  int max_ticks = 15;
  int tick_scale = 2;
  fprintf(fp, "\\draw[->] ($(0,0)$) -- ($(%d,0)$);\n", max_ticks + 1);

  // timeline ticks & labels
  fprintf(fp,
          "\\foreach \\x in {0,%d,...,%d} {\\draw(\\x cm,3pt) -- (\\x "
          "cm,-1pt);\\draw(\\x,0) node[below=0.5pt, "
          "font=\\fontsize{8}{0}\\selectfont] {\\x} ;}\n ",
          tick_scale, max_ticks);

  fprintf(fp, "\\end{tikzpicture}\n");
}

/*
Generate a single frame (slide)
*/
void gen_frame(FILE *fp, const char *frame_title, const char *algorithm) {

  fprintf(fp, "\\begin{frame}\n");
  fprintf(fp, "\\frametitle{%s}\n", frame_title);

  gen_timeline(fp, algorithm);

  fprintf(fp, "\\end{frame}\n");
}

/*
Generate multiple algorithm timeline in a single frame (slide)
*/
void execute_n_display_all_in_one(const char *frame_title, int rm_active,
                                  int edf_active, int llf_active) {
  FILE *fp;
  fp = fopen(BEAMER_TEX_FRAMES, "w");

  fprintf(fp, "\\begin{frame}\n");
  fprintf(fp, "\\frametitle{%s}\n", frame_title);

  if (rm_active) {
    // calculate rm
    gen_timeline(fp, "RM");
  }

  if (edf_active) {
    // calculate edf
    gen_timeline(fp, "EDF");
  }

  if (llf_active) {
    // calculate llf
    gen_timeline(fp, "LLF");
  }

  fprintf(fp, "\\end{frame}\n");

  fclose(fp);

  compile_tex();
}

/*
Generate multiple frames with single timelines
*/
void execute_n_display_separate(int rm_active, int edf_active, int llf_active) {
  FILE *fp;
  fp = fopen(BEAMER_TEX_FRAMES, "w");

  if (rm_active) {
    // calculate rm
    gen_frame(fp, "RM Resultado", "RM");
  }

  if (edf_active) {
    // calculate edf
    gen_frame(fp, "EDF Resultado", "EDF");
  }

  if (llf_active) {
    // calculate llf
    gen_frame(fp, "LLF Resultado", "LLF");
  }

  fclose(fp);

  compile_tex();
}

// for testing
void gen_tex(void) {

  //   gen_frame(fp, "RM Run");
  // execute_n_display_all_in_one("Multiple");
  // execute_n_display_separate("Single");
  execute_n_display_separate(1, 1, 1);
}

void compile_tex(void) {
  // need to compile twice for some reason...
  // otherwise pdf will have extra page with error

  char pdflatex_cmd[100];
  sprintf(pdflatex_cmd, "pdflatex --job-name=RESULT -output-directory=%s %s",
          PDFLATEX_OUT, BEAMER_TEX_TEMPLATE);

  system(pdflatex_cmd);
  system(pdflatex_cmd);

  system("cp latex/out/beamer-template.pdf latex/out/Scheduling-Test.pdf");
  system("cd latex/out/ && rm beamer-template*");
  system("open latex/out/Scheduling-Test.pdf");
}
