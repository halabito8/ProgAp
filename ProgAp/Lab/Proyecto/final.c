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
 *@date 14/05/2019
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
  struct Doctores *sig;
  GtkWidget *entrybox;
} tipodoctores;

typedef struct consultas{
  char FechaC[20],Dr[200],Diagnostico[500],Tratamiento[200],Anotaciones[200];
  struct consultas *sig;
}tipoconsulta;

typedef struct Pacientes
{
  char NombreP[200], DireccionP[100], TelP[20], Sexo[15], Alergias[100], TipoSangre[6], PadecimientosC[100],FechaN[15];
  int Edad;
  float Estatura;
  struct Pacientes *sig;
  tipoconsulta *inicio;
} tipopacientes;

typedef struct cosas
{
  GtkWidget *window,*entryboxd[10],*entryboxp[10],*entrybox[3],*entryboxc[10],*combo,*chkb[7],*rb[5],*calendario,*box,*combop,*combof;
  tipopacientes *pinicio,*eliminap,*buscar;
  tipodoctores *dinicio,*eliminad;
  tipoconsulta *modi;
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
void ListaPac(GtkWidget *window, gpointer data);
void HistoriaClinica(GtkWidget *window, gpointer data);
void GuardarHC(GtkWidget *window, gpointer data);
void NuevaHC(GtkWidget *window, gpointer data);
void NoHay(GtkWidget *window, gpointer data);
void APaciente(GtkWidget *window, gpointer data);
void BorraDoc(tipodoctores *inicio);
void BorraPac(tipopacientes *inicio);
void BorraCon(tipoconsulta *inicio);
void Cancelar(GtkWidget *window, gpointer data);
void EstaSeguro(GtkWidget window, gpointer data);
void leerdoc(tipodoctores **inicio);
void leerpac(tipopacientes **inicio);
void escribirdoc(tipodoctores *inicio);
void escribirpac(tipopacientes *inicio);
void BuscaPaciente(GtkWidget *window, gpointer data);
void BuscaDoctor(GtkWidget *window, gpointer data);
void BUSCAHC(GtkWidget *window, gpointer data);
void Ayuda(GtkWidget *window, gpointer data);
void MActivos(GtkWidget *window, gpointer data);
void MInactivos(GtkWidget *window, gpointer data);
void BuscaEspecialidad(GtkWidget *window, gpointer data);
void ModP(GtkWidget *window, gpointer data);
void ModD(GtkWidget *window, gpointer data);
void BuscaFecha(GtkWidget *window, gpointer data);
void BuscaCON(GtkWidget *window, gpointer data);
void GuardarMod(GtkWidget *window, gpointer data);
void leercon(tipowidget datos,tipoconsulta **inicio);
void escribircon(tipowidget datos);

gint main ( gint argc, gchar *argv[])
{
  tipowidget cosa;
  GtkWidget *button;
  GtkWidget *box, *box1, *box2, *box3,*box4,*box5,*box6,*box7;
  GtkWidget *verticalbox;
  GtkWidget *root_menu,*menu,*menu_bar,*op1,*op2,*op3,*subop1,*subop2,*menu2;
  GtkWidget *label;
  GtkWidget *imagen,*imagen2;

  cosa.pinicio=NULL;
  cosa.dinicio=NULL;
  cosa.eliminad=NULL;
  cosa.eliminap=NULL;

  gtk_init(&argc, &argv);

  leerdoc(&cosa.dinicio);
  leerpac(&cosa.pinicio);

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

  gtk_signal_connect(GTK_OBJECT(op1),"activate",GTK_SIGNAL_FUNC(ModificarD),&cosa);
  gtk_signal_connect(GTK_OBJECT(op2),"activate",GTK_SIGNAL_FUNC(ModificarP),&cosa);
  gtk_signal_connect(GTK_OBJECT(op3),"activate",GTK_SIGNAL_FUNC(ModificarC),&cosa);

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

  gtk_signal_connect(GTK_OBJECT(op2),"activate",GTK_SIGNAL_FUNC(ListaPac),&cosa);
  gtk_signal_connect(GTK_OBJECT(op3),"activate",GTK_SIGNAL_FUNC(HistoriaClinica),&cosa);

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(root_menu),menu);
  gtk_menu_bar_append(GTK_MENU_BAR(menu_bar),root_menu);

  menu2=gtk_menu_new();
  subop1=gtk_menu_item_new_with_label("Activos");
  subop2=gtk_menu_item_new_with_label("Inactivos");
  gtk_menu_append(GTK_MENU(menu2),subop1);
  gtk_menu_append(GTK_MENU(menu2),subop2);
  gtk_signal_connect(GTK_OBJECT(subop1),"activate",GTK_SIGNAL_FUNC(MActivos),&cosa);
  gtk_signal_connect(GTK_OBJECT(subop2),"activate",GTK_SIGNAL_FUNC(MInactivos),&cosa);

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(op1),menu2);

  //sub x
  root_menu=gtk_menu_item_new_with_label("AYUDA");
  gtk_signal_connect(GTK_OBJECT(root_menu),"activate",GTK_SIGNAL_FUNC(Ayuda),NULL);
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

  label = gtk_label_new("Nombre Completo Del Paciente:");
  gtk_box_pack_start(GTK_BOX(box5),label,TRUE,TRUE,0);
  cosa.entrybox[0] = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(box5),cosa.entrybox[0],TRUE,TRUE,0);
  button = AddButton1(box5,"Buscar",BuscaPaciente,&cosa); //////////////////////////////////////////////////////////////////////////////////////////

  label = gtk_label_new("Nombre Completo Del Doctor:  ");
  gtk_box_pack_start(GTK_BOX(box6),label,TRUE,TRUE,0);
  cosa.entrybox[1] = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(box6),cosa.entrybox[1],TRUE,TRUE,0);
  button = AddButton1(box6,"Buscar",BuscaDoctor,&cosa); //////////////////////////////////////////////////////////////////////////////////////////

  label = gtk_label_new("Especialidad:                             ");
  gtk_box_pack_start(GTK_BOX(box7),label,TRUE,TRUE,0);
  cosa.entrybox[2] = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(box7),cosa.entrybox[2],TRUE,TRUE,0);
  button = AddButton1(box7,"Buscar",BuscaEspecialidad,&cosa); //////////////////////////////////////////////////////////////////////////////////////////

  gtk_box_pack_start(GTK_BOX(box),box1,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box),box2,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box),box3,TRUE,TRUE,0);

  imagen = gtk_image_new_from_file("jeje2.jpg");
  gtk_box_pack_start(GTK_BOX(verticalbox),imagen,FALSE,TRUE,0);

  gtk_box_pack_start(GTK_BOX(verticalbox),menu_bar,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(verticalbox),imagen2,TRUE,TRUE,0);

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

void Ayuda(GtkWidget *window, gpointer data)
{

    GtkWidget *window1;
    GtkWidget *verticalbox,*uno;
    GtkWidget *imagen,*imagen2,*button,*label;

    imagen = gtk_image_new_from_file("help1.jpg");
    imagen2 = gtk_image_new_from_file("help2.jpg");

    uno= gtk_vbox_new(FALSE,5);
    verticalbox=gtk_vbox_new(FALSE,5);

    window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window1),400,200);
    gtk_window_move(GTK_WINDOW(window1),520,110);
    gtk_container_border_width(GTK_CONTAINER(window1),5);
    gtk_window_set_title(GTK_WINDOW(window1),"Ayuda");

    gtk_box_pack_start(GTK_BOX(uno),imagen,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(uno),imagen2,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(verticalbox),uno,TRUE,TRUE,0);
    button=AddButton2(verticalbox,"Entendido",Cancelar,window1);
    gtk_signal_connect(GTK_OBJECT(window1),"destroy",GTK_SIGNAL_FUNC(Cancelar),window1);

    gtk_container_add(GTK_CONTAINER(window1),verticalbox);
    gtk_widget_show_all(window1);
}

void StopTheApp(GtkWidget *window, gpointer data)
{
  tipowidget *dato=(tipowidget *)data;
  escribirdoc(dato->dinicio);
  escribirpac(dato->pinicio);
  BorraPac(dato->pinicio);
  BorraDoc(dato->dinicio);
  gtk_main_quit();
}

void BorraDoc(tipodoctores *inicio)
{
  tipodoctores *temp;
  temp=inicio;
  while(temp!=NULL){
    inicio=inicio->sig;
    free(temp);
    temp=inicio;
  }
}

void BorraPac(tipopacientes *inicio)
{
  tipopacientes *temp;
  temp=inicio;
  if(temp->inicio!=NULL)
    BorraCon(temp->inicio);
  while(temp!=NULL){
    inicio=inicio->sig;
    if(temp->inicio!=NULL)
      BorraCon(temp->inicio);
    free(temp);
    temp=inicio;
  }
}

void BorraCon(tipoconsulta *inicio){
  tipoconsulta *temp;
  temp=inicio;
  while(temp!=NULL){
    inicio=inicio->sig;
    free(temp);
    temp=inicio;
  }
}

void ShowNames(GtkButton *button, gpointer data)
{
  g_print("Bajo\nGaby\nHalabe\n\n");
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
      datos->entryboxd[i] = gtk_entry_new();
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
  gtk_box_pack_start(GTK_BOX(box[0]),datos->entryboxd[0],TRUE,TRUE,0);

  label = gtk_label_new("Especialidad 1:");
  gtk_box_pack_start(GTK_BOX(box[1]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[1]),datos->entryboxd[1],TRUE,TRUE,0);

  label = gtk_label_new("Especialidad 2:");
  gtk_box_pack_start(GTK_BOX(box[2]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[2]),datos->entryboxd[2],TRUE,TRUE,0);

  label = gtk_label_new("Telefono Urgencias:");
  gtk_box_pack_start(GTK_BOX(box[3]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[3]),datos->entryboxd[3],TRUE,TRUE,0);

  label = gtk_label_new("Telefono Personal:");
  gtk_box_pack_start(GTK_BOX(box[4]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[4]),datos->entryboxd[4],TRUE,TRUE,0);

  label = gtk_label_new("Dirección:");
  gtk_box_pack_start(GTK_BOX(box[5]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[5]),datos->entryboxd[5],TRUE,TRUE,0);

  label = gtk_label_new("Consultorio:");
  gtk_box_pack_start(GTK_BOX(box[6]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[6]),datos->entryboxd[6],TRUE,TRUE,0);

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
  tipodoctores *nuevo,*avanza,*avanza2;
  const gchar *text;
  char texto[200],semana[7][10];
  int i;

  if(datos->eliminad!=NULL){
    if(datos->eliminad==datos->dinicio){
      datos->dinicio=datos->eliminad->sig;
      free(datos->eliminad);
    }
    else{
      avanza=datos->dinicio;
      while(avanza->sig!=datos->eliminad)
        avanza=avanza->sig;
      avanza->sig=datos->eliminad->sig;
      free(datos->eliminad);
    }
    datos->eliminad=NULL;
  }

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
    nuevo=(tipodoctores *)malloc(sizeof(tipodoctores));
    strcpy(semana[0],"Lunes");
    strcpy(semana[1],"Martes");
    strcpy(semana[2],"Miercoles");
    strcpy(semana[3],"Jueves");
    strcpy(semana[4],"Viernes");
    strcpy(semana[5],"Sabado");
    strcpy(semana[6],"Domingo");

    text=gtk_entry_get_text(GTK_ENTRY(datos->entryboxd[0]));
    strcpy(texto,text);
    g_print("%s\n",texto);
    strcpy(nuevo->NombreD,texto);
    text=gtk_entry_get_text(GTK_ENTRY(datos->entryboxd[1]));
    strcpy(texto,text);
    g_print("%s\n",texto);
    strcpy(nuevo->Esp1,texto);
    text=gtk_entry_get_text(GTK_ENTRY(datos->entryboxd[2]));
    strcpy(texto,text);
    g_print("%s\n",texto);
    strcpy(nuevo->Esp2,texto);
    text=gtk_entry_get_text(GTK_ENTRY(datos->entryboxd[3]));
    strcpy(texto,text);
    g_print("%s\n",texto);
    strcpy(nuevo->TelU,texto);
    text=gtk_entry_get_text(GTK_ENTRY(datos->entryboxd[4]));
    strcpy(texto,text);
    g_print("%s\n",texto);
    strcpy(nuevo->TelN,texto);
    text=gtk_entry_get_text(GTK_ENTRY(datos->entryboxd[5]));
    strcpy(texto,text);
    g_print("%s\n",texto);
    strcpy(nuevo->DireccionD,texto);
    text=gtk_entry_get_text(GTK_ENTRY(datos->entryboxd[6]));
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
    nuevo->sig=NULL;
    avanza=datos->dinicio;
    if(datos->dinicio==NULL)
      datos->dinicio=nuevo;
    else{
      avanza=datos->dinicio;
      while(avanza!=NULL&&strcmp(nuevo->NombreD,avanza->NombreD)>0)
        avanza=avanza->sig;
      if(avanza==NULL){
        avanza=datos->dinicio;
        while(avanza->sig!=NULL)
          avanza=avanza->sig;
        avanza->sig=nuevo;
      }
      else if(avanza==datos->dinicio){
        nuevo->sig=datos->dinicio;
        datos->dinicio=nuevo;
      }
      else{
        avanza2=datos->dinicio;
        while(avanza2->sig!=avanza)
          avanza2=avanza2->sig;
        nuevo->sig=avanza2->sig;
        avanza2->sig=nuevo;
      }
    }
    if(respuesta== -5)
      {
	gtk_widget_destroy(datos->window);
      }
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
      datos->entryboxp[i] = gtk_entry_new();
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
  gtk_box_pack_start(GTK_BOX(box[0]),datos->entryboxp[0],TRUE,TRUE,0);

  label = gtk_label_new("Dirección:");
  gtk_box_pack_start(GTK_BOX(box[1]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[1]),datos->entryboxp[1],TRUE,TRUE,0);

  label = gtk_label_new("Teléfono:");
  gtk_box_pack_start(GTK_BOX(box[2]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[2]),datos->entryboxp[2],TRUE,TRUE,0);

  label = gtk_label_new("Alergias:");
  gtk_box_pack_start(GTK_BOX(box[3]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[3]),datos->entryboxp[3],TRUE,TRUE,0);

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
  gtk_box_pack_start(GTK_BOX(box[5]),datos->entryboxp[4],TRUE,TRUE,0);

  label = gtk_label_new("Estatura (m):");
  gtk_box_pack_start(GTK_BOX(box[6]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[6]),datos->entryboxp[5],TRUE,TRUE,0);

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
  tipopacientes *nuevo,*avanza,*avanza2;
  const gchar *text;
  char texto[200],cadena[30];
  int ano,mes,dia,fdia,fmes,fano;
  guint year,month,day;

  if(datos->eliminap!=NULL){
    if(datos->eliminap==datos->pinicio){
      datos->pinicio=datos->eliminap->sig;
      free(datos->eliminap);
    }
    else{
      avanza=datos->pinicio;
      while(avanza->sig!=datos->eliminap)
        avanza=avanza->sig;
      avanza->sig=datos->eliminap->sig;
      free(datos->eliminap);
    }
    datos->eliminap=NULL;
  }

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
    nuevo=(tipopacientes *)malloc(sizeof(tipopacientes));
    text=gtk_entry_get_text(GTK_ENTRY(datos->entryboxp[0]));
    strcpy(texto,text);
    g_print("%s\n",texto);
    strcpy(nuevo->NombreP,texto);
    text=gtk_entry_get_text(GTK_ENTRY(datos->entryboxp[1]));
    strcpy(texto,text);
    g_print("%s\n",texto);
    strcpy(nuevo->DireccionP,texto);
    text=gtk_entry_get_text(GTK_ENTRY(datos->entryboxp[2]));
    strcpy(texto,text);
    g_print("%s\n",texto);
    strcpy(nuevo->TelP,texto);
    text=gtk_entry_get_text(GTK_ENTRY(datos->entryboxp[3]));
    strcpy(texto,text);
    g_print("%s\n",texto);
    strcpy(nuevo->Alergias,texto);
    text=gtk_entry_get_text(GTK_ENTRY(datos->entryboxp[4]));
    strcpy(texto,text);
    g_print("%s\n",texto);
    strcpy(nuevo->PadecimientosC,texto);
    text=gtk_entry_get_text(GTK_ENTRY(datos->entryboxp[5]));
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
    nuevo->sig=NULL;
    if(datos->pinicio==NULL)
      datos->pinicio=nuevo;
    else{
      avanza=datos->pinicio;
      while(avanza!=NULL&&strcmp(nuevo->NombreP,avanza->NombreP)>0)
        avanza=avanza->sig;
      if(avanza==NULL){
        avanza=datos->pinicio;
        while(avanza->sig!=NULL)
          avanza=avanza->sig;
        avanza->sig=nuevo;
      }
      else if(avanza==datos->pinicio){
        nuevo->sig=datos->pinicio;
        datos->pinicio=nuevo;
      }
      else{
        avanza2=datos->pinicio;
        while(avanza2->sig!=avanza)
          avanza2=avanza2->sig;
        nuevo->sig=avanza2->sig;
        avanza2->sig=nuevo;
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
  tipopacientes *temp;
  GtkWidget *window1,*label, *imagen;
  GtkWidget *verticalbox, *horizontalbox,*box[9],*button;
  GtkWidget *cajarb;
  int i;

  temp=datos->pinicio;

  verticalbox=gtk_vbox_new(FALSE,5);
  horizontalbox=gtk_hbox_new(TRUE,5);
  for(i=0;i<=8;i++)
    {
      datos->entryboxp[i] = gtk_entry_new();
      box[i] = gtk_hbox_new(TRUE,5);
    }

  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window1),500,200);
  gtk_window_move(GTK_WINDOW(window1),560,270);
  gtk_container_border_width(GTK_CONTAINER(window1),5);
  gtk_window_set_title(GTK_WINDOW(window1),"Modificar Paciente");
  datos->window=window1;

  label = gtk_label_new("Nombre del Paciente:");
  gtk_box_pack_start(GTK_BOX(box[0]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[0]),datos ->entryboxp[0],TRUE,TRUE,0);
  button=AddButton1(box[0],"Buscar",ModP,datos);

  label = gtk_label_new("Dirección:");
  gtk_box_pack_start(GTK_BOX(box[1]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[1]),datos->entryboxp[1],TRUE,TRUE,0);

  label = gtk_label_new("Teléfono:");
  gtk_box_pack_start(GTK_BOX(box[2]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[2]),datos->entryboxp[2],TRUE,TRUE,0);


  label = gtk_label_new("Alergias:");
  gtk_box_pack_start(GTK_BOX(box[3]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[3]),datos->entryboxp[3],TRUE,TRUE,0);

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
  gtk_box_pack_start(GTK_BOX(box[5]),datos->entryboxp[4],TRUE,TRUE,0);

  label = gtk_label_new("Estatura (m):");
  gtk_box_pack_start(GTK_BOX(box[6]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[6]),datos->entryboxp[5],TRUE,TRUE,0);

  label = gtk_label_new("Género:");
  gtk_box_pack_start(GTK_BOX(box[7]),label,TRUE,TRUE,0);

  cajarb=gtk_hbox_new(FALSE,5);

  datos->rb[0]=gtk_radio_button_new_with_label(NULL,"Femenino");
  gtk_box_pack_start(GTK_BOX(cajarb),datos->rb[0],FALSE,FALSE,0);

  datos->rb[1]=gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(datos->rb[0])),"Masculino");
  gtk_box_pack_start(GTK_BOX(cajarb),datos->rb[1],FALSE,FALSE,0);

  gtk_box_pack_start(GTK_BOX(box[7]),cajarb,FALSE,FALSE,0);

  label=gtk_label_new("Fecha De Nacimiento:");
  datos->calendario=gtk_calendar_new();
  gtk_box_pack_start(GTK_BOX(box[8]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[8]),datos->calendario,TRUE,TRUE,0);

  imagen = gtk_image_new_from_file("modificar.jpg");
  gtk_box_pack_start(GTK_BOX(verticalbox),imagen,FALSE,TRUE,0);

  for(i=0;i<=8;i++)
    gtk_box_pack_start(GTK_BOX(verticalbox),box[i],TRUE,TRUE,0);

  button=AddButton1(horizontalbox,"Guardar Datos", APaciente, datos);
  button=AddButton2(horizontalbox,"Cancelar", Cancelar, window1);

  gtk_box_pack_start(GTK_BOX(verticalbox),horizontalbox,TRUE,TRUE,0);
  gtk_container_add(GTK_CONTAINER(window1),verticalbox);
  gtk_widget_show_all(window1);
}

void ModP(GtkWidget *window, gpointer data){
  tipowidget *datos=(tipowidget *)data;
  tipopacientes *avanza;
  const gchar *text;
  char texto[200];
  int dia,mes,ano;
  guint gdia,gmes,gano;
  avanza=datos->pinicio;
  text=gtk_entry_get_text(GTK_ENTRY(datos->entryboxp[0]));
  strcpy(texto,text);
  while(avanza!=NULL&&strcmp(texto,avanza->NombreP)!=0)
    avanza=avanza->sig;
  if(avanza!=NULL){
    gtk_entry_set_text(GTK_ENTRY(datos->entryboxp[1]),avanza->DireccionP);
    gtk_entry_set_text(GTK_ENTRY(datos->entryboxp[2]),avanza->TelP);
    gtk_entry_set_text(GTK_ENTRY(datos->entryboxp[3]),avanza->Alergias);
    gtk_entry_set_text(GTK_ENTRY(datos->entryboxp[4]),avanza->PadecimientosC);
    sprintf(texto,"%.2f",avanza->Estatura);
    gtk_entry_set_text(GTK_ENTRY(datos->entryboxp[5]),texto);
    if(strcmp(avanza->TipoSangre,"A+")==0)
      gtk_combo_box_set_active(GTK_COMBO_BOX(datos->combo),0);
    else if(strcmp(avanza->TipoSangre,"A-")==0)
      gtk_combo_box_set_active(GTK_COMBO_BOX(datos->combo),1);
    else if(strcmp(avanza->TipoSangre,"B+")==0)
      gtk_combo_box_set_active(GTK_COMBO_BOX(datos->combo),2);
    else if(strcmp(avanza->TipoSangre,"B-")==0)
      gtk_combo_box_set_active(GTK_COMBO_BOX(datos->combo),3);
    else if(strcmp(avanza->TipoSangre,"AB+")==0)
      gtk_combo_box_set_active(GTK_COMBO_BOX(datos->combo),4);
    else if(strcmp(avanza->TipoSangre,"AB-")==0)
      gtk_combo_box_set_active(GTK_COMBO_BOX(datos->combo),5);
    else if(strcmp(avanza->TipoSangre,"O+")==0)
      gtk_combo_box_set_active(GTK_COMBO_BOX(datos->combo),6);
    else if(strcmp(avanza->TipoSangre,"O-")==0)
      gtk_combo_box_set_active(GTK_COMBO_BOX(datos->combo),7);
    if(strcmp(avanza->Sexo,"Femenino")==0)
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(datos->rb[0]),TRUE);
    else
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(datos->rb[1]),TRUE);
    sscanf(avanza->FechaN,"%i/%i/%i",&dia,&mes,&ano);
    gdia=dia;
    gmes=--mes;
    gano=ano;
    gtk_calendar_select_month(GTK_CALENDAR(datos->calendario),gmes,gano);
    gtk_calendar_select_day(GTK_CALENDAR(datos->calendario),gdia);
    datos->eliminap=avanza;
  }
}

void ModificarD(GtkWidget *window, gpointer data)
{
  tipowidget *datos=(tipowidget *)data;
  GtkWidget *window1,*label, *imagen;
  GtkWidget *verticalbox, *horizontalbox,*box[9],*button,*cajachkb1,*cajachkb2,*bas;
  GtkWidget *cajarb, *cajarb2;
  int i;
  char semana[7][10];
  strcpy(semana[0],"Lunes");
  strcpy(semana[1],"Martes");
  strcpy(semana[2],"Miercoles");
  strcpy(semana[3],"Jueves");
  strcpy(semana[4],"Viernes");
  strcpy(semana[5],"Sabado");
  strcpy(semana[6],"Domingo");

  verticalbox=gtk_vbox_new(FALSE,5);
  horizontalbox=gtk_hbox_new(TRUE,5);

  imagen = gtk_image_new_from_file("modificar.jpg");
  gtk_box_pack_start(GTK_BOX(verticalbox),imagen,FALSE,TRUE,0);

  for(i=0;i<=8;i++)
    {
      datos->entryboxd[i] = gtk_entry_new();
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
  datos->window=window1;

  label = gtk_label_new("Nombre del Doctor:");
  gtk_box_pack_start(GTK_BOX(box[0]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[0]),datos ->entryboxd[0],TRUE,TRUE,0);
  button=AddButton1(box[0],"Buscar",ModD,datos);

  label = gtk_label_new("Especialidad 1:");
  gtk_box_pack_start(GTK_BOX(box[1]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[1]),datos->entryboxd[1],TRUE,TRUE,0);

  label = gtk_label_new("Especialidad 2:");
  gtk_box_pack_start(GTK_BOX(box[2]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[2]),datos->entryboxd[2],TRUE,TRUE,0);

  label = gtk_label_new("Telefono Urgencias:");
  gtk_box_pack_start(GTK_BOX(box[3]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[3]),datos->entryboxd[3],TRUE,TRUE,0);

  label = gtk_label_new("Telefono Personal:");
  gtk_box_pack_start(GTK_BOX(box[4]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[4]),datos->entryboxd[4],TRUE,TRUE,0);

  label = gtk_label_new("Dirección:");
  gtk_box_pack_start(GTK_BOX(box[5]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[5]),datos->entryboxd[5],TRUE,TRUE,0);

  label = gtk_label_new("Consultorio:");
  gtk_box_pack_start(GTK_BOX(box[6]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[6]),datos->entryboxd[6],TRUE,TRUE,0);

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
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(ADoctor), datos);
  gtk_widget_show(button);
  button=AddButton2(horizontalbox,"Cancelar", Cancelar, window1);

  gtk_box_pack_start(GTK_BOX(verticalbox),horizontalbox,TRUE,TRUE,0);

  gtk_container_add(GTK_CONTAINER(window1),verticalbox);
  gtk_widget_show_all(window1);
}

void ModD(GtkWidget *window, gpointer data){
  tipowidget *datos=(tipowidget *)data;
  tipodoctores *avanza;
  const gchar *text;
  char texto[200];
  int i;
  avanza=datos->dinicio;
  text=gtk_entry_get_text(GTK_ENTRY(datos->entryboxd[0]));
  strcpy(texto,text);
  while(avanza!=NULL&&strcmp(texto,avanza->NombreD)!=0)
    avanza=avanza->sig;
  if(avanza!=NULL){
    gtk_entry_set_text(GTK_ENTRY(datos->entryboxd[1]),avanza->Esp1);
    gtk_entry_set_text(GTK_ENTRY(datos->entryboxd[2]),avanza->Esp2);
    gtk_entry_set_text(GTK_ENTRY(datos->entryboxd[3]),avanza->TelU);
    gtk_entry_set_text(GTK_ENTRY(datos->entryboxd[4]),avanza->TelN);
    gtk_entry_set_text(GTK_ENTRY(datos->entryboxd[5]),avanza->DireccionD);
    gtk_entry_set_text(GTK_ENTRY(datos->entryboxd[6]),avanza->Consultorio);
    if(strcmp(avanza->Horario,"06-16")==0)
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(datos->rb[0]),TRUE);
    else if(strcmp(avanza->Horario,"14-00")==0)
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(datos->rb[1]),TRUE);
    else
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(datos->rb[2]),TRUE);
    for(i=0;i<7;i++){
      if(avanza->dias[i]==1)
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(datos->chkb[i]),TRUE);
      else
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(datos->chkb[i]),FALSE);
    }
    if(avanza->Estatus==1)
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(datos->rb[3]),TRUE);
    else
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(datos->rb[4]),TRUE);
  }
}

void ModificarC(GtkWidget *window, gpointer data)
{
  tipowidget *datos=(tipowidget *)data;
  tipopacientes *avanza;
  GtkWidget *window1,*label, *imagen;
  GtkWidget *verticalbox, *horizontalbox,*box[9],*button;
  int i;

  verticalbox=gtk_vbox_new(FALSE,5);
  horizontalbox=gtk_hbox_new(TRUE,5);

  imagen = gtk_image_new_from_file("modificar.jpg");
  gtk_box_pack_start(GTK_BOX(verticalbox),imagen,FALSE,TRUE,0);

  for(i=0;i<=8;i++)
    {
      datos->entryboxc[i] = gtk_entry_new();
      box[i] = gtk_hbox_new(TRUE,5);
    }

  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window1),500,200);
  gtk_window_move(GTK_WINDOW(window1),560,270);
  gtk_container_border_width(GTK_CONTAINER(window1),5);
  gtk_window_set_title(GTK_WINDOW(window1),"Modificar Historia Clínica");

  label = gtk_label_new("Nombre del Paciente:");
  gtk_box_pack_start(GTK_BOX(box[0]),label,TRUE,TRUE,0);
  avanza=datos->pinicio;
  datos->combop=gtk_combo_box_new_text();
  while(avanza!=NULL){
    gtk_combo_box_append_text(GTK_COMBO_BOX(datos->combop),avanza->NombreP);
    avanza=avanza->sig;
  }
  gtk_box_pack_start(GTK_BOX(box[0]),datos->combop,TRUE,TRUE,0);
  button=AddButton1(box[0],"Buscar",BuscaFecha,datos);

  label = gtk_label_new("Fecha de Consulta:");
  gtk_box_pack_start(GTK_BOX(box[1]),label,TRUE,TRUE,0);
  datos->combof=gtk_combo_box_new_text();
  gtk_box_pack_start(GTK_BOX(box[1]),datos->combof,TRUE,TRUE,0);
  button=AddButton1(box[1],"Buscar",BuscaCON,datos);

  label = gtk_label_new("Nombre del Doctor Tratante");
  gtk_box_pack_start(GTK_BOX(box[2]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[2]),datos->entryboxc[2],TRUE,TRUE,0);


  label = gtk_label_new("Diágnostico:");
  gtk_box_pack_start(GTK_BOX(box[3]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[3]),datos->entryboxc[3],TRUE,TRUE,0);

  label = gtk_label_new("Tratamiento:");
  gtk_box_pack_start(GTK_BOX(box[4]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[4]),datos->entryboxc[4],TRUE,TRUE,0);

  label = gtk_label_new("Anotaciones:");
  gtk_box_pack_start(GTK_BOX(box[5]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[5]),datos->entryboxc[5],TRUE,TRUE,0);

  for(i=0;i<=5;i++)
    gtk_box_pack_start(GTK_BOX(verticalbox),box[i],TRUE,TRUE,0);


  button = gtk_button_new_with_label("Guardar Consulta");
  gtk_box_pack_start(GTK_BOX(horizontalbox),button,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(GuardarMod),datos);
  gtk_widget_show(button);
  button=AddButton2(horizontalbox,"Cancelar", Cancelar, window1);

  gtk_box_pack_start(GTK_BOX(verticalbox),horizontalbox,TRUE,TRUE,0);

  gtk_container_add(GTK_CONTAINER(window1),verticalbox);
  gtk_widget_show_all(window1);
}

void BuscaFecha(GtkWidget *window, gpointer data){
  tipowidget *datos=(tipowidget *)data;
  tipopacientes *avanza;
  tipoconsulta *temp;
  const gchar *text;
  char texto[200];
  text=gtk_combo_box_get_active_text(GTK_COMBO_BOX(datos->combop));
  strcpy(texto,text);
  gtk_combo_box_set_button_sensitivity(GTK_COMBO_BOX(datos->combop),GTK_SENSITIVITY_OFF);
  avanza=datos->pinicio;
  while(avanza!=NULL&&strcmp(avanza->NombreP,texto))
    avanza=avanza->sig;
  temp=avanza->inicio;
  while(temp!=NULL){
    gtk_combo_box_append_text(GTK_COMBO_BOX(datos->combof),temp->FechaC);
    temp=temp->sig;
  }
  datos->buscar=avanza;
}

void BuscaCON(GtkWidget *window, gpointer data){
  tipowidget *datos=(tipowidget *)data;
  tipoconsulta *temp;
  temp=datos->buscar->inicio;
  const gchar *text;
  char texto[200];
  text=gtk_combo_box_get_active_text(GTK_COMBO_BOX(datos->combof));
  strcpy(texto,text);
  while(temp!=NULL&&strcmp(texto,temp->FechaC)!=0)
    temp=temp->sig;
  gtk_entry_set_text(GTK_ENTRY(datos->entryboxc[2]),temp->Dr);
  gtk_entry_set_text(GTK_ENTRY(datos->entryboxc[3]),temp->Diagnostico);
  gtk_entry_set_text(GTK_ENTRY(datos->entryboxc[4]),temp->Tratamiento);
  gtk_entry_set_text(GTK_ENTRY(datos->entryboxc[5]),temp->Anotaciones);
  datos->modi=temp;
}

void GuardarMod(GtkWidget *window, gpointer data){
  tipowidget *datos=(tipowidget *)data;
  tipopacientes *avanza;
  tipoconsulta *temp;
  avanza=datos->buscar;
  temp=datos->modi;
  const gchar *text;
  text=gtk_entry_get_text(GTK_ENTRY(datos->entryboxc[2]));
  strcpy(temp->Dr,text);
  text=gtk_entry_get_text(GTK_ENTRY(datos->entryboxc[3]));
  strcpy(temp->Diagnostico,text);
  text=gtk_entry_get_text(GTK_ENTRY(datos->entryboxc[4]));
  strcpy(temp->Tratamiento,text);
  text=gtk_entry_get_text(GTK_ENTRY(datos->entryboxc[5]));
  strcpy(temp->Anotaciones,text);
}

void MActivos(GtkWidget *window, gpointer data){
  tipowidget *datos=(tipowidget *)data;
  tipodoctores *temp;
  GtkWidget *horizontalbox,*boxdias,*label,*window1,*verticalbox,*box,*button;
  GtkWidget *swin,*imagen;
  char texto[200],semana[7][10];
  int i;

  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request (window1, 470, 450);
  gtk_window_move(GTK_WINDOW(window1),560,270);
  gtk_container_border_width(GTK_CONTAINER(window1),5);
  gtk_window_set_title(GTK_WINDOW(window1),"Lista de Doctores");

  imagen = gtk_image_new_from_file("listadoc.jpg");
  verticalbox=gtk_vbox_new(FALSE,5);
  box=gtk_vbox_new(FALSE,5);
  swin = gtk_scrolled_window_new (NULL, NULL);

  strcpy(semana[0],"Lunes");
  strcpy(semana[1],"Martes");
  strcpy(semana[2],"Miercoles");
  strcpy(semana[3],"Jueves");
  strcpy(semana[4],"Viernes");
  strcpy(semana[5],"Sabado");
  strcpy(semana[6],"Domingo");


  temp=datos->dinicio;
  while(temp!=NULL){
    if(temp->Estatus==1){

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Nombre:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->NombreD);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Especialidad 1:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->Esp1);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Especialidad 2:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->Esp2);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Telefono de Urgencias:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->TelU);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);\

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Telefono Personal:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->TelN);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Direccion:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->DireccionD);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Consultorio:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->Consultorio);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Horario:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->Horario);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Dias de Consulta");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      boxdias=gtk_vbox_new(TRUE,5);
      for(i=0;i<7;i++){
        if(temp->dias[i]==1){
          label=gtk_label_new(semana[i]);
          gtk_box_pack_start(GTK_BOX(boxdias),label,TRUE,TRUE,0);
        }
      }
      gtk_box_pack_start(GTK_BOX(horizontalbox),boxdias,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Estatus:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      if(temp->Estatus==1)
        strcpy(texto,"Activo");
      else
        strcpy(texto,"Inactivo");
      label=gtk_label_new(texto);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);
      label=gtk_label_new("____________________________________________________");
      gtk_box_pack_start(GTK_BOX(box),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(swin),box,FALSE,TRUE,0);
    }
    temp=temp->sig;
  }

  gtk_container_set_border_width (GTK_CONTAINER (swin), 10);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (swin),GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (swin), box);
  gtk_box_pack_start(GTK_BOX (verticalbox), imagen,FALSE,TRUE,5);
  gtk_box_pack_start_defaults(GTK_BOX (verticalbox), swin);

  button = gtk_button_new_with_label("Cerrar");
  gtk_box_pack_end(GTK_BOX(verticalbox),button,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(Cancelar), window1);
  gtk_box_pack_start(GTK_BOX(verticalbox),box,TRUE,TRUE,0);
  gtk_container_add(GTK_CONTAINER(window1),verticalbox);
  gtk_widget_show_all(window1);
}

void MInactivos(GtkWidget *window, gpointer data){
  tipowidget *datos=(tipowidget *)data;
  tipodoctores *temp;
  GtkWidget *horizontalbox,*boxdias,*label,*window1,*verticalbox,*box,*button;
  GtkWidget *swin,*imagen;
  char texto[200],semana[7][10];
  int i;

  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request (window1, 470, 450);
  gtk_window_move(GTK_WINDOW(window1),560,270);
  gtk_container_border_width(GTK_CONTAINER(window1),5);
  gtk_window_set_title(GTK_WINDOW(window1),"Lista de Doctores");
  imagen = gtk_image_new_from_file("listadoc.jpg");
  swin = gtk_scrolled_window_new (NULL, NULL);

  verticalbox=gtk_vbox_new(FALSE,5);
  box=gtk_vbox_new(FALSE,5);

  strcpy(semana[0],"Lunes");
  strcpy(semana[1],"Martes");
  strcpy(semana[2],"Miercoles");
  strcpy(semana[3],"Jueves");
  strcpy(semana[4],"Viernes");
  strcpy(semana[5],"Sabado");
  strcpy(semana[6],"Domingo");

  temp=datos->dinicio;
  while(temp!=NULL){
    if(temp->Estatus==0){

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Nombre:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->NombreD);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Especialidad 1:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->Esp1);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Especialidad 2:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->Esp2);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Telefono de Urgencias:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->TelU);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);\

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Telefono Personal:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->TelN);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Direccion:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->DireccionD);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Consultorio:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->Consultorio);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Horario:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->Horario);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Dias de Consulta");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      boxdias=gtk_vbox_new(TRUE,5);
      for(i=0;i<7;i++){
        if(temp->dias[i]==1){
          label=gtk_label_new(semana[i]);
          gtk_box_pack_start(GTK_BOX(boxdias),label,TRUE,TRUE,0);
        }
      }
      gtk_box_pack_start(GTK_BOX(horizontalbox),boxdias,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Estatus:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      if(temp->Estatus==1)
        strcpy(texto,"Activo");
      else
        strcpy(texto,"Inactivo");
      label=gtk_label_new(texto);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);
      label=gtk_label_new("____________________________________________________");
      gtk_box_pack_start(GTK_BOX(box),label,TRUE,TRUE,0);

      gtk_box_pack_start(GTK_BOX(swin),box,FALSE,TRUE,0);
    }
    temp=temp->sig;
  }

  gtk_container_set_border_width (GTK_CONTAINER (swin), 10);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (swin),GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (swin), box);

  gtk_box_pack_start(GTK_BOX(verticalbox),imagen,FALSE,TRUE,0);
  gtk_box_pack_start_defaults(GTK_BOX (verticalbox), swin);



  button = gtk_button_new_with_label("Cerrar");
  gtk_box_pack_end(GTK_BOX(verticalbox),button,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(Cancelar), window1);
  gtk_box_pack_start(GTK_BOX(verticalbox),box,TRUE,TRUE,0);
  gtk_container_add(GTK_CONTAINER(window1),verticalbox);
  gtk_widget_show_all(window1);
}

void ListaPac(GtkWidget *window, gpointer data)
{
  tipowidget *datos=(tipowidget *) data;
  GtkWidget *window1,*button,*label;
  GtkWidget *swin,*viewport;
  GtkAdjustment *vertical;
  GtkWidget *verticalbox,*verticalbox1,*verticalbox2,*horizontalbox,*imagen,*box;
  tipopacientes *temp;
  char texto[20];
  temp=datos->pinicio;
  verticalbox=gtk_vbox_new(FALSE,5);

  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request (window1, 470, 450);
  gtk_window_move(GTK_WINDOW(window1),560,270);
  gtk_container_border_width(GTK_CONTAINER(window1),10);
  gtk_window_set_title(GTK_WINDOW(window1),"Lista de Pacientes");
  swin = gtk_scrolled_window_new (NULL, NULL);
  imagen = gtk_image_new_from_file("listapaci.jpg");
  gtk_box_pack_start(GTK_BOX(verticalbox),imagen,FALSE,TRUE,0);
  box=gtk_vbox_new(FALSE,5);
  if(temp!=NULL){
    while(temp!=NULL){
      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Nombre:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->NombreP);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Direccion:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->DireccionP);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Telefono:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->TelP);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Sexo:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->Sexo);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Alergias:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->Alergias);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Tipo De Sangre:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->TipoSangre);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Padecimientos Cronicos:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->PadecimientosC);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Fecha De Nacimiento:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->FechaN);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Edad:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      sprintf(texto,"%i",temp->Edad);
      label=gtk_label_new(texto);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Estatura:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      sprintf(texto,"%.2f",temp->Estatura);
      label=gtk_label_new(texto);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      label=gtk_label_new("____________________________________________________");
      gtk_box_pack_start(GTK_BOX(box),label,TRUE,TRUE,0);

      gtk_box_pack_start(GTK_BOX(swin),box,FALSE,TRUE,0);
      temp=temp->sig;
    }
  }
  else{
    label=gtk_label_new("No hay pacientes");
    gtk_box_pack_start(GTK_BOX(box),label,TRUE,TRUE,0);
  }

  gtk_container_set_border_width (GTK_CONTAINER (swin), 10);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (swin),GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (swin), box);
  gtk_box_pack_start_defaults(GTK_BOX (verticalbox), swin);

  button = gtk_button_new_with_label("Cerrar");
  gtk_box_pack_start(GTK_BOX(verticalbox),button,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(Cancelar), window1);
  gtk_widget_show(button);
  gtk_box_pack_start(GTK_BOX(verticalbox),horizontalbox,TRUE,TRUE,0);

  gtk_container_add(GTK_CONTAINER(window1),verticalbox);
  gtk_widget_show_all(window1);
}

void HistoriaClinica(GtkWidget *window, gpointer data)
{
  tipowidget *datos=(tipowidget *) data;
  tipopacientes *avanza;
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

  gtk_box_pack_start(GTK_BOX(verticalbox),horizontalbox,TRUE,TRUE,0);


  horizontalbox=gtk_hbox_new(TRUE,5);
  button = gtk_button_new_with_label("Nueva Historia Clínica");
  gtk_box_pack_start(GTK_BOX(horizontalbox),button,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(NuevaHC),datos);
  gtk_widget_show(button);
  button=AddButton2(horizontalbox,"Cancelar",Cancelar,window1);

  gtk_box_pack_start(GTK_BOX(verticalbox),horizontalbox,TRUE,TRUE,0);

  gtk_container_add(GTK_CONTAINER(window1),verticalbox);
  gtk_widget_show_all(window1);
}

void BUSCAHC(GtkWidget *window, gpointer data){
  tipowidget *datos=(tipowidget *)data;
  tipopacientes *avanza2;
  tipoconsulta *avanza;
  GtkWidget *button,*window1,*verticalbox,*horizontalbox,*box,*label;
  const gchar *text;
  char texto[200];
  verticalbox=gtk_vbox_new(FALSE,5);

  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window1),400,200);
  gtk_window_move(GTK_WINDOW(window1),560,270);
  gtk_container_border_width(GTK_CONTAINER(window1),5);
  gtk_window_set_title(GTK_WINDOW(window1),"HISTORIA CLÍNICA");
  text=gtk_combo_box_get_active_text(GTK_COMBO_BOX(datos->combop));
  strcpy(texto,text);
  avanza2=datos->pinicio;
  while(avanza2!=NULL&&strcmp(texto,avanza2->NombreP))
    avanza2=avanza2->sig;
  if(avanza2!=NULL){
    box=gtk_hbox_new(TRUE,5);
    avanza=avanza2->inicio;
    while(avanza!=NULL){
      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Fecha Consulta:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(avanza->FechaC);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);
    }
  }
  gtk_widget_show_all(window1);
}

void NuevaHC(GtkWidget *window, gpointer data)
{
  tipowidget *datos=(tipowidget *)data;
  tipopacientes *avanza;
  GtkWidget *window1, *label, *imagen;
  GtkWidget *verticalbox, *horizontalbox,*box[6],*button,*scroll[6],*caja;
  int i;

  verticalbox=gtk_vbox_new(FALSE,5);
  horizontalbox=gtk_hbox_new(TRUE,5);

  imagen = gtk_image_new_from_file("historia.jpg");
  gtk_box_pack_start(GTK_BOX(verticalbox),imagen,FALSE,TRUE,0);

  for(i=0;i<6;i++)
    {
      datos->entryboxc[i] = gtk_entry_new();
      box[i] = gtk_hbox_new(TRUE,5);
    }

  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window1),500,200);
  gtk_window_move(GTK_WINDOW(window1),560,270);
  gtk_container_border_width(GTK_CONTAINER(window1),5);
  gtk_window_set_title(GTK_WINDOW(window1),"Nueva Historia Clínica");

  label = gtk_label_new("Nombre del Paciente:");
  gtk_box_pack_start(GTK_BOX(box[0]),label,TRUE,TRUE,0);
  avanza=datos->pinicio;
  datos->combop=gtk_combo_box_new_text();
  while(avanza!=NULL){
    gtk_combo_box_append_text(GTK_COMBO_BOX(datos->combop),avanza->NombreP);
    avanza=avanza->sig;
  }
  gtk_box_pack_start(GTK_BOX(box[0]),datos->combop,TRUE,TRUE,0);
  caja=gtk_hbox_new(FALSE,5);
  label = gtk_label_new("Nombre del Doctor Tratante:");
  gtk_box_pack_start(GTK_BOX(box[2]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[2]),datos->entryboxc[2],TRUE,TRUE,0);

  caja=gtk_hbox_new(FALSE,5);
  label = gtk_label_new("Diágnostico:");
  gtk_box_pack_start(GTK_BOX(box[3]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[3]),datos->entryboxc[3],TRUE,TRUE,0);

  caja=gtk_hbox_new(FALSE,5);
  label = gtk_label_new("Tratamiento:");
  gtk_box_pack_start(GTK_BOX(box[4]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[4]),datos->entryboxc[4],TRUE,TRUE,0);

  caja=gtk_hbox_new(FALSE,5);
  label = gtk_label_new("Anotaciones:");
  gtk_box_pack_start(GTK_BOX(box[5]),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box[5]),datos->entryboxc[5],TRUE,TRUE,0);

  for(i=0;i<6;i++)
    gtk_box_pack_start(GTK_BOX(verticalbox),box[i],TRUE,TRUE,0);

  datos->window=window1;

  button = gtk_button_new_with_label("Guardar Consulta");
  gtk_box_pack_start(GTK_BOX(horizontalbox),button,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(GuardarHC),datos);
  gtk_widget_show(button);
  button=AddButton2(horizontalbox,"Cancelar", Cancelar, window1);

  gtk_box_pack_start(GTK_BOX(verticalbox),horizontalbox,TRUE,TRUE,0);

  gtk_container_add(GTK_CONTAINER(window1),verticalbox);
  gtk_widget_show_all(window1);
}

void GuardarHC(GtkWidget *window, gpointer data){
  tipowidget *datos=(tipowidget *)data;
  tipopacientes *avanza;
  tipoconsulta *nuevo;
  const gchar *text;
  char texto[200];
  time_t crudo;
  struct tm *tipotiempo;

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
    avanza=datos->pinicio;
    text=gtk_combo_box_get_active_text(GTK_COMBO_BOX(datos->combop));
    strcpy(texto,text);
    g_print("%s\n",texto);
    while(avanza!=NULL&&strcmp(avanza->NombreP,texto))
      avanza=avanza->sig;
    if(avanza!=NULL){
      time(&crudo);
      tipotiempo=localtime(&crudo);
      strftime(texto,199,"%Y-%m-%d-%H:%M",tipotiempo);
      nuevo=(tipoconsulta *)malloc(sizeof(tipoconsulta));
      strcpy(nuevo->FechaC,texto);
      text=gtk_entry_get_text(GTK_ENTRY(datos->entryboxc[2]));
      strcpy(texto,text);
      g_print("%s\n",texto);
      strcpy(nuevo->Dr,texto);
      text=gtk_entry_get_text(GTK_ENTRY(datos->entryboxc[3]));
      strcpy(texto,text);
      g_print("%s\n",texto);
      strcpy(nuevo->Diagnostico,texto);
      text=gtk_entry_get_text(GTK_ENTRY(datos->entryboxc[4]));
      strcpy(texto,text);
      g_print("%s\n",texto);
      strcpy(nuevo->Tratamiento,texto);
      text=gtk_entry_get_text(GTK_ENTRY(datos->entryboxc[5]));
      strcpy(texto,text);
      g_print("%s\n",texto);
      strcpy(nuevo->Anotaciones,texto);
      nuevo->sig=avanza->inicio;
      avanza->inicio=nuevo;
    }
  }
  if(respuesta==-5){
    gtk_widget_destroy(datos->window);

  }
}

void BuscaDoctor(GtkWidget *window, gpointer data){
  tipowidget *datos=(tipowidget *)data;
  tipodoctores *temp;
  GtkWidget *window1,*verticalbox,*horizontalbox,*box,*label,*boxdias,*imagen,*button;
  const gchar *text;
  char texto[200],semana[7][10];
  int i;

  strcpy(semana[0],"Lunes");
  strcpy(semana[1],"Martes");
  strcpy(semana[2],"Miercoles");
  strcpy(semana[3],"Jueves");
  strcpy(semana[4],"Viernes");
  strcpy(semana[5],"Sabado");
  strcpy(semana[6],"Domingo");
  window1=gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window1),400,200);
  gtk_window_move(GTK_WINDOW(window1),560,270);
  gtk_container_border_width(GTK_CONTAINER(window1),5);
  gtk_window_set_title(GTK_WINDOW(window1),"INFORMACION");

  verticalbox=gtk_vbox_new(FALSE,5);
  box=gtk_vbox_new(FALSE,5);

  temp=datos->dinicio;

  text=gtk_entry_get_text(GTK_ENTRY(datos->entrybox[1]));
  strcpy(texto,text);
  while(temp!=NULL&&strcmp(temp->NombreD,texto)!=0)
    temp=temp->sig;

  if(temp!=NULL){

    horizontalbox=gtk_hbox_new(TRUE,5);
    label=gtk_label_new("Nombre:");
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    label=gtk_label_new(temp->NombreD);
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

    horizontalbox=gtk_hbox_new(TRUE,5);
    label=gtk_label_new("Especialidad 1:");
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    label=gtk_label_new(temp->Esp1);
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

    horizontalbox=gtk_hbox_new(TRUE,5);
    label=gtk_label_new("Especialidad 2:");
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    label=gtk_label_new(temp->Esp2);
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

    horizontalbox=gtk_hbox_new(TRUE,5);
    label=gtk_label_new("Telefono de Urgencias:");
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    label=gtk_label_new(temp->TelU);
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);\

    horizontalbox=gtk_hbox_new(TRUE,5);
    label=gtk_label_new("Telefono Personal:");
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    label=gtk_label_new(temp->TelN);
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

    horizontalbox=gtk_hbox_new(TRUE,5);
    label=gtk_label_new("Direccion");
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    label=gtk_label_new(temp->DireccionD);
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

    horizontalbox=gtk_hbox_new(TRUE,5);
    label=gtk_label_new("Consultorio");
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    label=gtk_label_new(temp->Consultorio);
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

    horizontalbox=gtk_hbox_new(TRUE,5);
    label=gtk_label_new("Horario");
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    label=gtk_label_new(temp->Horario);
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

    horizontalbox=gtk_hbox_new(TRUE,5);
    label=gtk_label_new("Horario");
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    boxdias=gtk_vbox_new(TRUE,5);
    for(i=0;i<7;i++){
      if(temp->dias[i]==1){
        label=gtk_label_new(semana[i]);
        gtk_box_pack_start(GTK_BOX(boxdias),label,TRUE,TRUE,0);
      }
    }
    gtk_box_pack_start(GTK_BOX(horizontalbox),boxdias,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

    horizontalbox=gtk_hbox_new(TRUE,5);
    label=gtk_label_new("Estaus:");
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    if(temp->Estatus==0)
      strcpy(texto,"Activo");
    else
      strcpy(texto,"Inactivo");
    label=gtk_label_new(texto);
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);
  }
  else{
    verticalbox=gtk_vbox_new(FALSE,5);
    horizontalbox=gtk_hbox_new(TRUE,5);

    window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window1),400,200);
    gtk_window_move(GTK_WINDOW(window1),560,270);
    gtk_container_border_width(GTK_CONTAINER(window1),5);
    gtk_window_set_title(GTK_WINDOW(window1),"No Encontrado");

    imagen = gtk_image_new_from_file("noencontrado.jpg");
    gtk_box_pack_start(GTK_BOX(verticalbox),imagen,FALSE,TRUE,0);
    button=AddButton1(verticalbox,"Aceptar",Cancelar,window1);

    gtk_container_add(GTK_CONTAINER(window1),verticalbox);
    gtk_widget_show_all(window1);
      }
  gtk_signal_connect(GTK_OBJECT(window1),"destroy",GTK_SIGNAL_FUNC(Cancelar),window1);

  gtk_box_pack_start(GTK_BOX(verticalbox),box,TRUE,TRUE,0);
  gtk_container_add(GTK_CONTAINER(window1),verticalbox);
  gtk_widget_show_all(window1);
}

void BuscaEspecialidad(GtkWidget *window, gpointer data){
  tipowidget *datos=(tipowidget *)data;
  tipodoctores *temp;
  GtkWidget *window1,*verticalbox,*horizontalbox,*box,*label,*boxdias,*swin;
  const gchar *text;
  char texto[200],semana[7][10];
  int i;

  strcpy(semana[0],"Lunes");
  strcpy(semana[1],"Martes");
  strcpy(semana[2],"Miercoles");
  strcpy(semana[3],"Jueves");
  strcpy(semana[4],"Viernes");
  strcpy(semana[5],"Sabado");
  strcpy(semana[6],"Domingo");
  window1=gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request (window1, 400, 350);
  gtk_window_move(GTK_WINDOW(window1),560,270);
  gtk_container_border_width(GTK_CONTAINER(window1),5);
  gtk_window_set_title(GTK_WINDOW(window1),"INFORMACION");
  swin = gtk_scrolled_window_new (NULL, NULL);
  verticalbox=gtk_vbox_new(FALSE,5);
  box=gtk_vbox_new(FALSE,5);

  temp=datos->dinicio;

  text=gtk_entry_get_text(GTK_ENTRY(datos->entrybox[2]));
  strcpy(texto,text);
  box=gtk_vbox_new(FALSE,5);

  while(temp!=NULL){
    if(strcmp(texto,temp->Esp1)==0||strcmp(texto,temp->Esp2)==0){

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Nombre:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->NombreD);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Especialidad 1:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->Esp1);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Especialidad 2:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->Esp2);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Telefono de Urgencias:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->TelU);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);\

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Telefono Personal:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->TelN);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Direccion:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->DireccionD);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Consultorio:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->Consultorio);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Horario:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      label=gtk_label_new(temp->Horario);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Dias de consulta:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      boxdias=gtk_vbox_new(TRUE,5);
      for(i=0;i<7;i++){
        if(temp->dias[i]==1){
          label=gtk_label_new(semana[i]);
          gtk_box_pack_start(GTK_BOX(boxdias),label,TRUE,TRUE,0);
        }
      }
      gtk_box_pack_start(GTK_BOX(horizontalbox),boxdias,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

      horizontalbox=gtk_hbox_new(TRUE,5);
      label=gtk_label_new("Estaus:");
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      if(temp->Estatus==0)
        strcpy(texto,"Activo");
      else
        strcpy(texto,"Inactivo");
      label=gtk_label_new(texto);
      gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
      gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);
    }
    temp=temp->sig;
  }
  gtk_box_pack_start(GTK_BOX(swin),box,FALSE,TRUE,0);

  gtk_container_set_border_width (GTK_CONTAINER (swin), 10);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (swin),GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (swin), box);
  gtk_box_pack_start_defaults(GTK_BOX (verticalbox), swin);

  gtk_signal_connect(GTK_OBJECT(window1),"destroy",GTK_SIGNAL_FUNC(Cancelar),window1);

  gtk_box_pack_start(GTK_BOX(verticalbox),box,TRUE,TRUE,0);
  gtk_container_add(GTK_CONTAINER(window1),verticalbox);
  gtk_widget_show_all(window1);
}

void BuscaPaciente(GtkWidget *window, gpointer data){
  tipowidget *datos=(tipowidget *)data;
  tipopacientes *temp;
  GtkWidget *window1,*verticalbox,*horizontalbox,*box,*label,*button,*imagen;
  const gchar *text;
  char texto[200];
  window1=gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window1),400,200);
  gtk_window_move(GTK_WINDOW(window1),560,270);
  gtk_container_border_width(GTK_CONTAINER(window1),5);
  gtk_window_set_title(GTK_WINDOW(window1),"INFORMACION");

  verticalbox=gtk_vbox_new(FALSE,5);
  box=gtk_vbox_new(FALSE,5);

  temp=datos->pinicio;

  text=gtk_entry_get_text(GTK_ENTRY(datos->entrybox[0]));
  strcpy(texto,text);
  box=gtk_vbox_new(FALSE,5);

  while(temp!=NULL&&strcmp(temp->NombreP,texto)!=0)
    temp=temp->sig;

  if(temp!=NULL){
    horizontalbox=gtk_hbox_new(TRUE,5);
    label=gtk_label_new("Nombre:");
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    label=gtk_label_new(temp->NombreP);
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

    horizontalbox=gtk_hbox_new(TRUE,5);
    label=gtk_label_new("Direccion:");
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    label=gtk_label_new(temp->DireccionP);
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

    horizontalbox=gtk_hbox_new(TRUE,5);
    label=gtk_label_new("Telefono:");
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    label=gtk_label_new(temp->TelP);
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

    horizontalbox=gtk_hbox_new(TRUE,5);
    label=gtk_label_new("Sexo:");
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    label=gtk_label_new(temp->Sexo);
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

    horizontalbox=gtk_hbox_new(TRUE,5);
    label=gtk_label_new("Alergias:");
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    label=gtk_label_new(temp->Alergias);
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

    horizontalbox=gtk_hbox_new(TRUE,5);
    label=gtk_label_new("Tipo De Sangre:");
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    label=gtk_label_new(temp->TipoSangre);
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

    horizontalbox=gtk_hbox_new(TRUE,5);
    label=gtk_label_new("Padecimientos Cronicos:");
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    label=gtk_label_new(temp->PadecimientosC);
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

    horizontalbox=gtk_hbox_new(TRUE,5);
    label=gtk_label_new("Fecha De Nacimiento:");
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    label=gtk_label_new(temp->FechaN);
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

    horizontalbox=gtk_hbox_new(TRUE,5);
    label=gtk_label_new("Edad:");
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    sprintf(texto,"%i",temp->Edad);
    label=gtk_label_new(texto);
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);

    horizontalbox=gtk_hbox_new(TRUE,5);
    label=gtk_label_new("Estatura:");
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    sprintf(texto,"%.2f",temp->Estatura);
    label=gtk_label_new(texto);
    gtk_box_pack_start(GTK_BOX(horizontalbox),label,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(box),horizontalbox,TRUE,TRUE,0);
  }
  else{
    verticalbox=gtk_vbox_new(FALSE,5);
  horizontalbox=gtk_hbox_new(TRUE,5);

  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window1),400,200);
  gtk_window_move(GTK_WINDOW(window1),560,270);
  gtk_container_border_width(GTK_CONTAINER(window1),5);
  gtk_window_set_title(GTK_WINDOW(window1),"No Encontrado");

  imagen = gtk_image_new_from_file("noencontrado.jpg");
  gtk_box_pack_start(GTK_BOX(verticalbox),imagen,FALSE,TRUE,0);
  button=AddButton1(verticalbox,"Aceptar",Cancelar,window1);

  gtk_container_add(GTK_CONTAINER(window1),verticalbox);
  gtk_widget_show_all(window1);
  }
  gtk_signal_connect(GTK_OBJECT(window1),"destroy",GTK_SIGNAL_FUNC(Cancelar),window1);

  gtk_box_pack_start(GTK_BOX(verticalbox),box,TRUE,TRUE,0);
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
  gtk_window_set_title(GTK_WINDOW(window1),"No Encontrado");

  imagen = gtk_image_new_from_file("noencontrado.jpg");
  gtk_box_pack_start(GTK_BOX(verticalbox),imagen,FALSE,TRUE,0);
  button=AddButton1(verticalbox,"Aceptar",Cancelar,window1);

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
  GtkWidget *window1;
  GtkWidget *button;
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
  button = AddButton1(verticalbox,"Aceptar",APaciente,datos);
  button = AddButton2(verticalbox,"Cancelar",Cancelar,window1);

  gtk_container_add(GTK_CONTAINER(window1),verticalbox);
  gtk_widget_show_all(window1);
}

void leerdoc(tipodoctores **inicio){
  tipodoctores *nuevo,*avanza;
  FILE *base;
  int i;
  char texto[200];
  base=fopen("doctores.txt","rt");
  if(base!=NULL){
    while(fgets(texto,199,base)!=NULL){
      nuevo=(tipodoctores *)malloc(sizeof(tipodoctores));
      strcpy(nuevo->NombreD,texto);
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
      nuevo->sig=NULL;
      avanza=*inicio;
      if(*inicio!=NULL){
        while(avanza->sig!=NULL)
          avanza=avanza->sig;
        avanza->sig=nuevo;
      }
      else
        *inicio=nuevo;
    }
    fclose(base);
  }
}

void leerpac(tipopacientes **inicio){
  tipopacientes *nuevo,*avanza;
  tipoconsulta *temp;
  FILE *base,*con;
  char texto[200];
  base=fopen("pacientes.txt","rt");
  if(base!=NULL){
    while(fgets(texto,199,base)!=NULL){
      nuevo=(tipopacientes *)malloc(sizeof(tipopacientes));
      strcpy(nuevo->NombreP,texto);
      nuevo->NombreP[strlen(nuevo->NombreP)-1]='\0';
      fgets(nuevo->DireccionP,99,base);
      nuevo->DireccionP[strlen(nuevo->DireccionP)-1]='\0';
      fgets(nuevo->TelP,19,base);
      nuevo->TelP[strlen(nuevo->TelP)-1]='\0';
      fgets(nuevo->Sexo,14,base);
      nuevo->Sexo[strlen(nuevo->Sexo)-1]='\0';
      fgets(nuevo->Alergias,99,base);
      nuevo->Alergias[strlen(nuevo->Alergias)-1]='\0';
      fgets(nuevo->TipoSangre,5,base);
      nuevo->TipoSangre[strlen(nuevo->TipoSangre)-1]='\0';
      fgets(nuevo->PadecimientosC,99,base);
      nuevo->PadecimientosC[strlen(nuevo->PadecimientosC)-1]='\0';
      fgets(nuevo->FechaN,14,base);
      nuevo->FechaN[strlen(nuevo->FechaN)-1]='\0';
      fscanf(base,"%i\n%f\n",&nuevo->Edad,&nuevo->Estatura);
      nuevo->sig=NULL;
      nuevo->inicio=NULL;
      avanza=*inicio;
      if(*inicio!=NULL){
        while(avanza->sig!=NULL)
          avanza=avanza->sig;
        avanza->sig=nuevo;
      }
      else
        *inicio=nuevo;
      strcpy(texto,nuevo->NombreP);
      strcat(texto,".txt");
      con=fopen(texto,"rt");
      if(con!=NULL){
        while(fgets(texto,19,con)!=NULL){
          temp=(tipoconsulta *)malloc(sizeof(tipoconsulta));
          strcpy(temp->FechaC,texto);
          fgets(temp->Dr,199,con);
          fgets(temp->Diagnostico,499,con);
          fgets(temp->Tratamiento,199,con);
          fgets(temp->Anotaciones,199,con);
          temp->FechaC[strlen(temp->FechaC)-1]='\0';
          temp->Dr[strlen(temp->Dr)-1]='\0';
          temp->Diagnostico[strlen(temp->Diagnostico)-1]='\0';
          temp->Tratamiento[strlen(temp->Tratamiento)-1]='\0';
          temp->Anotaciones[strlen(temp->Anotaciones)-1]='\0';
          temp->sig=nuevo->inicio;
          nuevo->inicio=temp;
        }
        fclose(con);
      }
    }
    fclose(base);
  }
}

void escribirdoc(tipodoctores *inicio){
  FILE *base;
  int i;
  tipodoctores *temp;
  temp=inicio;
  base=fopen("doctores.txt","wt");
  while(temp!=NULL){
    fprintf(base,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n",temp->NombreD,temp->Esp1,temp->Esp2,temp->TelU,temp->TelN,temp->DireccionD,temp->Consultorio);
    for(i=0;i<7;i++)
      fprintf(base,"%i\n",temp->dias[i]);
    fprintf(base,"%s\n%i\n",temp->Horario,temp->Estatus);
    temp=temp->sig;
  }
  fclose(base);
}

void escribirpac(tipopacientes *inicio){
  FILE *base,*con;
  tipopacientes *temp;
  tipoconsulta *avanza;
  char texto[200];
  base=fopen("pacientes.txt","wt");
  temp=inicio;
  while(temp!=NULL){
    fputs(temp->NombreP,base);
    fprintf(base,"\n");
    fputs(temp->DireccionP,base);
    fprintf(base,"\n");
    fputs(temp->TelP,base);
    fprintf(base,"\n");
    fputs(temp->Sexo,base);
    fprintf(base,"\n");
    fputs(temp->Alergias,base);
    fprintf(base,"\n");
    fputs(temp->TipoSangre,base);
    fprintf(base,"\n");
    fputs(temp->PadecimientosC,base);
    fprintf(base,"\n");
    fputs(temp->FechaN,base);
    fprintf(base,"\n");
    fprintf(base,"%d\n%f\n",temp->Edad,temp->Estatura);
    avanza=temp->inicio;
    if(avanza!=NULL){
      strcpy(texto,temp->NombreP);
      strcat(texto,".txt");
      con=fopen(texto,"wt");
      while(avanza!=NULL){
        fputs(avanza->FechaC,con);
        fprintf(con,"\n");
        fputs(avanza->Dr,con);
        fprintf(con,"\n");
        fputs(avanza->Diagnostico,con);
        fprintf(con,"\n");
        fputs(avanza->Tratamiento,con);
        fprintf(con,"\n");
        fputs(avanza->Anotaciones,con);
        fprintf(con,"\n");
        avanza=avanza->sig;
      }
    }
    temp=temp->sig;
  }
  fclose(base);
}
