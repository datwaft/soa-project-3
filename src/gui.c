#include "gui.h"

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

GtkApplication *application_new(void) {
  GtkApplication *application =
      gtk_application_new(APPLICATION_ID, G_APPLICATION_FLAGS_NONE);
  g_signal_connect(application, "activate", G_CALLBACK(application_on_activate),
                   NULL);
  return application;
}

void application_on_activate(GtkApplication *app, gpointer _) {
  user_data_t user_data = {
      .builder = gtk_builder_new_from_resource(TEMPLATE_URI),
  };
  gtk_builder_connect_signals(user_data.builder, &user_data);

  //   generate_configuration_rows(DEFAULT_THREAD_NUM, &user_data);

  GtkWidget *window =
      GTK_WIDGET(gtk_builder_get_object(user_data.builder, "window_main"));
  gtk_widget_show_all(window);

  gtk_main();
}

void window_on_delete_event(GtkWidget *widget, gpointer user_data) {
  gtk_main_quit();
}

void on_changed_sbtn_task_num(GtkComboBox *widget, user_data_t *user_data) {
  GtkSpinButton *spin_task_num = GTK_SPIN_BUTTON(
      gtk_builder_get_object(user_data->builder, "spin_task_num"));
  gint new_rows = gtk_spin_button_get_value(spin_task_num);

  clear_configuration_rows(user_data);
  generate_configuration_rows(new_rows, user_data);
}

static void clear_configuration_rows(user_data_t *user_data) {
  GtkContainer *box_task_config = GTK_CONTAINER(
      gtk_builder_get_object(user_data->builder, "box_task_config"));
  GList *children = gtk_container_get_children(box_task_config);
  while (children) {
    gtk_container_remove(box_task_config, children->data);
    children = children->next;
  }
}

static void generate_configuration_rows(int row_n, user_data_t *user_data) {
  for (int row = 0; row < row_n; row++) {
    GtkWidget *grid_row = gtk_grid_new();

    // We start at enumerating rows at 1.
    char row_str[5]; // We probably won't need more than 5 digits.
    sprintf(row_str, "%d", row + 1);
    GtkWidget *label_row = gtk_label_new(row_str);

    GtkAdjustment *adjustment_ticket = gtk_adjustment_new(
        DEFAULT_EXECUTION, MIN_EXECUTION, MAX_EXECUTION, 1.0, 5.0, 0.0);
    GtkWidget *sbtn_execution = gtk_spin_button_new(adjustment_ticket, 1.0, 0);
    gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(sbtn_execution), true);

    GtkAdjustment *adjustment_work = gtk_adjustment_new(
        DEFAULT_PERIOD, MIN_PERIOD, MAX_PERIOD, 1.0, 5.0, 0.0);
    GtkWidget *sbtn_period = gtk_spin_button_new(adjustment_work, 1.0, 0);
    gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(sbtn_period), true);

    gtk_grid_attach(GTK_GRID(grid_row), label_row, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid_row), sbtn_execution, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid_row), sbtn_period, 2, 0, 1, 1);
    gtk_widget_show(grid_row);

    gtk_grid_set_column_homogeneous(GTK_GRID(grid_row), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(grid_row), 3);

    GtkBox *box_task_config =
        GTK_BOX(gtk_builder_get_object(user_data->builder, "box_task_config"));
    gtk_box_pack_start(box_task_config, grid_row, FALSE, FALSE, 3);

    gtk_widget_show(sbtn_execution);
    gtk_widget_show(sbtn_period);
    gtk_widget_show(label_row);
  }
}

void on_button_execute_clicked(GtkWidget *widget, user_data_t *user_data) {

  GtkComboBox *cb_display_mode = GTK_COMBO_BOX(
      gtk_builder_get_object(user_data->builder, "cb_display_mode"));

  GtkSpinButton *spin_task_num = GTK_SPIN_BUTTON(
      gtk_builder_get_object(user_data->builder, "spin_task_num"));

  GtkCheckButton *checkbtn_rm = GTK_CHECK_BUTTON(
      gtk_builder_get_object(user_data->builder, "checkbtn_rm"));

  GtkCheckButton *checkbtn_edf = GTK_CHECK_BUTTON(
      gtk_builder_get_object(user_data->builder, "checkbtn_edf"));

  GtkCheckButton *checkbtn_llf = GTK_CHECK_BUTTON(
      gtk_builder_get_object(user_data->builder, "checkbtn_llf"));

  bool rm_active = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbtn_rm));

  bool edf_active =
      gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbtn_edf));

  bool llf_active =
      gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbtn_llf));

  int sdf = gtk_combo_box_get_active(cb_display_mode);

  gint task_n = gtk_spin_button_get_value(spin_task_num);

  GtkContainer *box_task_config = GTK_CONTAINER(
      gtk_builder_get_object(user_data->builder, "box_task_config"));
  GList *children = gtk_container_get_children(box_task_config);

  uint64_t execution_n[task_n];
  int64_t period_n[task_n];

  for (gint i = 0; children; ++i, children = children->next) {
    gint execution_column_value = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(gtk_grid_get_child_at(GTK_GRID(children->data), 1, 0)));
    gint period_column_value = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(gtk_grid_get_child_at(GTK_GRID(children->data), 2, 0)));
    execution_n[i] = execution_column_value;
    period_n[i] = period_column_value;
  }

  for (gint i = 0; i < task_n; ++i) {
    char info[10];
    sprintf(info, "%ld - %ld\n", execution_n[i], period_n[i]);
    g_print(info);
    // args_t *args = malloc(sizeof(args_t));

    // args->i = 0;
    // args->n = period_n[i] * 50;
    // args->result = 0;
    // args->sign = 1;
    // args->divisor = 1;
    // args->row = generate_execution_row(i, user_data);

    // scheduler_create_task((scheduler_f_addr_t)calculate_pi, args,
    // execution_n[i]);
  }

  if (!(rm_active || edf_active || llf_active)) {
    failure_dialog();
  } else {
    success_dialog();
  }

  //   execute_scheduler(user_data);
}

static void success_dialog(void) {

  GtkWidget *message_widget = gtk_message_dialog_new(
      NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Exito!");

  gtk_message_dialog_format_secondary_text(
      GTK_MESSAGE_DIALOG(message_widget),
      "Se ha creado un PDF con los resultados de pruebas de scheduling.");

  gtk_dialog_run(GTK_DIALOG(message_widget));

  gtk_widget_destroy(message_widget);
}

static void failure_dialog(void) {

  GtkWidget *message_widget = gtk_message_dialog_new(
      NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Error!");

  gtk_message_dialog_format_secondary_text(
      GTK_MESSAGE_DIALOG(message_widget),
      "Se require elegir al menos un algoritmo de scheduling.");

  gtk_dialog_run(GTK_DIALOG(message_widget));

  gtk_widget_destroy(message_widget);
}
