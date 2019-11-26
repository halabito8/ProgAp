#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>

typedef struct datos{
  GtkWidget *entry,*entry2,*rb1,*rb2,*zonas[5];
}info;

void Stop(GtkWindow *window,gpointer data);
void calcula(GtkWidget *window,gpointer data);

gint main (gint argc, gchar *argv[]){

  info datos;

  GtkWidget *window,*verticalbox,*label,*box,*rbbox,*button,*box1,*box2,*box3;
  int i,j=50;
  char nombre[20];

  gtk_init(&argc, &argv);

  window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window),400,300);
  gtk_container_border_width(GTK_CONTAINER(window),15);
  gtk_window_set_title(GTK_WINDOW(window),"Zonas Cardiacas");

  verticalbox = gtk_vbox_new(FALSE,2);
  gtk_container_add(GTK_CONTAINER(window),verticalbox);

  box=gtk_hbox_new(TRUE,5);
  gtk_box_pack_start(GTK_BOX(verticalbox),box,TRUE,TRUE,0);

  label=gtk_label_new("Edad:");
  gtk_box_pack_start(GTK_BOX(box),label,TRUE,TRUE,0);

  datos.entry=gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(box),datos.entry,TRUE,TRUE,0);

  box=gtk_hbox_new(TRUE,5);
  gtk_box_pack_start(GTK_BOX(verticalbox),box,TRUE,TRUE,0);

  label=gtk_label_new("Peso (libras):");
  gtk_box_pack_start(GTK_BOX(box),label,TRUE,TRUE,0);

  datos.entry2=gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(box),datos.entry2,TRUE,TRUE,0);

  box=gtk_hbox_new(TRUE,5);
  gtk_box_pack_start(GTK_BOX(verticalbox),box,TRUE,TRUE,0);

  label=gtk_label_new("");
  gtk_box_pack_start(GTK_BOX(box),label,TRUE,TRUE,0);

  rbbox=gtk_vbox_new(TRUE,5);
  gtk_box_pack_start(GTK_BOX(box),rbbox,TRUE,TRUE,0);

  datos.rb1=gtk_radio_button_new_with_label(NULL,"Hombre");
  gtk_box_pack_start(GTK_BOX(rbbox),datos.rb1,TRUE,TRUE,0);

  datos.rb2=gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(datos.rb1)),"Mujer");
  gtk_box_pack_start(GTK_BOX(rbbox),datos.rb2,TRUE,TRUE,0);

  box=gtk_hbox_new(TRUE,5);
  gtk_box_pack_start(GTK_BOX(verticalbox),box,TRUE,TRUE,0);

  button=gtk_button_new_with_label("Calcula");
  gtk_box_pack_start(GTK_BOX(box),button,TRUE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(calcula),&datos);

  label=gtk_label_new("");
  gtk_box_pack_start(GTK_BOX(box),label,TRUE,TRUE,0);

  box=gtk_hbox_new(TRUE,5);
  gtk_box_pack_start(GTK_BOX(verticalbox),box,TRUE,TRUE,0);

  label=gtk_label_new("Zonas");
  gtk_box_pack_start(GTK_BOX(box),label,TRUE,TRUE,0);

  box=gtk_hbox_new(TRUE,0);
  gtk_box_pack_start(GTK_BOX(verticalbox),box,FALSE,FALSE,0);

  box1=gtk_vbox_new(TRUE,5);
  gtk_box_pack_start(GTK_BOX(box),box1,TRUE,TRUE,0);

  for(i=0;i<5;i++){
    sprintf(nombre,"Zona %i",i+1);
    label=gtk_label_new(nombre);
    gtk_box_pack_start(GTK_BOX(box1),label,TRUE,TRUE,0);
  }

  box2=gtk_vbox_new(TRUE,5);
  gtk_box_pack_start(GTK_BOX(box),box2,TRUE,TRUE,0);

  for(i=0;i<5;i++){
    sprintf(nombre,"%i%% - %i%%",j,j+10);
    j+=10;
    label=gtk_label_new(nombre);
    gtk_box_pack_start(GTK_BOX(box2),label,TRUE,TRUE,0);
  }

  box3=gtk_vbox_new(TRUE,5);
  gtk_box_pack_start(GTK_BOX(box),box3,TRUE,TRUE,0);

  for(i=0;i<5;i++){
    datos.zonas[i]=gtk_label_new(NULL);
    gtk_box_pack_start(GTK_BOX(box3),datos.zonas[i],TRUE,TRUE,0);
  }

  gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(Stop),NULL);

  gtk_widget_show_all(window);
  gtk_main();
}

void Stop(GtkWindow *window,gpointer data){
  gtk_main_quit();
}

void calcula(GtkWidget *window,gpointer data){
  info *datos=(info *)data;
  const char *text;
  char texto[20];
  float edad,peso,latidos,diez;
  int i;

  text=gtk_entry_get_text(GTK_ENTRY(datos->entry));
  strcpy(texto,text);
  if(sscanf(texto,"%f",&edad)!=1){
    for(i=0;i<5;i++)
      gtk_label_set_label(GTK_LABEL(datos->zonas[i]),"Se ingreso una letra");
    return;
  }

  text=gtk_entry_get_text(GTK_ENTRY(datos->entry2));
  strcpy(texto,text);
  if(sscanf(texto,"%f",&peso)!=1){
    for(i=0;i<5;i++)
      gtk_label_set_label(GTK_LABEL(datos->zonas[i]),"Se ingreso una letra");
    return;
  }
  if(gtk_toggle_button_get_active(datos->rb1)){
    latidos=210-edad/2-.05*peso+4;
    diez=latidos/10;
    for(i=0;i<5;i++){
      sprintf(texto,"%.0f - %.0f ppm",diez*(i+5),diez*(i+6));
      gtk_label_set_label(GTK_LABEL(datos->zonas[i]),texto);
    }
  }
  else{
    latidos=210-edad/2-.01*peso;
    diez=latidos/10;
    for(i=0;i<5;i++){
      sprintf(texto,"%.0f - %.0f ppm",diez*(i+5),diez*(i+6));
      gtk_label_set_label(GTK_LABEL(datos->zonas[i]),texto);
    }
  }
}
