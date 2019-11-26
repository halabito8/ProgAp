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
 *@date 09/05/2019
 */


#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include<time.h>

typedef struct Doctores
{
  char NombreD[200], Esp1[50], Esp2[50], TelU[20], TelN[20], DireccionD[100], Consultorio[15],Horario[10];
  int Estatus,dias[7];
  struct Doctores *der,*izq;
  GtkWidget *entrybox;
} tipodoctores;


typedef struct Pacientes
{
  char NombreP[30], DireccionP[100], TelP[20], Sexo[10], Alergias[100], TipoSangre[20], PadecimientosC[100],FechaN[15];
  int Edad;
  float Estatura;
  struct Pacientes *der,*izq;
} tipopacientes;

typedef struct cosas
{
  GtkWidget *window,*entrybox[15],*combo,*chkb[7],*rb[5],*calendario;
  tipopacientes *pinicio;
  tipodoctores *dinicio;
}tipowidget;

GtkWidget *AddButton1(GtkWidget *theBox, const gchar *buttonText, gpointer CallBackFunction, tipowidget *EntryBox);
GtkWidget *AddButton2(GtkWidget *theBox, const gchar *buttonText, gpointer CallBackFunction, GtkWidget *Cancelar);
void StopTheApp(GtkWidget *window, gpointer data);
void ShowNames(GtkButton *button, gpointer data);
void AcercaDe(GtkWidget *window, gpointer data);
void InsertaDV(GtkWidget *window, gpointer data);
void InsertaPV(GtkWidget *window, gpointer data);
void ADoctor(GtkWidget *window, gpointer data);
void ModificarP(GtkWidget *window, gpointer data);
void ModificarD(GtkWidget *window, gpointer data);
void ModificarC(GtkWidget *window, gpointer data);
void ListaDoc(GtkWidget *window, gpointer data);
void Imprimedoc(tipodoctores *dinicio);
void HistoriaClinica(GtkWidget *window, gpointer data);
void NuevaHC(GtkWidget *window, gpointer data);
void NoHay(GtkWidget *window, gpointer data);
void APaciente(GtkWidget *window, gpointer data);
void BorraDoc(tipodoctores *inicio);
void BorraPac(tipopacientes *inicio);
void Cancelar(GtkWidget *window, gpointer data);
void EstaSeguro(GtkWidget window, gpointer data);
void leerdoc(tipodoctores **inicio);
void escribirdoc(tipodoctores *inicio);





gint main ( gint argc, gchar *argv[])
{
  tipodoctores datos;
  tipowidget cosa;
  GtkWidget *button;
  GtkWidget *box, *box1, *box2, *box3,*box4,*box5,*box6,*box7;
  GtkWidget *verticalbox;
  GtkWidget *root_menu,*menu,*menu_bar,*op1,*op2,*op3;
  GtkWidget *label;
  GtkWidget *entrybox,*imagen,*imagen2;

  cosa.pinicio=NULL;
  cosa.dinicio=NULL;

  gtk_init(&argc, &argv);

  leerdoc(&cosa.dinicio);

  cosa.window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(cosa.window),"HOSPITAL BHU");
  gtk_window_set_default_size(GTK_WINDOW(cosa.window),600,450);
  gtk_window_move(GTK_WINDOW(cosa.window),470,230);
  gtk_container_border_width(GTK_CONTAINER(cosa.window),15);

  /***********************************************************************/

  //menu
  menu_bar=gtk_menu_bar_new();

  menu=gtk_menu_new();
  root_menu=gtk_menu_item_new_with_label("MODIFICAR");
  op1=gtk_menu_item_new_with_label("Doctores");
  op2=gtk_menu_item_new_with_label("Pacientes");
  op3=gtk_menu_item_new_with_label("Historia Clínica");

  gtk_menu_append(GTK_MENU(menu),op1);
  gtk_menu_append(GTK_MENU(menu),op2);
  gtk_menu_append(GTK_MENU(menu),op3);

  gtk_signal_connect(GTK_OBJECT(op1),"activate",GTK_SIGNAL_FUNC(ModificarD),&datos);
  gtk_signal_connect(GTK_OBJECT(op2),"activate",GTK_SIGNAL_FUNC(ModificarP),&datos);
  gtk_signal_connect(GTK_OBJECT(op3),"activate",GTK_SIGNAL_FUNC(ModificarC),&datos);

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(root_menu),menu);
  gtk_menu_bar_append(GTK_MENU_BAR(menu_bar),root_menu);

  //sub2
  menu=gtk_menu_new();
  root_menu=gtk_menu_item_new_with_label("VER");
  op1=gtk_menu_item_new_with_label("Doctores");
  op2=gtk_menu_item_new_with_label("Pacientes");
  op3=gtk_menu_item_new_with_label("Historia Clínica");

  gtk_menu_append(GTK_MENU(menu),op1);
  gtk_menu_append(GTK_MENU(menu),op2);
  gtk_menu_append(GTK_MENU(menu),op3);

  gtk_signal_connect(GTK_OBJECT(op1),"activate",GTK_SIGNAL_FUNC(ListaDoc),&cosa);
  gtk_signal_connect(GTK_OBJECT(op2),"activate",GTK_SIGNAL_FUNC(ShowNames),NULL);
  gtk_signal_connect(GTK_OBJECT(op3),"activate",GTK_SIGNAL_FUNC(HistoriaClinica),NULL);

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(root_menu),menu);
  gtk_menu_bar_append(GTK_MENU_BAR(menu_bar),root_menu);

  root_menu=gtk_menu_item_new_with_label("AYUDA");
  gtk_signal_connect(GTK_OBJECT(root_menu),"activate",GTK_SIGNAL_FUNC(AcercaDe),NULL);
  gtk_menu_bar_append(GTK_MENU_BAR(menu_bar),root_menu);


  //sub3
  root_menu=gtk_menu_item_new_with_label("ACERCA DE...");
  gtk_signal_connect(GTK_OBJECT(root_menu),"activate",GTK_SIGNAL_FUNC(AcercaDe),NULL);
  gtk_menu_bar_append(GTK_MENU_BAR(menu_bar),root_menu);

  //fin del menu

  /***********************************************************************/
  imagen2 = gtk_image_new_from_file("busca.jpg");
  verticalbox = gtk_vbox_new(FALSE,5);
  box=gtk_vbox_new(TRUE,5);
  box1=gtk_hbox_new(TRUE,5);
  box2=gtk_hbox_new(TRUE,5);
  box3=gtk_hbox_new(TRUE,5);
  box4=gtk_hbox_new(TRUE,5);
  box5=gtk_hbox_new(FALSE,5);
  box6=gtk_hbox_new(FALSE,5);
  box7=gtk_hbox_new(FALSE,5);
  //aux=gtk_hbox_new(TRUE,5);

  entrybox = gtk_entry_new();
  //datos.entrybox=entrybox;
  //box = gtk_hbox_new(TRUE,5);

  label = gtk_label_new("Nombre Completo Del Paciente:");
  gtk_box_pack_start(GTK_BOX(box5),label,TRUE,TRUE,0);
  entrybox = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(box5),entrybox,TRUE,TRUE,0);
  datos.entrybox=entrybox;
  button = AddButton1(box5,"Buscar",/*BuscaPaciente*/ShowNames,&cosa); //////////////////////////////////////////////////////////////////////////////////////////

  label = gtk_label_new("Nombre Completo Del Doctor:  ");
  gtk_box_pack_start(GTK_BOX(box6),label,TRUE,TRUE,0);
  entrybox = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(box6),entrybox,TRUE,TRUE,0);
  datos.entrybox=entrybox;
  button = AddButton1(box6,"Buscar",/*BuscaDoctor*/ShowNames,&cosa); //////////////////////////////////////////////////////////////////////////////////////////

  label = gtk_label_new("Especialidad:                             ");
  gtk_box_pack_start(GTK_BOX(box7),label,TRUE,TRUE,0);
  entrybox = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(box7),entrybox,TRUE,TRUE,0);
  datos.entrybox=entrybox;
  button = AddButton1(box7,"Buscar",/*BuscaEspecialidad*/ShowNames,&cosa); //////////////////////////////////////////////////////////////////////////////////////////

  // gtk_box_pack_start(GTK_BOX(box),box4,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(box),box1,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box),box2,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box),box3,TRUE,TRUE,0);

  imagen = gtk_image_new_from_file("jeje2.jpg");
  gtk_box_pack_start(GTK_BOX(verticalbox),imagen,FALSE,TRUE,0);

  gtk_box_pack_start(GTK_BOX(verticalbox),menu_bar,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(verticalbox),imagen2,TRUE,TRUE,0);

  //gtk_box_pack_start(GTK_BOX(verticalbox),label,FALSE,FALSE,0);

  gtk_box_pack_start(GTK_BOX(verticalbox),box,FALSE,FALSE,5);
  gtk_box_pack_start(GTK_BOX(verticalbox),box5,TRUE,TRUE,5);
  gtk_box_pack_start(GTK_BOX(verticalbox),box6,TRUE,TRUE,5);
  gtk_box_pack_start(GTK_BOX(verticalbox),box7,TRUE,TRUE,5);
  box7=gtk_hbox_new(TRUE,2);
  button = AddButton1(box7,"Crear Nuevo Paciente",InsertaPV,&cosa);
  button = AddButton1(box7,"Crear Nuevo Doctor",InsertaDV,&cosa);
  gtk_box_pack_start(GTK_BOX(verticalbox),box7,TRUE,TRUE,0);

  gtk_signal_connect(GTK_OBJECT(cosa.window),"destroy",GTK_SIGNAL_FUNC(StopTheApp),&cosa);

  gtk_container_add(GTK_CONTAINER(cosa.window),verticalbox);
  gtk_widget_show_all(cosa.window);
  gtk_main();

  return 0;
}


GtkWidget *AddButton1(GtkWidget *theBox, const gchar *buttonText, gpointer CallBackFunction, tipowidget *EntryBox)
{
  GtkWidget *button;
  button = gtk_button_new_with_label(buttonText);
  gtk_box_pack_start(GTK_BOX(theBox),button,FALSE,TRUE,5);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(CallBackFunction),EntryBox);
  gtk_widget_show(button);
  return button;
}

GtkWidget *AddButton2(GtkWidget *theBox, const gchar *buttonText, gpointer CallBackFunction, GtkWidget *Cancelar)
{
  GtkWidget *button;
  button = gtk_button_new_with_label(buttonText);
  gtk_box_pack_start(GTK_BOX(theBox),button,FALSE,TRUE,5);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(CallBackFunction), Cancelar);
  gtk_widget_show(button);
  return button;
}


void AcercaDe(GtkWidget *window, gpointer data)
{
  GtkWidget *window1;
  GtkWidget *verticalbox,*uno;
  GtkWidget *imagen;

  imagen = gtk_image_new_from_file("mediana.jpg");

  uno= gtk_vbox_new(TRUE,5);
  verticalbox=gtk_vbox_new(TRUE,5);

  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window1),400,200);
  gtk_window_move(GTK_WINDOW(window1),405,160);
  gtk_container_border_width(GTK_CONTAINER(window1),5);
  gtk_window_set_title(GTK_WINDOW(window1),"Desarrolladores");

  gtk_box_pack_start(GTK_BOX(uno),imagen,TRUE,TRUE,0);

  gtk_box_pack_start(GTK_BOX(verticalbox),uno,TRUE,TRUE,0);

  gtk_container_add(GTK_CONTAINER(window1),verticalbox);
  gtk_widget_show_all(window1);
}


void StopTheApp(GtkWidget *window, gpointer data)
{
  FILE *doc;
  tipowidget *dato=(tipowidget *)data;
  doc=fopen("doctores.txt","wt");
  fclose(doc);
  escribirdoc(dato->dinicio);
  BorraPac(dato->pinicio);
  BorraDoc(dato->dinicio);
  gtk_main_quit();
}

void BorraDoc(tipodoctores *inicio)
{
  if(inicio!=NULL)
    {
      BorraDoc(inicio->izq);
      BorraDoc(inicio->der);
      free(inicio);
    }
}

void BorraPac(tipopacientes *inicio)
{
  if(inicio!=NULL)
    {
    BorraPac(inicio->izq);
    BorraPac(inicio->der);
    free(inicio);
    }
}

void ShowNames(GtkButton *button, gpointer data)
{
  g_print("Bajo\nGaby\nHalabe\n");
}

void InsertaDV(GtkWidget *window, gpointer data)
{
  tipowidget *datos=(tipowidget *) data;
  GtkWidget *window1,*label,*cajarb,*button,*cajarb2;
  GtkWidget *verticalbox, *horizontalbox, *box[10],*imagen, *cajachkb1,*cajachkb2, *bas;
  int i;
  char semana[7][10];

  verticalbox=gtk_vbox_new(FALSE,5);
  horizontalbox=gtk_hbox_new(TRUE,5);
  for(i=0;i<=8;i++)
    {
      datos->entrybox[i] = gtk_entry_new();
      box[i] = gtk_hbox_new(TRUE,5);
    }
  cajachkb1= gtk_vbox_new(TRUE,5);
  cajachkb2= gtk_vbox_new(TRUE,5);
  bas=gtk_hbox_new(TRUE,5);

  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window1),500,200);
  gtk_window_move(GTK_WINDOW(window1),555,170);
  gtk_container_border_width(GTK_CONTAINER(window1),5);
  gtk_window_set_title(GTK_WINDOW(window1),"Inserta Doctor");
  datos->window=window1;

  label = gtk_label_new("Nombre del Doctor:");
  gtk_box_pack_start(GTK_BOX(box[0]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[0]),datos->entrybox[0],TRUE,TRUE,0);

  label = gtk_label_new("Especialidad 1:");
  gtk_box_pack_start(GTK_BOX(box[1]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[1]),datos->entrybox[1],TRUE,TRUE,0);

  label = gtk_label_new("Especialidad 2:");
  gtk_box_pack_start(GTK_BOX(box[2]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[2]),datos->entrybox[2],TRUE,TRUE,0);

  label = gtk_label_new("Telefono Urgencias:");
  gtk_box_pack_start(GTK_BOX(box[3]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[3]),datos->entrybox[3],TRUE,TRUE,0);

  label = gtk_label_new("Telefono Personal:");
  gtk_box_pack_start(GTK_BOX(box[4]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[4]),datos->entrybox[4],TRUE,TRUE,0);

  label = gtk_label_new("Dirección:");
  gtk_box_pack_start(GTK_BOX(box[5]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[5]),datos->entrybox[5],TRUE,TRUE,0);

  label = gtk_label_new("Consultorio:");
  gtk_box_pack_start(GTK_BOX(box[6]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[6]),datos->entrybox[6],TRUE,TRUE,0);

  strcpy(semana[0],"Lunes");
  strcpy(semana[1],"Martes");
  strcpy(semana[2],"Miercoles");
  strcpy(semana[3],"Jueves");
  strcpy(semana[4],"Viernes");
  strcpy(semana[5],"Sabado");
  strcpy(semana[6],"Domingo");

  label = gtk_label_new("Días de Consulta:");
  gtk_box_pack_start(GTK_BOX(box[7]),label,TRUE,TRUE,0);

  for(i=0;i<4;i++){
    datos->chkb[i]=gtk_check_button_new_with_label(semana[i]);
    gtk_box_pack_start(GTK_BOX(cajachkb1),datos->chkb[i],TRUE,TRUE,0);
  }
  for(i=4;i<7;i++){
    datos->chkb[i]=gtk_check_button_new_with_label(semana[i]);
    gtk_box_pack_start(GTK_BOX(cajachkb2),datos->chkb[i],TRUE,TRUE,0);
  }


  gtk_box_pack_start(GTK_BOX(bas),cajachkb1,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(bas),cajachkb2,TRUE,TRUE,0);

  gtk_box_pack_start(GTK_BOX(box[7]),bas,TRUE,TRUE,0);

  cajarb=gtk_hbox_new(TRUE,0);
  cajarb2=gtk_hbox_new(TRUE,0);

  label = gtk_label_new("Horario:");
  gtk_box_pack_start(GTK_BOX(box[8]),label,TRUE,TRUE,0);

  datos->rb[0]=gtk_radio_button_new_with_label(NULL,"06-16");
  gtk_box_pack_start(GTK_BOX(cajarb),datos->rb[0],FALSE,FALSE,0);

  datos->rb[1]=gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(datos->rb[0])),"14-00");
  gtk_box_pack_start(GTK_BOX(cajarb),datos->rb[1],FALSE,FALSE,0);

  datos->rb[2]=gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(datos->rb[0])),"20-08");
  gtk_box_pack_start(GTK_BOX(cajarb),datos->rb[2],FALSE,FALSE,0);

  gtk_box_pack_start(GTK_BOX(cajarb2),cajarb,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(box[8]),cajarb2,TRUE,TRUE,0);


  imagen = gtk_image_new_from_file("nuevodoc.jpg");
  gtk_box_pack_start(GTK_BOX(verticalbox),imagen,FALSE,TRUE,0);

  for(i=0;i<=8;i++)
    gtk_box_pack_start(GTK_BOX(verticalbox),box[i],TRUE,TRUE,0);

  cajarb=gtk_hbox_new(TRUE,0);
  cajarb2=gtk_hbox_new(TRUE,0);

  label = gtk_label_new("Estatus:");
  gtk_box_pack_start(GTK_BOX(cajarb2),label,TRUE,TRUE,0);

  datos->rb[3]=gtk_radio_button_new_with_label(NULL,"Activo");
  gtk_box_pack_start(GTK_BOX(cajarb),datos->rb[3],FALSE,FALSE,0);

  datos->rb[4]=gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(datos->rb[3])),"Inactivo");
  gtk_box_pack_start(GTK_BOX(cajarb),datos->rb[4],FALSE,FALSE,0);

  gtk_box_pack_start(GTK_BOX(cajarb2),cajarb,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(verticalbox),cajarb2,TRUE,TRUE,0);

  button = gtk_button_new_with_label("Guardar Doctor");
  gtk_box_pack_start(GTK_BOX(horizontalbox),button,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(ADoctor),datos);
  gtk_widget_show(button);
  button=AddButton2(horizontalbox,"Cancelar",Cancelar,window1);

  gtk_box_pack_start(GTK_BOX(verticalbox),horizontalbox,TRUE,TRUE,0);

  gtk_container_add(GTK_CONTAINER(window1),verticalbox);
  gtk_widget_show_all(window1);
}

void ADoctor(GtkWidget *window, gpointer data)
{
  tipowidget *datos=(tipowidget *) data;
  tipodoctores *nuevo=(tipodoctores *)malloc(sizeof(tipodoctores)),*avanza;
  const gchar *text;
  char texto[200],semana[7][10];
  int i;


  //Dialog Esta seguro?????
  GtkWidget *dialog,*hbox,*image;
  gint respuesta;
  dialog=gtk_dialog_new_with_buttons("WARNING",GTK_WINDOW(datos->window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
  gtk_dialog_set_has_separator(GTK_DIALOG(dialog),FALSE);

  image=gtk_image_new_from_file("estaseguro.jpg");

  hbox=gtk_hbox_new(FALSE,5);
  gtk_container_set_border_width(GTK_CONTAINER(hbox),0);
  gtk_box_pack_start_defaults(GTK_BOX(hbox),image);


  gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(dialog)->vbox),hbox);
  gtk_widget_show_all(dialog);

  respuesta=gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
  //Termina Dialog Esta Seguro?????


  if(respuesta==-5){
    strcpy(semana[0],"Lunes");
    strcpy(semana[1],"Martes");
    strcpy(semana[2],"Miercoles");
    strcpy(semana[3],"Jueves");
    strcpy(semana[4],"Viernes");
    strcpy(semana[5],"Sabado");
    strcpy(semana[6],"Domingo");

    text=gtk_entry_get_text(GTK_ENTRY(datos->entrybox[0]));
    strcpy(texto,text);
    g_print("%s\n",texto);
    strcpy(nuevo->NombreD,texto);
    text=gtk_entry_get_text(GTK_ENTRY(datos->entrybox[1]));
    strcpy(texto,text);
    g_print("%s\n",texto);
    strcpy(nuevo->Esp1,texto);
    text=gtk_entry_get_text(GTK_ENTRY(datos->entrybox[2]));
    strcpy(texto,text);
    g_print("%s\n",texto);
    strcpy(nuevo->Esp2,texto);
    text=gtk_entry_get_text(GTK_ENTRY(datos->entrybox[3]));
    strcpy(texto,text);
    g_print("%s\n",texto);
    strcpy(nuevo->TelU,texto);
    text=gtk_entry_get_text(GTK_ENTRY(datos->entrybox[4]));
    strcpy(texto,text);
    g_print("%s\n",texto);
    strcpy(nuevo->TelN,texto);
    text=gtk_entry_get_text(GTK_ENTRY(datos->entrybox[5]));
    strcpy(texto,text);
    g_print("%s\n",texto);
    strcpy(nuevo->DireccionD,texto);
    text=gtk_entry_get_text(GTK_ENTRY(datos->entrybox[6]));
    strcpy(texto,text);
    g_print("%s\n",texto);
    strcpy(nuevo->Consultorio,texto);
    for(i=0;i<7;i++)
      nuevo->dias[i]=0;
    for(i=0;i<7;i++){
      if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(datos->chkb[i])))
	nuevo->dias[i]=1;
      else
	nuevo->dias[i]=0;
    }
    for(i=0;i<7;i++){
      if(nuevo->dias[i]==1)
	g_print("Si: %s\n",semana[i]);
      else
	g_print("No: %s\n",semana[i]);
    }
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(datos->rb[0])))
      strcpy(nuevo->Horario,"06-16");
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(datos->rb[1])))
      strcpy(nuevo->Horario,"14-00");
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(datos->rb[2])))
      strcpy(nuevo->Horario,"22-08");
    g_print("%s\n",nuevo->Horario);
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(datos->rb[3])))
      nuevo->Estatus=1;
    else
      nuevo->Estatus=0;
    if(nuevo->Estatus==1)
      g_print("Activo\n");
    else
      g_print("Inactivo\n");
    nuevo->izq=NULL;
    nuevo->der=NULL;
    avanza=datos->dinicio;
    if(datos->dinicio==NULL)
      datos->dinicio=nuevo;
    else{
      while(avanza!=NULL){
	if(strcmp(nuevo->NombreD,avanza->NombreD)>0){
	  if(avanza->der!=NULL)
	    avanza=avanza->der;
	  else{
	    avanza->der=nuevo;
	    gtk_widget_destroy(datos->window);
	    return;
	  }
	}
	if(strcmp(nuevo->NombreD,avanza->NombreD)<=0){
	  if(avanza->izq!=NULL)
	    avanza=avanza->izq;
	  else{
	    avanza->izq=nuevo;
	    gtk_widget_destroy(datos->window);
	    return;
	  }
	}
      }
    }
  }
  if(respuesta== -5)
    {
      gtk_widget_destroy(datos->window);
    }
}

void InsertaPV(GtkWidget *window, gpointer data)
{
  tipowidget *datos=(tipowidget *)data;
  GtkWidget *window1,*label,*imagen;
  GtkWidget *verticalbox, *horizontalbox,*box[10],*button,*boxfecha;
  GtkWidget *cajarb;
  int i;

  verticalbox=gtk_vbox_new(FALSE,5);
  horizontalbox=gtk_hbox_new(TRUE,5);
  boxfecha=gtk_hbox_new(FALSE,0);
  for(i=0;i<=10;i++)
    {
      datos->entrybox[i] = gtk_entry_new();
      box[i] = gtk_hbox_new(TRUE,5);
    }

  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window1),500,200);
  gtk_window_move(GTK_WINDOW(window1),560,170);
  gtk_container_border_width(GTK_CONTAINER(window1),5);
  gtk_window_set_title(GTK_WINDOW(window1),"Inserta Paciente");
  datos->window=window1;

  label = gtk_label_new("Nombre del Paciente:");
  gtk_box_pack_start(GTK_BOX(box[0]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[0]),datos->entrybox[0],TRUE,TRUE,0);

  label = gtk_label_new("Dirección:");
  gtk_box_pack_start(GTK_BOX(box[1]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[1]),datos->entrybox[1],TRUE,TRUE,0);

  label = gtk_label_new("Teléfono:");
  gtk_box_pack_start(GTK_BOX(box[2]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[2]),datos->entrybox[2],TRUE,TRUE,0);

  label = gtk_label_new("Alergias:");
  gtk_box_pack_start(GTK_BOX(box[3]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[3]),datos->entrybox[3],TRUE,TRUE,0);

  label = gtk_label_new("Tipo de Sangre:");
  gtk_box_pack_start(GTK_BOX(box[4]),label,TRUE,TRUE,0);
  datos->combo=gtk_combo_box_new_text();
  gtk_combo_box_append_text(GTK_COMBO_BOX(datos->combo),"A+");
  gtk_combo_box_append_text(GTK_COMBO_BOX(datos->combo),"A-");
  gtk_combo_box_append_text(GTK_COMBO_BOX(datos->combo),"B+");
  gtk_combo_box_append_text(GTK_COMBO_BOX(datos->combo),"B-");
  gtk_combo_box_append_text(GTK_COMBO_BOX(datos->combo),"AB+");
  gtk_combo_box_append_text(GTK_COMBO_BOX(datos->combo),"AB-");
  gtk_combo_box_append_text(GTK_COMBO_BOX(datos->combo),"O+");
  gtk_combo_box_append_text(GTK_COMBO_BOX(datos->combo),"O-");

  gtk_box_pack_start(GTK_BOX(box[4]),datos->combo,TRUE,TRUE,0);

  label = gtk_label_new("Padecimientos Crónicos:");
  gtk_box_pack_start(GTK_BOX(box[5]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[5]),datos->entrybox[4],TRUE,TRUE,0);

  label = gtk_label_new("Estatura (m):");
  gtk_box_pack_start(GTK_BOX(box[6]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[6]),datos->entrybox[5],TRUE,TRUE,0);

  label = gtk_label_new("Género:");
  gtk_box_pack_start(GTK_BOX(box[7]),label,TRUE,TRUE,0);

  cajarb=gtk_hbox_new(FALSE,5);

  datos->rb[0]=gtk_radio_button_new_with_label(NULL,"Femenino");
  gtk_box_pack_start(GTK_BOX(cajarb),datos->rb[0],FALSE,FALSE,0);

  datos->rb[1]=gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(datos->rb[0])),"Masculino");
  gtk_box_pack_start(GTK_BOX(cajarb),datos->rb[1],FALSE,FALSE,0);

  gtk_box_pack_start(GTK_BOX(box[7]),cajarb,FALSE,FALSE,0);

  imagen = gtk_image_new_from_file("nuevopaci.jpg");
  gtk_box_pack_start(GTK_BOX(verticalbox),imagen,FALSE,TRUE,0);

  label=gtk_label_new("Fecha De Nacimiento:");
  datos->calendario=gtk_calendar_new();
  gtk_box_pack_start(GTK_BOX(box[8]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[8]),datos->calendario,TRUE,TRUE,0);

  for(i=0;i<=8;i++)
    gtk_box_pack_start(GTK_BOX(verticalbox),box[i],TRUE,TRUE,0);

  button = gtk_button_new_with_label("Guardar Paciente");
  gtk_box_pack_start(GTK_BOX(horizontalbox),button,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(APaciente),datos);
  gtk_widget_show(button);
  button=AddButton2(horizontalbox,"Cancelar",Cancelar, window1);

  gtk_box_pack_start(GTK_BOX(verticalbox),horizontalbox,TRUE,TRUE,0);
  gtk_container_add(GTK_CONTAINER(window1),verticalbox);
  gtk_widget_show_all(window1);

}

void APaciente(GtkWidget *window, gpointer data)
{
  time_t crudo;
  struct tm *cocinado;
  tipowidget *datos=(tipowidget *) data;
  tipopacientes *nuevo=(tipopacientes *)malloc(sizeof(tipopacientes)),*avanza;
  const gchar *text;
  char texto[200],cadena[30];
  int ano,mes,dia,fdia,fmes,fano;
  guint year,month,day;

  //Dialog Esta seguro?????
  GtkWidget *dialog,*hbox,*image;
  gint respuesta;
  dialog=gtk_dialog_new_with_buttons("WARNING",GTK_WINDOW(datos->window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
  gtk_dialog_set_has_separator(GTK_DIALOG(dialog),FALSE);

  image=gtk_image_new_from_file("estaseguro.jpg");

  hbox=gtk_hbox_new(FALSE,5);
  gtk_container_set_border_width(GTK_CONTAINER(hbox),0);
  gtk_box_pack_start_defaults(GTK_BOX(hbox),image);

  gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(dialog)->vbox),hbox);
  gtk_widget_show_all(dialog);

  respuesta=gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
  //Termina Dialog Esta Seguro?????

  if(respuesta==-5){
    text=gtk_entry_get_text(GTK_ENTRY(datos->entrybox[0]));
    strcpy(texto,text);
    g_print("%s\n",texto);
    strcpy(nuevo->NombreP,texto);
    text=gtk_entry_get_text(GTK_ENTRY(datos->entrybox[1]));
    strcpy(texto,text);
    g_print("%s\n",texto);
    strcpy(nuevo->DireccionP,texto);
    text=gtk_entry_get_text(GTK_ENTRY(datos->entrybox[2]));
    strcpy(texto,text);
    g_print("%s\n",texto);
    strcpy(nuevo->TelP,texto);
    text=gtk_entry_get_text(GTK_ENTRY(datos->entrybox[3]));
    strcpy(texto,text);
    g_print("%s\n",texto);
    strcpy(nuevo->Alergias,texto);
    text=gtk_entry_get_text(GTK_ENTRY(datos->entrybox[4]));
    strcpy(texto,text);
    g_print("%s\n",texto);
    strcpy(nuevo->PadecimientosC,texto);
    text=gtk_entry_get_text(GTK_ENTRY(datos->entrybox[5]));
    strcpy(texto,text);
    g_print("%s\n",texto);
    sscanf(texto,"%f",&nuevo->Estatura);
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(datos->rb[0])))
      strcpy(nuevo->Sexo,"Femenino");
    else
      strcpy(nuevo->Sexo,"Masculino");
    g_print("%s\n",nuevo->Sexo);
    switch(gtk_combo_box_get_active(GTK_COMBO_BOX(datos->combo))){
    case 0:strcpy(nuevo->TipoSangre,"A+");
      break;
    case 1:strcpy(nuevo->TipoSangre,"A-");
      break;
    case 2:strcpy(nuevo->TipoSangre,"B+");
      break;
    case 3:strcpy(nuevo->TipoSangre,"B-");
      break;
    case 4:strcpy(nuevo->TipoSangre,"AB+");
      break;
    case 5:strcpy(nuevo->TipoSangre,"AB-");
      break;
    case 6:strcpy(nuevo->TipoSangre,"O+");
      break;
    case 7:strcpy(nuevo->TipoSangre,"O-");
      break;
    }
    g_print("%s\n",nuevo->TipoSangre);
    gtk_calendar_get_date(GTK_CALENDAR(datos->calendario),&year,&month,&day);
    dia=day;
    mes=++month;
    ano=year;
    sprintf(nuevo->FechaN,"%i/%i/%i",dia,mes,ano);
    time(&crudo);
    cocinado=localtime(&crudo);
    strftime(cadena,sizeof(cadena),"%Y-%m-%d",cocinado);
    sscanf(cadena,"%i-%i-%i",&fano,&fmes,&fdia);
    nuevo->Edad=fano-ano;
    if(mes>fmes)
      nuevo->Edad--;
    if(mes==fmes&&dia>fdia)
      nuevo->Edad--;
    g_print("%i\n",nuevo->Edad);
    nuevo->izq=NULL;
    nuevo->der=NULL;
    if(datos->pinicio==NULL)
      datos->pinicio=nuevo;
    else{
      avanza=datos->pinicio;
      while(avanza!=NULL){
	if(strcmp(nuevo->NombreP,avanza->NombreP)>0){
	  if(avanza->der!=NULL)
	    avanza=avanza->der;
	  else{
	    avanza->der=nuevo;
	    gtk_widget_destroy(datos->window);
	    return;
	  }
	}
	if(strcmp(nuevo->NombreP,avanza->NombreP)<=0)
	  {
	    if(avanza->izq!=NULL)
	      avanza=avanza->izq;
	    else{
	      avanza->izq=nuevo;
	      gtk_widget_destroy(datos->window);
	      return;
	    }
	  }
      }
    }
  }
  if(respuesta== -5)
    {
      gtk_widget_destroy(datos->window);
    }
}
void ModificarP(GtkWidget *window, gpointer data)
{
  tipowidget *datos=(tipowidget *)data;
  GtkWidget *window1,*label, *imagen;
  GtkWidget *verticalbox, *horizontalbox,*box[9],*button;
  GtkWidget *rb1, *rb2;
  GtkWidget *cajarb;
  GtkWidget *calendario;
  int i;

  verticalbox=gtk_vbox_new(FALSE,5);
  horizontalbox=gtk_hbox_new(TRUE,5);
  for(i=0;i<=8;i++)
    {
      datos->entrybox[i] = gtk_entry_new();
      box[i] = gtk_hbox_new(TRUE,5);
    }

  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window1),500,200);
  gtk_window_move(GTK_WINDOW(window1),560,270);
  gtk_container_border_width(GTK_CONTAINER(window1),5);
  gtk_window_set_title(GTK_WINDOW(window1),"Modificar Paciente");

  label = gtk_label_new("Nombre del Paciente:");
  gtk_box_pack_start(GTK_BOX(box[0]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[0]),datos ->entrybox[0],TRUE,TRUE,0);
  button=AddButton1(box[0],"Buscar",ShowNames,datos);

  label = gtk_label_new("Dirección:");
  gtk_box_pack_start(GTK_BOX(box[1]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[1]),datos->entrybox[1],TRUE,TRUE,0);

  label = gtk_label_new("Teléfono:");
  gtk_box_pack_start(GTK_BOX(box[2]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[2]),datos->entrybox[2],TRUE,TRUE,0);


  label = gtk_label_new("Alergias:");
  gtk_box_pack_start(GTK_BOX(box[3]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[3]),datos->entrybox[3],TRUE,TRUE,0);

  label = gtk_label_new("Tipo de Sangre:");
  gtk_box_pack_start(GTK_BOX(box[4]),label,TRUE,TRUE,0);
  datos->combo=gtk_combo_box_new_text();
  gtk_combo_box_append_text(GTK_COMBO_BOX(datos->combo),"A+");
  gtk_combo_box_append_text(GTK_COMBO_BOX(datos->combo),"A-");
  gtk_combo_box_append_text(GTK_COMBO_BOX(datos->combo),"B+");
  gtk_combo_box_append_text(GTK_COMBO_BOX(datos->combo),"B-");
  gtk_combo_box_append_text(GTK_COMBO_BOX(datos->combo),"AB+");
  gtk_combo_box_append_text(GTK_COMBO_BOX(datos->combo),"AB-");
  gtk_combo_box_append_text(GTK_COMBO_BOX(datos->combo),"O+");
  gtk_combo_box_append_text(GTK_COMBO_BOX(datos->combo),"O-");

  gtk_box_pack_start(GTK_BOX(box[4]),datos->combo,TRUE,TRUE,0);

  label = gtk_label_new("Padecimientos Crónicos:");
  gtk_box_pack_start(GTK_BOX(box[5]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[5]),datos->entrybox[4],TRUE,TRUE,0);

  label = gtk_label_new("Estatura (m):");
  gtk_box_pack_start(GTK_BOX(box[6]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[6]),datos->entrybox[5],TRUE,TRUE,0);

  label = gtk_label_new("Género:");
  gtk_box_pack_start(GTK_BOX(box[7]),label,TRUE,TRUE,0);

  cajarb=gtk_hbox_new(FALSE,5);

  rb1=gtk_radio_button_new_with_label(NULL,"Femenino");
  gtk_box_pack_start(GTK_BOX(cajarb),rb1,FALSE,FALSE,0);
  gtk_signal_connect(GTK_OBJECT(rb1),"toggled",GTK_SIGNAL_FUNC(ShowNames),"1");

  rb2=gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(rb1)),"Masculino");
  gtk_box_pack_start(GTK_BOX(cajarb),rb2,FALSE,FALSE,0);
  gtk_signal_connect(GTK_OBJECT(rb2),"toggled",GTK_SIGNAL_FUNC(ShowNames),"2");

  gtk_box_pack_start(GTK_BOX(box[7]),cajarb,FALSE,FALSE,0);

  label=gtk_label_new("Fecha De Nacimiento:");
  calendario=gtk_calendar_new();
  gtk_box_pack_start(GTK_BOX(box[8]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[8]),calendario,TRUE,TRUE,0);

  imagen = gtk_image_new_from_file("modificar.jpg");
  gtk_box_pack_start(GTK_BOX(verticalbox),imagen,FALSE,TRUE,0);

  for(i=0;i<=8;i++)
    gtk_box_pack_start(GTK_BOX(verticalbox),box[i],TRUE,TRUE,0);

  button=AddButton1(horizontalbox,"Guardar Datos", ShowNames, datos);
  button=AddButton2(horizontalbox,"Cancelar", Cancelar, window1);

  gtk_box_pack_start(GTK_BOX(verticalbox),horizontalbox,TRUE,TRUE,0);
  gtk_container_add(GTK_CONTAINER(window1),verticalbox);
  gtk_widget_show_all(window1);
}

void ModificarD(GtkWidget *window, gpointer data)
{
  tipowidget *datos=(tipowidget *)data;
  GtkWidget *window1,*label, *imagen;
  GtkWidget *verticalbox, *horizontalbox,*box[9],*button,*cajachkb1,*cajachkb2,*bas;
  GtkWidget *rb1, *rb2;
  GtkWidget *cajarb, *cajarb2;
  int i;

  verticalbox=gtk_vbox_new(FALSE,5);
  horizontalbox=gtk_hbox_new(TRUE,5);

  imagen = gtk_image_new_from_file("modificar.jpg");
  gtk_box_pack_start(GTK_BOX(verticalbox),imagen,FALSE,TRUE,0);

  for(i=0;i<=8;i++)
    {
      datos->entrybox[i] = gtk_entry_new();
      box[i] = gtk_hbox_new(TRUE,5);
    }

  cajachkb1= gtk_vbox_new(TRUE,5);
  cajachkb2= gtk_vbox_new(TRUE,5);
  bas=gtk_hbox_new(TRUE,5);

  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window1),500,200);
  gtk_window_move(GTK_WINDOW(window1),560,270);
  gtk_container_border_width(GTK_CONTAINER(window1),5);
  gtk_window_set_title(GTK_WINDOW(window1),"Modificar Doctor");

  label = gtk_label_new("Nombre del Doctor:");
  gtk_box_pack_start(GTK_BOX(box[0]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[0]),datos ->entrybox[0],TRUE,TRUE,0);
  button=AddButton1(box[0],"Buscar",ShowNames,datos);

  label = gtk_label_new("Especialidad 1:");
  gtk_box_pack_start(GTK_BOX(box[1]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[1]),datos->entrybox[1],TRUE,TRUE,0);

  label = gtk_label_new("Especialidad 2:");
  gtk_box_pack_start(GTK_BOX(box[2]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[2]),datos->entrybox[2],TRUE,TRUE,0);

  label = gtk_label_new("Telefono Urgencias:");
  gtk_box_pack_start(GTK_BOX(box[3]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[3]),datos->entrybox[3],TRUE,TRUE,0);

  label = gtk_label_new("Telefono Personal:");
  gtk_box_pack_start(GTK_BOX(box[4]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[4]),datos->entrybox[4],TRUE,TRUE,0);

  label = gtk_label_new("Dirección:");
  gtk_box_pack_start(GTK_BOX(box[5]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[5]),datos->entrybox[5],TRUE,TRUE,0);

  label = gtk_label_new("Consultorio:");
  gtk_box_pack_start(GTK_BOX(box[6]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[6]),datos->entrybox[6],TRUE,TRUE,0);

  label = gtk_label_new("Días de Consulta:");
  gtk_box_pack_start(GTK_BOX(box[7]),label,TRUE,TRUE,0);
  datos->chkb[0]=gtk_check_button_new_with_label("Lunes");
  gtk_box_pack_start(GTK_BOX(cajachkb1),datos->chkb[0],TRUE,TRUE,0);
  datos->chkb[1]=gtk_check_button_new_with_label("Martes");
  gtk_box_pack_start(GTK_BOX(cajachkb1),datos->chkb[1],TRUE,TRUE,0);
  datos->chkb[2]=gtk_check_button_new_with_label("Miercoles");
  gtk_box_pack_start(GTK_BOX(cajachkb1),datos->chkb[2],TRUE,TRUE,0);
  datos->chkb[3]=gtk_check_button_new_with_label("Jueves");
  gtk_box_pack_start(GTK_BOX(cajachkb1),datos->chkb[3],TRUE,TRUE,0);
  datos->chkb[4]=gtk_check_button_new_with_label("Viernes");
  gtk_box_pack_start(GTK_BOX(cajachkb2),datos->chkb[4],TRUE,TRUE,0);
  datos->chkb[5]=gtk_check_button_new_with_label("Sabado");
  gtk_box_pack_start(GTK_BOX(cajachkb2),datos->chkb[5],TRUE,TRUE,0);
  datos->chkb[6]=gtk_check_button_new_with_label("Domingo");
  gtk_box_pack_start(GTK_BOX(cajachkb2),datos->chkb[6],TRUE,TRUE,0);

  gtk_box_pack_start(GTK_BOX(bas),cajachkb1,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(bas),cajachkb2,TRUE,TRUE,0);

  gtk_box_pack_start(GTK_BOX(box[7]),bas,TRUE,TRUE,0);

  cajarb=gtk_hbox_new(TRUE,0);
  cajarb2=gtk_hbox_new(TRUE,0);

  label = gtk_label_new("Horario:");
  gtk_box_pack_start(GTK_BOX(box[8]),label,TRUE,TRUE,0);

  rb1=gtk_radio_button_new_with_label(NULL,"06-16");
  gtk_box_pack_start(GTK_BOX(cajarb),rb1,FALSE,FALSE,0);
  gtk_signal_connect(GTK_OBJECT(rb1),"toggled",GTK_SIGNAL_FUNC(ShowNames),"1");

  rb2=gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(rb1)),"14-00");
  gtk_box_pack_start(GTK_BOX(cajarb),rb2,FALSE,FALSE,0);
  gtk_signal_connect(GTK_OBJECT(rb2),"toggled",GTK_SIGNAL_FUNC(ShowNames),"2");

  rb2=gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(rb1)),"20-08");
  gtk_box_pack_start(GTK_BOX(cajarb),rb2,FALSE,FALSE,0);
  gtk_signal_connect(GTK_OBJECT(rb2),"toggled",GTK_SIGNAL_FUNC(ShowNames),"3");

  gtk_box_pack_start(GTK_BOX(cajarb2),cajarb,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(box[8]),cajarb2,TRUE,TRUE,0);

  for(i=0;i<=8;i++)
    gtk_box_pack_start(GTK_BOX(verticalbox),box[i],TRUE,TRUE,0);

  cajarb=gtk_hbox_new(TRUE,0);
  cajarb2=gtk_hbox_new(TRUE,0);

  label = gtk_label_new("Estatus:");
  gtk_box_pack_start(GTK_BOX(cajarb2),label,TRUE,TRUE,0);

  datos->rb[0]=gtk_radio_button_new_with_label(NULL,"Activo");
  gtk_box_pack_start(GTK_BOX(cajarb),rb1,FALSE,FALSE,0);
  gtk_signal_connect(GTK_OBJECT(rb1),"toggled",GTK_SIGNAL_FUNC(ShowNames),"1");

  datos->rb[1]=gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(rb1)),"Inactivo");
  gtk_box_pack_start(GTK_BOX(cajarb),rb2,FALSE,FALSE,0);
  gtk_signal_connect(GTK_OBJECT(rb2),"toggled",GTK_SIGNAL_FUNC(ShowNames),"2");

  gtk_box_pack_start(GTK_BOX(cajarb2),cajarb,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(verticalbox),cajarb2,TRUE,TRUE,0);

  button = gtk_button_new_with_label("Guardar Doctor");
  gtk_box_pack_start(GTK_BOX(horizontalbox),button,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(ShowNames), datos);
  gtk_widget_show(button);
  button=AddButton2(horizontalbox,"Cancelar", Cancelar, window1);

  gtk_box_pack_start(GTK_BOX(verticalbox),horizontalbox,TRUE,TRUE,0);

  gtk_container_add(GTK_CONTAINER(window1),verticalbox);
  gtk_widget_show_all(window1);
}


void ModificarC(GtkWidget *window, gpointer data)
{
  tipowidget *datos=(tipowidget *)data;
  GtkWidget *window1,*label, *imagen;
  GtkWidget *verticalbox, *horizontalbox,*box[9],*button;
  int i;

  verticalbox=gtk_vbox_new(FALSE,5);
  horizontalbox=gtk_hbox_new(TRUE,5);

  imagen = gtk_image_new_from_file("modificar.jpg");
  gtk_box_pack_start(GTK_BOX(verticalbox),imagen,FALSE,TRUE,0);

  for(i=0;i<=8;i++)
    {
      datos->entrybox[i] = gtk_entry_new();
      box[i] = gtk_hbox_new(TRUE,5);
    }

  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window1),500,200);
  gtk_window_move(GTK_WINDOW(window1),560,270);
  gtk_container_border_width(GTK_CONTAINER(window1),5);
  gtk_window_set_title(GTK_WINDOW(window1),"Modificar Historia Clínica");

  label = gtk_label_new("Nombre del Paciente:");
  gtk_box_pack_start(GTK_BOX(box[0]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[0]),datos ->entrybox[0],TRUE,TRUE,0);
  button=AddButton1(box[0],"Buscar",ShowNames,datos);

  label = gtk_label_new("Fecha de Consulta:");
  gtk_box_pack_start(GTK_BOX(box[1]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[1]),datos->entrybox[1],TRUE,TRUE,0);

  label = gtk_label_new("Nombre del Doctor Tratante");
  gtk_box_pack_start(GTK_BOX(box[2]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[2]),datos->entrybox[2],TRUE,TRUE,0);

  label = gtk_label_new("Diágnostico:");
  gtk_box_pack_start(GTK_BOX(box[3]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[3]),datos->entrybox[3],TRUE,TRUE,0);

  label = gtk_label_new("Tratamiento:");
  gtk_box_pack_start(GTK_BOX(box[4]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[4]),datos->entrybox[4],TRUE,TRUE,0);

  label = gtk_label_new("Anotaciones:");
  gtk_box_pack_start(GTK_BOX(box[5]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[5]),datos->entrybox[5],TRUE,TRUE,0);

  for(i=0;i<=5;i++)
    gtk_box_pack_start(GTK_BOX(verticalbox),box[i],TRUE,TRUE,0);


  button = gtk_button_new_with_label("Guardar Doctor");
  gtk_box_pack_start(GTK_BOX(horizontalbox),button,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(ADoctor),datos);
  gtk_widget_show(button);
  button=AddButton2(horizontalbox,"Cancelar", Cancelar, window1);

  gtk_box_pack_start(GTK_BOX(verticalbox),horizontalbox,TRUE,TRUE,0);

  gtk_container_add(GTK_CONTAINER(window1),verticalbox);
  gtk_widget_show_all(window1);
}

void ListaDoc(GtkWidget *window, gpointer data)
{
  tipowidget *datos=(tipowidget *) data;
  GtkWidget *window1,*label,*rb1,*rb2,*cajarb,*button,*cajarb2;
  GtkWidget *verticalbox,*horizontalbox,*imagen;

  Imprimedoc(datos->dinicio);

  verticalbox=gtk_vbox_new(FALSE,5);
  horizontalbox=gtk_hbox_new(TRUE,5);

  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window1),500,200);
  gtk_window_move(GTK_WINDOW(window1),560,270);
  gtk_container_border_width(GTK_CONTAINER(window1),5);
  gtk_window_set_title(GTK_WINDOW(window1),"Lista de Doctores");

  imagen = gtk_image_new_from_file("listadoc.jpg");
  gtk_box_pack_start(GTK_BOX(verticalbox),imagen,FALSE,TRUE,0);

  cajarb=gtk_hbox_new(TRUE,0);
  cajarb2=gtk_hbox_new(TRUE,0);

  label = gtk_label_new("Por Estatus:");
  gtk_box_pack_start(GTK_BOX(cajarb2),label,TRUE,TRUE,0);

  rb1=gtk_radio_button_new_with_label(NULL,"Activo");
  gtk_box_pack_start(GTK_BOX(cajarb),rb1,FALSE,FALSE,0);
  gtk_signal_connect(GTK_OBJECT(rb1),"toggled",GTK_SIGNAL_FUNC(ShowNames),"1");//func lista activo

  rb2=gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(rb1)),"Inactivo");
  gtk_box_pack_start(GTK_BOX(cajarb),rb2,FALSE,FALSE,0);
  gtk_signal_connect(GTK_OBJECT(rb2),"toggled",GTK_SIGNAL_FUNC(ShowNames),"2");//func lista inactivo

  gtk_box_pack_start(GTK_BOX(cajarb2),cajarb,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(verticalbox),cajarb2,TRUE,TRUE,0);

  button = gtk_button_new_with_label("Cerrar");
  gtk_box_pack_start(GTK_BOX(horizontalbox),button,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(Cancelar), window1);
  gtk_widget_show(button);

  gtk_box_pack_start(GTK_BOX(verticalbox),horizontalbox,TRUE,TRUE,0);

  gtk_container_add(GTK_CONTAINER(window1),verticalbox);
  gtk_widget_show_all(window1);
}

void Imprimedoc(tipodoctores *dinicio)
{
  g_print("\n\n");
  if(dinicio!=NULL)
    {
      Imprimedoc(dinicio->izq);
      g_print("%s\n%s\n%s\n%s\n%s\n%s\n%s\n",dinicio->NombreD,dinicio->Esp1,dinicio->Esp2,dinicio->TelU,dinicio->TelN,dinicio->DireccionD,dinicio->Consultorio);
      Imprimedoc(dinicio->der);
    }
}

void NuevaHC(GtkWidget *window, gpointer data)
{
  tipowidget *datos=(tipowidget *)data;
  GtkWidget *window1, *label, *imagen;
  GtkWidget *verticalbox, *horizontalbox,*box[6],*button;
  int i;

  verticalbox=gtk_vbox_new(FALSE,5);
  horizontalbox=gtk_hbox_new(TRUE,5);

  imagen = gtk_image_new_from_file("historia.jpg");
  gtk_box_pack_start(GTK_BOX(verticalbox),imagen,FALSE,TRUE,0);

  for(i=0;i<6;i++)
    {
      datos->entrybox[i] = gtk_entry_new();
      box[i] = gtk_hbox_new(TRUE,5);
    }

  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window1),500,200);
  gtk_window_move(GTK_WINDOW(window1),560,270);
  gtk_container_border_width(GTK_CONTAINER(window1),5);
  gtk_window_set_title(GTK_WINDOW(window1),"Nueva Historia Clínica");

  label = gtk_label_new("Nombre del Paciente:");
  gtk_box_pack_start(GTK_BOX(box[0]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[0]),datos ->entrybox[0],TRUE,TRUE,0);
  button=AddButton1(box[0],"Buscar",ShowNames, datos);

  label = gtk_label_new("Fecha de Consulta:");
  gtk_box_pack_start(GTK_BOX(box[1]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[1]),datos->entrybox[1],TRUE,TRUE,0);

  label = gtk_label_new("Nombre del Doctor Tratante");
  gtk_box_pack_start(GTK_BOX(box[2]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[2]),datos->entrybox[2],TRUE,TRUE,0);

  label = gtk_label_new("Diágnostico:");
  gtk_box_pack_start(GTK_BOX(box[3]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[3]),datos->entrybox[3],TRUE,TRUE,0);

  label = gtk_label_new("Tratamiento:");
  gtk_box_pack_start(GTK_BOX(box[4]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[4]),datos->entrybox[4],TRUE,TRUE,0);

  label = gtk_label_new("Anotaciones:");
  gtk_box_pack_start(GTK_BOX(box[5]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[5]),datos->entrybox[5],TRUE,TRUE,0);

  for(i=0;i<6;i++)
  gtk_box_pack_start(GTK_BOX(verticalbox),box[i],TRUE,TRUE,0);

  button = gtk_button_new_with_label("Guardar Doctor");
  gtk_box_pack_start(GTK_BOX(horizontalbox),button,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(ShowNames),datos);
  gtk_widget_show(button);
  button=AddButton2(horizontalbox,"Cancelar", Cancelar, window1);

  gtk_box_pack_start(GTK_BOX(verticalbox),horizontalbox,TRUE,TRUE,0);

  gtk_container_add(GTK_CONTAINER(window1),verticalbox);
  gtk_widget_show_all(window1);
}


void HistoriaClinica(GtkWidget *window, gpointer data)
{
  tipowidget *datos=(tipowidget *) data;
  GtkWidget *window1,*label, *entrybox,*button;
  GtkWidget *verticalbox,*horizontalbox,*imagen;

  verticalbox=gtk_vbox_new(FALSE,5);
  horizontalbox=gtk_hbox_new(TRUE,5);

  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window1),400,200);
  gtk_window_move(GTK_WINDOW(window1),560,270);
  gtk_container_border_width(GTK_CONTAINER(window1),5);
  gtk_window_set_title(GTK_WINDOW(window1),"HISTORIA CLÍNICA");

  imagen = gtk_image_new_from_file("historia.jpg");
  gtk_box_pack_start(GTK_BOX(verticalbox),imagen,FALSE,TRUE,0);

  entrybox=gtk_entry_new();
  label = gtk_label_new("Nombre del Paciente:");
  gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(horizontalbox),entrybox,TRUE,TRUE,0);
  button=AddButton1(horizontalbox,"Buscar", ShowNames,datos);

  button = gtk_button_new_with_label("Nueva Historia Clínica");
  gtk_box_pack_start(GTK_BOX(horizontalbox),button,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(NuevaHC),datos);
  gtk_widget_show(button);
  button=AddButton2(horizontalbox,"Cancelar",Cancelar,window1);

  gtk_box_pack_start(GTK_BOX(verticalbox),horizontalbox,TRUE,TRUE,0);

  gtk_container_add(GTK_CONTAINER(window1),verticalbox);
  gtk_widget_show_all(window1);
}


void NoHay(GtkWidget *window, gpointer data)//Mensaje cuando no se encuetra
{
  tipowidget *datos=(tipowidget *) data;
  GtkWidget *window1,*button;
  GtkWidget *verticalbox,*horizontalbox,*imagen;

  verticalbox=gtk_vbox_new(FALSE,5);
  horizontalbox=gtk_hbox_new(TRUE,5);

  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window1),400,200);
  gtk_window_move(GTK_WINDOW(window1),560,270);
  gtk_container_border_width(GTK_CONTAINER(window1),5);
  gtk_window_set_title(GTK_WINDOW(window1),"HISTORIA CLÍNICA");

  imagen = gtk_image_new_from_file("noencontrado.jpg");
  gtk_box_pack_start(GTK_BOX(verticalbox),imagen,FALSE,TRUE,0);
  button=AddButton1(verticalbox,"Aceptar",ShowNames,datos);

  gtk_container_add(GTK_CONTAINER(window1),verticalbox);
  gtk_widget_show_all(window1);
}



void Cancelar(GtkWidget *window, gpointer data)
{
  gtk_widget_destroy((data));
}


void EstaSeguro(GtkWidget window, gpointer data)
{
  tipowidget *datos=(tipowidget *) data;
  GtkWidget *window1,*button;
  GtkWidget *verticalbox,*horizontalbox,*imagen;

  verticalbox=gtk_vbox_new(FALSE,5);
  horizontalbox=gtk_hbox_new(TRUE,5);

  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window1),400,200);
  gtk_window_move(GTK_WINDOW(window1),560,270);
  gtk_container_border_width(GTK_CONTAINER(window1),5);
  gtk_window_set_title(GTK_WINDOW(window1),"WARNING");

  imagen = gtk_image_new_from_file("estaseguro.jpg");
  gtk_box_pack_start(GTK_BOX(verticalbox),imagen,FALSE,TRUE,0);
  button=AddButton1(verticalbox,"Aceptar",APaciente,datos);
  button=AddButton2(verticalbox,"Cancelar",Cancelar,window1);


  gtk_container_add(GTK_CONTAINER(window1),verticalbox);
  gtk_widget_show_all(window1);
}

void leerdoc(tipodoctores **inicio){
  tipodoctores *nuevo=(tipodoctores *)malloc(sizeof(tipodoctores)),*avanza;
  FILE *base;
  int i;
  base=fopen("doctores.txt","rt");
  if(base!=NULL){
    while(fgets(nuevo->NombreD,199,base)!=NULL){
      nuevo->NombreD[strlen(nuevo->NombreD)-1]='\0';
      fgets(nuevo->Esp1,49,base);
      nuevo->Esp1[strlen(nuevo->Esp1)-1]='\0';
      fgets(nuevo->Esp2,49,base);
      nuevo->Esp2[strlen(nuevo->Esp2)-1]='\0';
      fgets(nuevo->TelU,19,base);
      nuevo->TelU[strlen(nuevo->TelU)-1]='\0';
      fgets(nuevo->TelN,19,base);
      nuevo->TelN[strlen(nuevo->TelN)-1]='\0';
      fgets(nuevo->DireccionD,99,base);
      nuevo->DireccionD[strlen(nuevo->DireccionD)-1]='\0';
      fgets(nuevo->Consultorio,14,base);
      nuevo->Consultorio[strlen(nuevo->Consultorio)-1]='\0';
      for(i=0;i<7;i++)
        fscanf(base,"%i\n",&nuevo->dias[i]);
      fgets(nuevo->Horario,9,base);
      nuevo->Horario[strlen(nuevo->Horario)-1]='\0';
      fscanf(base,"%i\n",&nuevo->Estatus);
      nuevo->izq=NULL;
      nuevo->der=NULL;
      avanza=*inicio;
      if(*inicio==NULL)
        *inicio=nuevo;
      else{
        while(avanza!=NULL){
          if(strcmp(nuevo->NombreD,avanza->NombreD)>0){
            if(avanza->der!=NULL)
    	        avanza=avanza->der;
            else{
        		  avanza->der=nuevo;
              avanza=NULL;
    	      }
          }
          if(strcmp(nuevo->NombreD,avanza->NombreD)<=0){
            if(avanza->izq!=NULL)
          		avanza=avanza->izq;
          	else{
        		  avanza->izq=nuevo;
              avanza=NULL;
            }
          }
        }
      }
    }
    fclose(base);
  }
}

void escribirdoc(tipodoctores *inicio){
  FILE *base;
  int i;
  base=fopen("doctores.txt","at");
  if(inicio!=NULL){
    escribirdoc(inicio->izq);
    fprintf(base,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n",inicio->NombreD,inicio->Esp1,inicio->Esp2,inicio->TelU,inicio->TelN,inicio->DireccionD,inicio->Consultorio);
    for(i=0;i<7;i++)
      fprintf(base,"%i\n",inicio->dias[i]);
    fprintf(base,"%s\n%i\n",inicio->Horario,inicio->Estatus);
    fclose(base);
    escribirdoc(inicio->der);
  }
}
