#include "tex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void gen_timeline(FILE *fp) {
  char algorithm_name[] = "RM";

  fprintf(fp, "\\begin{tikzpicture}[very thick, black, scale=.7]\n");
  fprintf(fp, "\\small\n");

  fprintf(fp, "\\draw ($(0,2)$) node[activity, black] {%s};\n", algorithm_name);

  // task fill
  int start = 0;
  int finish = 2;
  int color = 1; // as defined in beamer-template
  fprintf(fp,
          "\\fill[color=color%d!20] rectangle ($(%d,0)$) -- ($(%d,0)$) -- "
          "($(%d,1)$) -- ($(%d,1)$);\n",
          color, start, finish, finish, start);

  // task fill, middle task name placement
  fprintf(fp,
          "\\draw ($(%d,0)+(%f,0.5)$) "
          "node[activity,color%d,font=\\fontsize{6}{0}\\selectfont] {1};\n",
          start, ((finish - start) / 2.0), color);

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

void gen_frame() {
  char frame_name[] = "Testing Template";

  FILE *fp;
  fp = fopen("latex/frames/frame1.tex", "w");

  fprintf(fp, "\\begin{frame}\n");
  fprintf(fp, "\\frametitle{%s}\n", frame_name);

  gen_timeline(fp);

  fprintf(fp, "\\end{frame}\n");

  fclose(fp);
}
