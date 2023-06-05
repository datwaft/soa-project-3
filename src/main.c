#include <stdio.h>
#include <stdlib.h>

#include "gui.h"
#include "table_str.h"
#include "task.h"
#include "tex.h"

int main(int argc, char **argv) {
  g_application_run(G_APPLICATION(application_new()), argc, argv);
  return EXIT_SUCCESS;
}
