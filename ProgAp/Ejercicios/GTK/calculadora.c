#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>

GtkWidget *AddButton(GtkWidget *theBox, const gchar *buttonText, gpointer CallBackFunction, GtkWidget *EntryBox);
GtkWidget *AddButtonn(GtkWidget *theBox, const gchar *buttonText, gpointer CallBackFunction, GtkWidget *EntryBox);
void StopTheApp(GtkWidget *window, gpointer data);
void Imprimir(GtkButton *button, gpointer data);
void Calcular(GtkWidget *button, gpointer data);
void Limpiar(GtkWidget *button, gpointer data);
void Operando(GtkButton *button, gpointer data);

gint main (gint argc, gchar *argv[]){
  gint i;
  gchar a[2];
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *box;
  GtkWidget *verticalbox;
  GtkWidget *entrybox;

  gtk_init(&argc, &argv);

  window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window),320,200);
  gtk_container_border_width(GTK_CONTAINER(window),5);
  gtk_window_set_title(GTK_WINDOW(window),"Cotorreo");

  verticalbox = gtk_vbox_new(TRUE,5);
  gtk_container_add(GTK_CONTAINER(window),verticalbox);

  entrybox = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(verticalbox),entrybox,TRUE,TRUE,5);

  box=gtk_hbox_new(TRUE,0);

  for(i=0;i<3;i++){
    sprintf(a,"%d",i+1);
    button=AddButton(box,a,Imprimir,entrybox);
  }

  button=AddButtonn(box,"CE",Limpiar,entrybox);
  gtk_box_pack_start(GTK_BOX(verticalbox),box,FALSE,TRUE,0);

  box=gtk_hbox_new(TRUE,0);

  for(i=0;i<3;i++){
    sprintf(a,"%d",i+4);
    button=AddButton(box,a,Imprimir,entrybox);
  }
  strcpy(a,"-");
  button=AddButtonn(box,a,Imprimir,entrybox);

  gtk_box_pack_start(GTK_BOX(verticalbox),box,FALSE,TRUE,0);

  box=gtk_hbox_new(TRUE,0);

  for(i=0;i<3;i++){
    sprintf(a,"%d",i+7);
    button=AddButton(box,a,Imprimir,entrybox);
  }
  strcpy(a,"+");
  button=AddButtonn(box,a,Imprimir,entrybox);

  gtk_box_pack_start(GTK_BOX(verticalbox),box,FALSE,TRUE,0);

  box=gtk_hbox_new(TRUE,0);

  strcpy(a,"0");
  button=AddButton(box,a,Imprimir,entrybox);
  strcpy(a,"/");
  button=AddButtonn(box,a,Imprimir,entrybox);
  strcpy(a,"*");
  button=AddButtonn(box,a,Imprimir,entrybox);
  strcpy(a,".");
  button=AddButtonn(box,a,Imprimir,entrybox);
  strcpy(a,"=");
  button=AddButtonn(box,a,Calcular,entrybox);

  gtk_box_pack_start(GTK_BOX(verticalbox),box,TRUE,TRUE,0);

  gtk_widget_show_all(window);
  gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);
  gtk_main();
  return 0;
}

GtkWidget *AddButton(GtkWidget *theBox, const gchar *buttonText, gpointer CallBackFunction, GtkWidget *EntryBox){
    GtkWidget *button;
    button = gtk_button_new_with_label(buttonText);
    gtk_box_pack_start(GTK_BOX(theBox),button,FALSE,TRUE,0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(CallBackFunction),EntryBox);
    gtk_widget_show(button);
    return button;
}

GtkWidget *AddButtonn(GtkWidget *theBox, const gchar *buttonText, gpointer CallBackFunction, GtkWidget *EntryBox){
    GtkWidget *button;
    GdkColor color;
    gdk_color_parse("#189AEF",&color);
    button = gtk_button_new_with_label(buttonText);
    gtk_widget_modify_bg(button,GTK_STATE_NORMAL,&color);
    gtk_widget_modify_bg(button,GTK_STATE_PRELIGHT,&color);
    gtk_box_pack_start(GTK_BOX(theBox),button,FALSE,TRUE,0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(CallBackFunction),EntryBox);
    gtk_widget_show(button);
    return button;
}

void Calcular(GtkWidget *button, gpointer data){
  float primero,segundo,final=0;
  const gchar *text;
  char resultado[200],op;
  text=gtk_entry_get_text(GTK_ENTRY(data));
  strcpy(resultado,text);
  sscanf(resultado,"%f%c%f",&primero,&op,&segundo);
  g_print("%s",text);
  switch(op){
    case '+':
      final=primero+segundo;
    break;
    case '-':
      final=primero-segundo;
    break;
    case '/':
      final=primero/segundo;
    break;
    case '*':
      final=primero*segundo;
    break;
  }
  sprintf(resultado,"%f",final);
  g_print("=%s\n",resultado);
  gtk_entry_set_text(GTK_ENTRY(data),resultado);
}

void Imprimir(GtkButton *button, gpointer data){
  char resultado[2];
  strcpy(resultado,gtk_button_get_label(button));
  gtk_entry_append_text(GTK_ENTRY(data),resultado);
}

void Limpiar(GtkWidget *button, gpointer data){
  gtk_entry_set_text(GTK_ENTRY(data),"\0");
}

void StopTheApp(GtkWidget *window, gpointer data){
  gtk_main_quit();
}
