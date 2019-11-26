/* buttonsentry.c
   Este ejercicio muestra el uso de contenedores, botones y
   espacios de entrada con sus funciones de callback y seniales

*/

#include <gtk/gtk.h>
#include <string.h>


GtkWidget *AddButton(GtkWidget *theBox, const gchar *buttonText, gpointer CallBackFunction, GtkWidget *EntryBox);
void ButtonClicked(GtkButton *button, gpointer data);
void StopTheApp(GtkWidget *window, gpointer data);
void HelloAction(GtkButton *button, gpointer data);
void Arriba(GtkButton *button,gpointer data);
void Izq(GtkButton *button,gpointer data);
void enter(GtkButton *button,gpointer data);
void salir(GtkButton *button,gpointer data);


gint main ( gint argc, gchar *argv[])
{

  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *box;
  GtkWidget *cajaarriba;
  GtkWidget *verticalbox;
  GtkWidget *entrybox;
  GtkWidget *entrybox2;



  gtk_init(&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window),320,200);
  gtk_container_border_width(GTK_CONTAINER(window),5);

  gtk_window_set_title(GTK_WINDOW(window),"Irale");

  verticalbox = gtk_vbox_new(TRUE,5);

  entrybox = gtk_entry_new();
  entrybox2 = gtk_entry_new();

  cajaarriba=gtk_hbox_new(TRUE,5);

  box = gtk_hbox_new(TRUE,5);
  button = AddButton(box,"pon texto",ButtonClicked,entrybox);
  button = AddButton(box,"captura texto",HelloAction,entrybox);

  button=gtk_button_new_with_label("Arriba");
  gtk_box_pack_start(GTK_BOX(cajaarriba),button,TRUE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(Arriba),entrybox);

  button=gtk_button_new_with_label("Medio");
  gtk_box_pack_start(GTK_BOX(cajaarriba),button,TRUE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(Izq),entrybox2);
  gtk_signal_connect(GTK_OBJECT(button),"enter",GTK_SIGNAL_FUNC(enter),entrybox2);
  gtk_signal_connect(GTK_OBJECT(button),"leave",GTK_SIGNAL_FUNC(salir),entrybox2);

  gtk_box_pack_start(GTK_BOX(verticalbox),entrybox2,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(verticalbox),cajaarriba,TRUE,TRUE,0);
  gtk_box_pack_end(GTK_BOX(cajaarriba),entrybox,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(verticalbox),box,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(verticalbox),entrybox2,TRUE,TRUE,0);


  gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);


  gtk_container_add(GTK_CONTAINER(window),verticalbox);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;

}



GtkWidget *AddButton(GtkWidget *theBox, const gchar *buttonText, gpointer CallBackFunction, GtkWidget *EntryBox)
{
    GtkWidget *button;
    button = gtk_button_new_with_label(buttonText);
    gtk_box_pack_start(GTK_BOX(theBox),button,TRUE,TRUE,0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(CallBackFunction),EntryBox);
    gtk_widget_show(button);
    return button;


}

void Arriba(GtkButton *button,gpointer data){
  g_print("Funciona?\n");
}

void Izq(GtkButton *button,gpointer data){
  gchar *text;
  g_print("Medio\n");
  text=gtk_entry_get_text(GTK_ENTRY(data));
  if(strlen(text)==0)
    g_print("No hay nada\n");
  else{
    g_print("%s\n",text);
    gtk_entry_set_text(GTK_ENTRY(data),"JAJAJAJA");
  }
}

void salir(GtkButton *button,gpointer data){
  g_print("Salio de medio\n");
}

void enter(GtkButton *button,gpointer data){
  g_print("Entro a medio\n");
}

void ButtonClicked(GtkButton *button, gpointer data)
{
  int i;
  i=rand()%46;
  if(i<15)
    g_print("Deja de picarme \n");
  else if(i>14&&i<30)
    g_print("Ahora no estoy enojada\n");
  else
    g_print("Cinco minutos mas\n");

  gtk_entry_set_text(GTK_ENTRY(data),"Hola Mundo");



}



void HelloAction(GtkButton *button, gpointer data)
{
    const gchar *text;


    text =gtk_entry_get_text(GTK_ENTRY(data));

    g_print("%s\n",text);



}

void StopTheApp(GtkWidget *window, gpointer data)
{
    gtk_main_quit();


}
