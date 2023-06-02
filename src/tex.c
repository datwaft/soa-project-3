#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_INSERT 28

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
