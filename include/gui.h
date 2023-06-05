#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>

// Application constants
#define APPLICATION_ID "com.soa.pr3"
#define TEMPLATE_URI "/com/soa/pr3/template.ui"
#define DEFAULT_EXECUTION 1
#define MAX_EXECUTION 100
#define MIN_EXECUTION 1
#define DEFAULT_PERIOD 1
#define MAX_PERIOD 100
#define MIN_PERIOD 1

typedef struct user_data_st {
  GtkBuilder *builder;
} user_data_t;

GtkApplication *application_new(void);

void application_on_activate(GtkApplication *app, gpointer user_data);

void window_on_delete_event(GtkWidget *widget, gpointer user_data);

void on_changed_sbtn_task_num(GtkComboBox *widget, user_data_t *user_data);

#endif // !GUI_H
