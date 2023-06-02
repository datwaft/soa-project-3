#include "tex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BEGIN "\begin {frame}"

void generate_tex() {
  FILE *fp_template;
  FILE *fp_output;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  fp_template = fopen("latex/beamer-template.tex", "r");
  fp_output = fopen("latex/beamer-output.tex", "w");

  if (fp_template == NULL)
    exit(EXIT_FAILURE);

  int line_counter = 1;
  while ((read = getline(&line, &len, fp_template)) != -1) {
    printf("Retrieved line of length %zu:\n", read);
    printf("%s", line);
    fprintf(fp_output, "%s", line);

    if (line_counter == LINE_INSERT) {
      fprintf(fp_output, "%s", "hellow world\n");
    }

    line_counter++;
  }

  fclose(fp_template);
  fclose(fp_output);

  if (line)
    free(line);
  exit(EXIT_SUCCESS);
}

void gen() {
  char frame_name[] = "Super Chart";
  char algorithm_name[] = "RM2";

  FILE *fp;
  fp = fopen("latex/frames/frame1.tex", "w");

  fprintf(fp, "\\begin{frame}\n");
  fprintf(fp, "\\frametitle{%s}\n", frame_name);
  fprintf(fp, "\\begin{tikzpicture}[very thick, black, scale=.8]\n");
  fprintf(fp, "\\small\n");

  fprintf(fp, "\\draw ($(0,2)$) node[activity, black] {%s};\n", algorithm_name);

  // task fill
  int start = 1;
  int finish = 7;
  fprintf(fp,
          "\\fill[color=color1!20] rectangle ($(%d,0)$) -- ($(%d,0)$) -- "
          "($(%d,1)$) -- ($(%d,1)$);\n",
          start, finish, finish, start);
  // period

  int task_period = 4;
  fprintf(fp,
          "\\draw[<-,thick,color=black] ($(%d,0)$) -- ($(%d,1.5)$) node "
          "[above=0pt,align=center,black,font=\\fontsize{8}{0}\\selectfont]"
          " {p1};\n",
          task_period, task_period);

  // timeline
  fprintf(fp, "\\draw[->] ($(0,0)$) -- ($(14,0)$);\n");

  // timeline ticks
  fprintf(fp, "\\foreach \\x in {0,2,...,12}\n");
  fprintf(fp, "\\draw(\\x cm,3pt) -- (\\x cm,-1pt);\n");

  // timeline labels
  fprintf(fp, "\\foreach \\i \\j in {0/0,2/2,4/4,6/6,8/8,10/10,12/12}{\\draw "
              "(\\i,0) node[below=0.5pt] {\\j} ;}\n");

  fprintf(fp, "\\end{tikzpicture}\n");
  fprintf(fp, "\\end{frame}\n");

  fclose(fp);
}
