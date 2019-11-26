/**
 *@file formato.c
 *
 *@brief Este programa nos permite manipular, visualizar y
 *consultar información de los usuarios de una clínica, tanto
 *de los pacientes como de los médicos, así como el historial
 *clínico por medio de la parte gráfica utilizando estructuras
 *y archivos de texto para leer y utilizar la información.
 *
 *@autor David Halabe, Emanuel Bajonero, Gabriela Uribe
 *@date 30/04/2019
 */


#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct wid{
  GtkWidget *combo;
}hola;

void StopTheApp(GtkWidget *window, gpointer data);
void click(GtkWidget *window, gpointer data);


gint main ( gint argc, gchar *argv[])
{
  GtkWidget *window,*verticalbox,*button;
  hola cosa;

  gtk_init(&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window),"Combo");
  gtk_window_set_default_size(GTK_WINDOW(window),600,450);
  gtk_window_move(GTK_WINDOW(window),450,160);
  gtk_container_border_width(GTK_CONTAINER(window),15);
  verticalbox = gtk_vbox_new(FALSE,5);

  gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);

  cosa.combo=gtk_combo_box_new_text();
  gtk_box_pack_start(GTK_BOX(verticalbox),cosa.combo,FALSE,FALSE,0);
  gtk_combo_box_append_text(GTK_COMBO_BOX(cosa.combo),"Op1");
  gtk_combo_box_append_text(GTK_COMBO_BOX(cosa.combo),"Op2");

  button=gtk_button_new_with_label("Guardar");
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(click),&cosa);
  gtk_box_pack_start(GTK_BOX(verticalbox),button,FALSE,TRUE,0);

  gtk_container_add(GTK_CONTAINER(window),verticalbox);

  gtk_widget_show_all(window);
  gtk_main();
}

void StopTheApp(GtkWidget *window, gpointer data){
  gtk_main_quit();
}

void click(GtkWidget *window, gpointer data){
  hola *cosa=(hola *)data;
  const gchar *text;
  char texto [20];
  // gint i;
  // int e;
  // i=gtk_combo_box_get_active(GTK_COMBO_BOX(cosa->combo));
  // e=i;
  // g_print("%i\n",e);
  text=gtk_combo_box_get_active_text(GTK_COMBO_BOX(cosa->combo));
  strcpy(texto,text);
  g_print("%s\n",texto);
}
