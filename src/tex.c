#include "tex.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "algorithms.h"
#include "step.h"
#include "task.h"

static void schedulability_test_frame(FILE *file, char const *algorithm,
                                      task_t tasks[], int64_t tasks_size);

void draw_task(FILE *fp, int task_id, int start, int finish) {
  int color = task_id; // 1 to 9 as defined in latex/beamer-template.tex

  // Task fill
  fprintf(fp,
          "\\fill[color=color%d!20] rectangle ($(%d,0)$) -- ($(%d,0)$) -- "
          "($(%d,1)$) -- ($(%d,1)$);\n",
          color, start, finish, finish, start);

  // Task fill, middle task name placement
  fprintf(fp,
          "\\draw ($(%d,0)+(%f,0.5)$) "
          "node[activity,color%d,font=\\fontsize{6}{0}\\selectfont] {%d};\n",
          start, ((finish - start) / 2.0), color, task_id);
}

void draw_period(FILE *fp, int task_id, int task_period) {
  fprintf(fp,
          "\\draw[<-,ultra thin,color=black] ($(%d,0)$) -- ($(%d,1.5)$) node "
          "[above=0pt,align=center,black,font=\\fontsize{5}{0}\\selectfont]"
          " {%d};\n",
          task_period, task_period, task_id);
}

void gen_timeline(FILE *fp, const char *algorithm, step_t *steps, int steps_n,
                  task_t *tasks, int task_n) {
  int max = 0;

  for (int i = 0; i < task_n; i++) {
    if (tasks[i].period > max)
      max = tasks[i].period;
  }

  int max_scale = max + steps_n;
  float graph_scale = 0.7;
  fprintf(fp, "\\begin{tikzpicture}[very thick, black, scale=%f]\n",
          graph_scale);
  fprintf(fp, "\\small\n");

  fprintf(fp, "\\draw ($(0,2)$) node[activity, black] {%s};\n", algorithm);

  // draw all
  for (int i = 0; i < steps_n; i++) {
    draw_task(fp, steps[i].task_id, steps[i].duration.start,
              steps[i].duration.finish);
  }

  // draw periods
  for (int i = 0; i < task_n; i++) {
    int m = max / tasks[i].period;
    for (int j = 1; j <= m; j++) {
      draw_period(fp, tasks[i].id, tasks[i].period * j);
    }
  }

  // timeline
  int max_ticks = max_scale;
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

void gen_frame(FILE *fp, const char *frame_title, const char *algorithm,
               step_t *steps, int steps_n, task_t *tasks, int task_n) {

  fprintf(fp, "\\begin{frame}\n");
  fprintf(fp, "\\frametitle{%s}\n", frame_title);

  gen_timeline(fp, algorithm, steps, steps_n, tasks, task_n);

  fprintf(fp, "\\end{frame}\n");
}

void execute_n_display_all_in_one(task_t *tasks, int task_n,
                                  const char *frame_title, int rm_active,
                                  int edf_active, int llf_active) {
  FILE *fp;
  fp = fopen(BEAMER_TEX_FRAMES, "w");

  if (rm_active) {
    schedulability_test_frame(fp, "RM", tasks, task_n);
  }

  if (edf_active) {
    schedulability_test_frame(fp, "EDF", tasks, task_n);
  }

  if (llf_active) {
    schedulability_test_frame(fp, "LLF", tasks, task_n);
  }

  fprintf(fp, "\\begin{frame}\n");
  fprintf(fp, "\\frametitle{%s}\n", frame_title);

  if (rm_active) {
    // calculate RM

    steps_t result = steps_RM(tasks, task_n);
    step_vec_t steps = result.steps;
    bool ended_early = result.ended_early;

    if (ended_early) {
      char str[100];
      sprintf(str, "RM: No Schedulable, µ=%lf, U=%lf", calc_µ(tasks, task_n),
              calc_U_RM(task_n));

      gen_timeline(fp, str, steps.a, kv_size(steps), tasks, task_n);
    } else {
      gen_timeline(fp, "RM", steps.a, kv_size(steps), tasks, task_n);
    }
  }

  if (edf_active) {
    // calculate EDF

    steps_t result = steps_EDF(tasks, task_n);
    step_vec_t steps = result.steps;
    bool ended_early = result.ended_early;

    if (ended_early) {
      gen_timeline(fp, "EDF: No Schedulable", steps.a, kv_size(steps), tasks,
                   task_n);
    } else {
      gen_timeline(fp, "EDF", steps.a, kv_size(steps), tasks, task_n);
    }
  }

  if (llf_active) {
    // calculate LLF

    steps_t result = steps_LLF(tasks, task_n);
    step_vec_t steps = result.steps;
    bool ended_early = result.ended_early;

    // TODO: remove this
    for (size_t i = 0; i < kv_size(steps); ++i) {
      char buffer[STEP_SERIALIZE_LENGTH + 1];
      step_serialize(buffer, &kv_A(steps, i));
      printf("%s\n", buffer);
    }

    if (ended_early) {
      gen_timeline(fp, "LLF: No Schedulable", steps.a, kv_size(steps), tasks,
                   task_n);
    } else {
      gen_timeline(fp, "LLF", steps.a, kv_size(steps), tasks, task_n);
    }
  }

  fprintf(fp, "\\end{frame}\n");

  fclose(fp);

  compile_tex();
}

void execute_n_display_separate(task_t *tasks, int task_n, int rm_active,
                                int edf_active, int llf_active) {
  FILE *fp;
  fp = fopen(BEAMER_TEX_FRAMES, "w");

  if (rm_active) {
    schedulability_test_frame(fp, "RM", tasks, task_n);
  }

  if (edf_active) {
    schedulability_test_frame(fp, "EDF", tasks, task_n);
  }

  if (llf_active) {
    schedulability_test_frame(fp, "LLF", tasks, task_n);
  }

  if (rm_active) {
    // calculate RM

    steps_t result = steps_RM(tasks, task_n);
    step_vec_t steps = result.steps;
    bool ended_early = result.ended_early;

    if (ended_early) {
      char str[100];
      sprintf(str, "RM: No Schedulable, µ=%lf, U=%lf", calc_µ(tasks, task_n),
              calc_U_RM(task_n));

      gen_frame(fp, "RM Resultado", str, steps.a, kv_size(steps), tasks,
                task_n);
    } else {
      gen_frame(fp, "RM Resultado", "RM", steps.a, kv_size(steps), tasks,
                task_n);
    }
  }

  if (edf_active) {
    // calculate EDF

    steps_t result = steps_EDF(tasks, task_n);
    step_vec_t steps = result.steps;
    bool ended_early = result.ended_early;

    if (ended_early) {
      gen_frame(fp, "EDF Resultado", "EDF: No Schedulable", steps.a,
                kv_size(steps), tasks, task_n);
    } else {
      gen_frame(fp, "EDF Resultado", "EDF", steps.a, kv_size(steps), tasks,
                task_n);
    }
  }

  if (llf_active) {
    // calculate LLF

    steps_t result = steps_LLF(tasks, task_n);
    step_vec_t steps = result.steps;
    bool ended_early = result.ended_early;

    // TODO: remove this
    for (size_t i = 0; i < kv_size(steps); ++i) {
      char buffer[STEP_SERIALIZE_LENGTH + 1];
      step_serialize(buffer, &kv_A(steps, i));
      printf("%s\n", buffer);
    }

    if (ended_early) {
      gen_frame(fp, "LLF Resultado", "LLF: No Schedulable", steps.a,
                kv_size(steps), tasks, task_n);
    } else {
      gen_frame(fp, "LLF Resultado", "LLF", steps.a, kv_size(steps), tasks,
                task_n);
    }
  }

  fclose(fp);

  compile_tex();
}

void compile_tex(void) {
  // Need to compile twice for some reason...
  // Otherwise pdf will have extra page with error
  char pdflatex_cmd[200];
  sprintf(
      pdflatex_cmd,
      "pdflatex -interaction=errorstopmode -output-directory=%s %s > /dev/null",
      PDFLATEX_OUT, BEAMER_TEX_TEMPLATE);

  system(pdflatex_cmd);
  system(pdflatex_cmd);

  system("cp build/beamer-template.pdf build/Scheduling-Test.pdf");
  system("cd build/ && rm beamer-template*");
  system("open build/Scheduling-Test.pdf");
  system("cp resources/beamer-template.tex build/");
}

static void schedulability_test_frame(FILE *file, char const *algorithm,
                                      task_t tasks[], int64_t tasks_size) {
  fprintf(file, "\\begin{frame}\n");
  fprintf(file, "\\frametitle{Schedulability Test - %s}\n", algorithm);
  fprintf(file, "Schedulable if $\\mu < U(n)$\n");
  fprintf(file, "\\begin{equation}\n");
  double µ = calc_µ(tasks, tasks_size);
  double U = 1.0;
  if (strcmp(algorithm, "RM") == 0) {
    U = calc_U_RM(tasks_size);
  }
  if (µ < U) {
    fprintf(file, "%.3f < %.3f\n", µ, U);
  } else if (µ == U) {
    fprintf(file, "%.3f = %.3f\n", µ, U);
  } else {
    fprintf(file, "%.3f > %.3f\n", µ, U);
  }
  fprintf(file, "\\end{equation}\n");
  fprintf(file, "\\end{frame}\n");
}
