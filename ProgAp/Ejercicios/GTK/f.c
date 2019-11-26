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

typedef struct Doctores
{
  char NombreD[30], Esp1[30], Esp2[30], TelU[20], TelN[20], DireccionD[100], Consultorio[15], DiasC[7][2], Horarios[15];
  int Estatus;
  GtkWidget *entrybox;
  struct Doctores *der,*izq;
} tipodoctores;


typedef struct Pacientes
{
  char NombreP[30], DireccionP[100], TelP[20], Sexo[10], Alergias[100], TipoSangre[20], PadecimientosC[100];
  int FechaN[100], Edad;
  float Estatura;
  struct Pacientes *der,*izq;
} tipopacientes;

typedef struct cosas{
  GtkWidget *window,*entrybox[15],*combo,*chkb[6];
  tipopacientes *pinicio;
  tipodoctores *dinicio;
}tipowidget;

GtkWidget *AddButton1(GtkWidget *theBox, const gchar *buttonText, gpointer CallBackFunction, tipowidget *EntryBox);
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
  cosa.window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(cosa.window),"HOSPITAL BHU");
  gtk_window_set_default_size(GTK_WINDOW(cosa.window),600,450);
  gtk_window_move(GTK_WINDOW(cosa.window),450,160);
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
  gtk_signal_connect(GTK_OBJECT(op3),"activate",GTK_SIGNAL_FUNC(ShowNames),NULL);


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
  button = AddButton1(box5,"Buscar",InsertaPV,&cosa);


  label = gtk_label_new("Nombre Completo Del Doctor:  ");
  gtk_box_pack_start(GTK_BOX(box6),label,TRUE,TRUE,0);
  entrybox = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(box6),entrybox,TRUE,TRUE,0);
  datos.entrybox=entrybox;
  button = AddButton1(box6,"Buscar",InsertaPV,&cosa);


  label = gtk_label_new("Especialidad:                             ");
  gtk_box_pack_start(GTK_BOX(box7),label,TRUE,TRUE,0);
  entrybox = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(box7),entrybox,TRUE,TRUE,0);
  datos.entrybox=entrybox;
  button = AddButton1(box7,"Buscar",InsertaPV,&cosa);


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


  gtk_signal_connect(GTK_OBJECT(cosa.window),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);

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


void AcercaDe(GtkWidget *window, gpointer data)
{
  GtkWidget *window1,*label;
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
  gtk_main_quit();
}

void ShowNames(GtkButton *button, gpointer data)
{
  g_print("Bajo\nGaby\nHalabe\n");
}

void InsertaDV(GtkWidget *window, gpointer data)
{
   tipowidget *datos=(tipowidget *) data;
  GtkWidget *window1,*label, *entrybox[9],*rb1,*rb2,*cajarb,*button,*cajarb2;
  GtkWidget *verticalbox,*horizontalbox,*box[9],*imagen,*chkb[6],*cajachkb1,*cajachkb2,*bas;

  int i;

  verticalbox=gtk_vbox_new(FALSE,5);
  horizontalbox=gtk_hbox_new(TRUE,5);
  for(i=0;i<=8;i++){
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
  gtk_window_set_title(GTK_WINDOW(window1),"Inserta Doctor");

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


  imagen = gtk_image_new_from_file("nuevodoc.jpg");
  gtk_box_pack_start(GTK_BOX(verticalbox),imagen,FALSE,TRUE,0);

  for(i=0;i<=8;i++)
    gtk_box_pack_start(GTK_BOX(verticalbox),box[i],TRUE,TRUE,0);

  cajarb=gtk_hbox_new(TRUE,0);
  cajarb2=gtk_hbox_new(TRUE,0);

  label = gtk_label_new("Estatus:");
  gtk_box_pack_start(GTK_BOX(cajarb2),label,TRUE,TRUE,0);

  rb1=gtk_radio_button_new_with_label(NULL,"Activo");
  gtk_box_pack_start(GTK_BOX(cajarb),rb1,FALSE,FALSE,0);
  gtk_signal_connect(GTK_OBJECT(rb1),"toggled",GTK_SIGNAL_FUNC(ShowNames),"1");

  rb2=gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(rb1)),"Inactivo");
  gtk_box_pack_start(GTK_BOX(cajarb),rb2,FALSE,FALSE,0);
  gtk_signal_connect(GTK_OBJECT(rb2),"toggled",GTK_SIGNAL_FUNC(ShowNames),"2");

  gtk_box_pack_start(GTK_BOX(cajarb2),cajarb,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(verticalbox),cajarb2,TRUE,TRUE,0);

  button = gtk_button_new_with_label("Guardar Doctor");
  gtk_box_pack_start(GTK_BOX(horizontalbox),button,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(ADoctor),datos);
  gtk_widget_show(button);
  button=AddButton1(horizontalbox,"Cancelar",ShowNames,NULL);

  gtk_box_pack_start(GTK_BOX(verticalbox),horizontalbox,TRUE,TRUE,0);

  gtk_container_add(GTK_CONTAINER(window1),verticalbox);
  gtk_widget_show_all(window1);
}

void ADoctor(GtkWidget *window, gpointer data){
  tipowidget *datos=(tipowidget *) data;
  tipodoctores *nuevo=(tipodoctores *)malloc(sizeof(tipodoctores)),*avanza;
  const gchar *text;
  char texto[200];
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
  nuevo->izq=NULL;
  nuevo->der=NULL;
  if(datos->dinicio==NULL)
    datos->dinicio=nuevo;
  else{
    avanza=datos->dinicio;
    while(avanza!=NULL){
      if(nuevo->NombreD>avanza->NombreD){
        if(avanza->der!=NULL)
          avanza=avanza->der;
        else{
          avanza->der=nuevo;
          return;
        }
      }
      if(nuevo->NombreD<=avanza->NombreD){
        if(avanza->izq!=NULL)
          avanza=avanza->izq;
        else{
          avanza->izq=nuevo;
          return;
        }
      }
    }
  }
}

void InsertaPV(GtkWidget *window, gpointer data)
{
  tipowidget *datos=(tipowidget *)data;
  GtkWidget *window1,*label, *entrybox,*imagen,*calendario;
  GtkWidget *verticalbox, *horizontalbox,*box[10],*button,*boxfecha;
  GtkWidget *rb1, *rb2;
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
  gtk_window_move(GTK_WINDOW(window1),560,270);
  gtk_container_border_width(GTK_CONTAINER(window1),5);
  gtk_window_set_title(GTK_WINDOW(window1),"Inserta Paciente");

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

  rb1=gtk_radio_button_new_with_label(NULL,"Femenino");
  gtk_box_pack_start(GTK_BOX(cajarb),rb1,FALSE,FALSE,0);
  gtk_signal_connect(GTK_OBJECT(rb1),"toggled",GTK_SIGNAL_FUNC(ShowNames),"1");

  rb2=gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(rb1)),"Masculino");
  gtk_box_pack_start(GTK_BOX(cajarb),rb2,FALSE,FALSE,0);
  gtk_signal_connect(GTK_OBJECT(rb2),"toggled",GTK_SIGNAL_FUNC(ShowNames),"2");

  gtk_box_pack_start(GTK_BOX(box[7]),cajarb,FALSE,FALSE,0);

  imagen = gtk_image_new_from_file("nuevopaci.jpg");
  gtk_box_pack_start(GTK_BOX(verticalbox),imagen,FALSE,TRUE,0);

  label=gtk_label_new("Fecha De Nacimiento:");
  calendario=gtk_calendar_new();
  gtk_box_pack_start(GTK_BOX(box[8]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[8]),calendario,TRUE,TRUE,0);

  for(i=0;i<=7;i++)
    gtk_box_pack_start(GTK_BOX(verticalbox),box[i],TRUE,TRUE,0);

  button=AddButton1(horizontalbox,"Guardar Datos",ShowNames, datos);
  button=AddButton1(horizontalbox,"Cancelar",ShowNames, NULL);

  gtk_box_pack_start(GTK_BOX(verticalbox),horizontalbox,TRUE,TRUE,0);
  gtk_container_add(GTK_CONTAINER(window1),verticalbox);
  gtk_widget_show_all(window1);
}

void ModificarP(GtkWidget *window, gpointer data)
{
  tipowidget *datos=(tipowidget *)data;
  GtkWidget *window1,*label, *entrybox[9], *imagen;
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

  button=AddButton1(horizontalbox,"Guardar Datos",ShowNames, datos);
  button=AddButton1(horizontalbox,"Cancelar",ShowNames, NULL);

  gtk_box_pack_start(GTK_BOX(verticalbox),horizontalbox,TRUE,TRUE,0);
  gtk_container_add(GTK_CONTAINER(window1),verticalbox);
  gtk_widget_show_all(window1);
}

void ModificarD(GtkWidget *window, gpointer data)
{
  tipowidget *datos=(tipowidget *)data;
  GtkWidget *window1,*label, *entrybox[9], *imagen;
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

  rb1=gtk_radio_button_new_with_label(NULL,"Activo");
  gtk_box_pack_start(GTK_BOX(cajarb),rb1,FALSE,FALSE,0);
  gtk_signal_connect(GTK_OBJECT(rb1),"toggled",GTK_SIGNAL_FUNC(ShowNames),"1");

  rb2=gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(rb1)),"Inactivo");
  gtk_box_pack_start(GTK_BOX(cajarb),rb2,FALSE,FALSE,0);
  gtk_signal_connect(GTK_OBJECT(rb2),"toggled",GTK_SIGNAL_FUNC(ShowNames),"2");

  gtk_box_pack_start(GTK_BOX(cajarb2),cajarb,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(verticalbox),cajarb2,TRUE,TRUE,0);

  button = gtk_button_new_with_label("Guardar Doctor");
  gtk_box_pack_start(GTK_BOX(horizontalbox),button,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(ADoctor), datos);
  gtk_widget_show(button);
  button=AddButton1(horizontalbox,"Cancelar",ShowNames, NULL);

  gtk_box_pack_start(GTK_BOX(verticalbox),horizontalbox,TRUE,TRUE,0);

  gtk_container_add(GTK_CONTAINER(window1),verticalbox);
  gtk_widget_show_all(window1);
}


void ModificarC(GtkWidget *window, gpointer data)
{
  tipowidget *datos=(tipowidget *)data;
  GtkWidget *window1,*label, *entrybox[9], *imagen;
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
  button=AddButton1(horizontalbox,"Cancelar",ShowNames, NULL);

  gtk_box_pack_start(GTK_BOX(verticalbox),horizontalbox,TRUE,TRUE,0);

  gtk_container_add(GTK_CONTAINER(window1),verticalbox);
  gtk_widget_show_all(window1);
}

/*void HistoriaC(GtkWidget *window, gpointer data)
{

}
*/
void ListaDoc(GtkWidget *window, gpointer data)
{
  tipowidget *datos=(tipowidget *) data;
  GtkWidget *window1,*label, *entrybox[9],*rb1,*rb2,*cajarb,*button,*cajarb2;
  GtkWidget *verticalbox,*horizontalbox,*box[9],*imagen;

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
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(ADoctor),&datos);
  gtk_widget_show(button);

  g_print("Imprimiendo\n");
  Imprimedoc(datos->dinicio);

  gtk_box_pack_start(GTK_BOX(verticalbox),horizontalbox,TRUE,TRUE,0);

  gtk_container_add(GTK_CONTAINER(window1),verticalbox);
  gtk_widget_show_all(window1);
}

void Imprimedoc(tipodoctores *dinicio){
  g_print("Dentro\n");
  if(dinicio!=NULL){
    Imprimedoc(dinicio->izq);
    g_print("%s\n%s\n",dinicio->NombreD,dinicio->Esp1);
    Imprimedoc(dinicio->der);
  }
}

/*
void NuevaHC(GtkWidget *window, gpointer data)
{
  tipowidget *datos=(tipowidget *)data;
  GtkWidget *window1,*label, *entrybox[9], *imagen;
  GtkWidget *verticalbox, *horizontalbox,*box[9],*button;
  int i;

  verticalbox=gtk_vbox_new(FALSE,5);
  horizontalbox=gtk_hbox_new(TRUE,5);

  imagen = gtk_image_new_from_file("nuevahist.jpg");
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
  gtk_window_set_title(GTK_WINDOW(window1),"Nueva Historia Clínica");

  label = gtk_label_new("Nombre del Paciente:");
  gtk_box_pack_start(GTK_BOX(box[0]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[0]),datos ->entrybox[0],TRUE,TRUE,0);
  button=AddButton2(box[0],"Buscar",ShowNames,entrybox);

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
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(ADoctor),&datos);
  gtk_widget_show(button);
  button=AddButton2(horizontalbox,"Cancelar",ShowNames,entrybox);

  gtk_box_pack_start(GTK_BOX(verticalbox),horizontalbox,TRUE,TRUE,0);

  gtk_container_add(GTK_CONTAINER(window1),verticalbox);
  gtk_widget_show_all(window1);

}*/
