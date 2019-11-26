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
void lee(GtkButton *button, gpointer data);
void Cambiaopcion1(GtkToggleButton *button, gpointer data);

gint main (gint argc, gchar *argv[]){
  gint i;
  gchar a[2];
  GtkWidget *window,*button,*box,*verticalbox,*entrybox,*menu_bar,*menu,*op1,*op2,*op3,*root_menu,*rb1,*rb2,*cajarb,*cajacalc,*cajatodo;

  gtk_init(&argc, &argv);

  window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window),140,250);
  gtk_container_border_width(GTK_CONTAINER(window),5);
  gtk_window_set_title(GTK_WINDOW(window),"Menu");



  verticalbox = gtk_vbox_new(FALSE,5);
  gtk_container_add(GTK_CONTAINER(window),verticalbox);

  cajacalc=gtk_vbox_new(TRUE,5);
  cajatodo=gtk_hbox_new(FALSE,5);

  box=gtk_hbox_new(TRUE,0);

  //menu
  menu_bar=gtk_menu_bar_new();

  menu=gtk_menu_new();
  op1=gtk_menu_item_new_with_label("op1");
  op2=gtk_menu_item_new_with_label("op2");
  op3=gtk_menu_item_new_with_label("Salir");

  gtk_signal_connect(GTK_OBJECT(op3),"activate",GTK_SIGNAL_FUNC(StopTheApp),NULL);

  gtk_menu_append(GTK_MENU(menu),op1);
  gtk_menu_append(GTK_MENU(menu),op2);
  gtk_menu_append(GTK_MENU(menu),op3);

  root_menu=gtk_menu_item_new_with_label("Calculadora");

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(root_menu),menu);

  gtk_menu_bar_append(GTK_MENU_BAR(menu_bar),root_menu);

  //sub2
  menu=gtk_menu_new();
  op1=gtk_menu_item_new_with_label("Leer");
  op2=gtk_menu_item_new_with_label("Guardar");
  op3=gtk_menu_item_new_with_label("Nuevo");

  gtk_menu_append(GTK_MENU(menu),op1);
  gtk_menu_append(GTK_MENU(menu),op2);
  gtk_menu_append(GTK_MENU(menu),op3);

  gtk_signal_connect(GTK_OBJECT(op1),"activate",GTK_SIGNAL_FUNC(lee),NULL);
  gtk_signal_connect(GTK_OBJECT(op2),"activate",GTK_SIGNAL_FUNC(lee),NULL);
  gtk_signal_connect(GTK_OBJECT(op3),"activate",GTK_SIGNAL_FUNC(lee),NULL);

  root_menu=gtk_menu_item_new_with_label("Juego");

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(root_menu),menu);

  gtk_menu_bar_append(GTK_MENU_BAR(menu_bar),root_menu);

  //sub3

  root_menu=gtk_menu_item_new_with_label("Opc3");
  gtk_signal_connect(GTK_OBJECT(root_menu),"activate",GTK_SIGNAL_FUNC(StopTheApp),NULL);
  gtk_menu_bar_append(GTK_MENU_BAR(menu_bar),root_menu);

  gtk_box_pack_start(GTK_BOX(verticalbox),menu_bar,FALSE,FALSE,0);

  //radiobutton

  cajarb=gtk_vbox_new(TRUE,0);

  rb1=gtk_radio_button_new_with_label(NULL,"Opcion 1");
  gtk_box_pack_start(GTK_BOX(cajarb),rb1,FALSE,FALSE,0);
  gtk_signal_connect(GTK_OBJECT(rb1),"toggled",GTK_SIGNAL_FUNC(Cambiaopcion1),"1");

  rb2=gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(rb1)),"Opcion 2");
  gtk_box_pack_start(GTK_BOX(cajarb),rb2,FALSE,FALSE,0);
  gtk_signal_connect(GTK_OBJECT(rb2),"toggled",GTK_SIGNAL_FUNC(Cambiaopcion1),"2");

  rb2=gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(rb1)),"Opcion 3");
  gtk_box_pack_start(GTK_BOX(cajarb),rb2,FALSE,FALSE,0);
  gtk_signal_connect(GTK_OBJECT(rb2),"toggled",GTK_SIGNAL_FUNC(Cambiaopcion1),"3");


  entrybox = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(cajacalc),entrybox,TRUE,TRUE,5);

  box=gtk_hbox_new(TRUE,0);

  for(i=0;i<3;i++){
    sprintf(a,"%d",i+1);
    button=AddButton(box,a,Imprimir,entrybox);
  }

  button=AddButtonn(box,"CE",Limpiar,entrybox);
  gtk_box_pack_start(GTK_BOX(cajacalc),box,FALSE,TRUE,0);

  box=gtk_hbox_new(TRUE,0);

  for(i=0;i<3;i++){
    sprintf(a,"%d",i+4);
    button=AddButton(box,a,Imprimir,entrybox);
  }
  strcpy(a,"-");
  button=AddButtonn(box,a,Imprimir,entrybox);

  gtk_box_pack_start(GTK_BOX(cajacalc),box,FALSE,TRUE,0);

  box=gtk_hbox_new(TRUE,0);

  for(i=0;i<3;i++){
    sprintf(a,"%d",i+7);
    button=AddButton(box,a,Imprimir,entrybox);
  }
  strcpy(a,"+");
  button=AddButtonn(box,a,Imprimir,entrybox);

  gtk_box_pack_start(GTK_BOX(cajacalc),box,FALSE,TRUE,0);

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

  gtk_box_pack_start(GTK_BOX(cajacalc),box,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(cajatodo),cajacalc,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(cajatodo),cajarb,TRUE,TRUE,0);

  gtk_box_pack_start(GTK_BOX(verticalbox),cajatodo,TRUE,TRUE,0);

  gtk_widget_show_all(window);
  gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);
  gtk_main();
  return 0;
}

void Cambiaopcion1(GtkToggleButton *button, gpointer data){
  char *cad=(char *)data;
  if(gtk_toggle_button_get_active(button))
    g_print("Boton seleccionado %s\n",cad);
}

void lee(GtkButton *button, gpointer data){
  g_print("Hola\n");
}

GtkWidget *AddButton(GtkWidget *theBox, const gchar *buttonText, gpointer CallBackFunction, GtkWidget *EntryBox){
    GtkWidget *button;
    button = gtk_button_new_with_label(buttonText);
    gtk_box_pack_start(GTK_BOX(theBox),button,FALSE,TRUE,1);
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
    gtk_box_pack_start(GTK_BOX(theBox),button,FALSE,TRUE,1);
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
