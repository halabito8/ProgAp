/****************************************************************
 *								*
 * Archivo:	state_mach1.c					*
 * Descripcion: Codigo Fuente para implementar el programa	*
 *		de maquina de estados.			 	*
 *								*
 ****************************************************************/

/*************** ARCHIVOS DE INCLUSION ***************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tables.h"


/*************** VARIABLES GLOBALES ***************/
EVENT event;
int state;
char buf[BUFFER];

/*************** PROTOTIPOS DE FUNCION ***************/
void initialise(void);
void getevent(void);

int NumeroCuenta(void);
int MsgBorrar(void);
int ExisteNIP(void);
int MsgInserta(void);
int MsgRetira(void);
int MsgContra(void);
void BitacoraMov(float cantidad,int acc);
int ConsultarSaldo(void);
int Exit(void);
int Inserta1000(void);
int Inserta2000(void);
int Inserta3000(void);
int Inserta4000(void);
int EscogeCuanto(void);
int Alcanza(void);
int Contra(void);
int Cancelar(void);
int MsgNoValido(void);
int NipIncorrecto(void);
int MsgNoAlcanza(void);
int RetiraDinero(void);
int ExisteNIP(void);
int Bitacora(void);
int nul(void);
void leer(void);
void alta(void);
void escribir(void);
void imprimir(void);
void borrar(void);


/*************** FUNCION PRINCIPAL ***************/
int main(int argc, char **argv)
{
  int actx, auxx, outcome;

  if(argc==2)
    {
      if((strcmp(argv[1],"-c"))==0)
	{
	  leer();
	  do{
	    system("clear");
	    printf("Que quiere hacer?\n1. Alta usuario\n2. Ver lista de usuarios\n3. Salir\nOpcion: ");
	    __fpurge(stdin);
	    scanf("%i",&op);
	    switch(op){
	    case 1:
	      alta();
	      break;
	    case 2:
	      imprimir();
	      break;
	    case 3:
	      i=1;
	      printf("Adios\n");
	      break;
	    default:
	      printf("Escoja una opcion correcta\n");
	      break;
	    }
	  }while(i==0);
	  escribir();
	  borrar();
	}
    }
  else{
    initialise();

    while (1) {    /* loop infinito para la MFE */
      getevent();

      for ((actx = state_table[state].start);(action_table[actx].event != event.etype) && (actx < state_table[state].end);actx++)
	;
    outcome = (*(action_table[actx].action))();
    if(action_table[actx].moreacts == -1)
      state = action_table[actx].nextstate;
    else {
      auxx = action_table[actx].moreacts + outcome;
      while (auxx != -1){
	outcome = (*(aux_table[auxx].action))();
	if (aux_table[auxx].moreacts == -1 ){
	  state = aux_table[auxx].nextstate;
	  auxx = -1;
	}
	else
	  auxx = aux_table[auxx].moreacts + outcome;

      }
    }
  }
  } /* while(1) */
}

void getevent(void)
{
  char *ptmp;
  ptmp = &buf[2];

#ifdef DEBUG
  printf("wait event \n");
#endif
  __fpurge(stdin);
  gets(buf);

  switch (buf[0])
    {
    case 'T' :
      event.etype=T;
      break;
    case 'C' :
      event.etype=C;
      system("clear");
      printf("(T)Numero de cuenta\t (S)alir\n");
      break;
    case 'S' :
      event.etype=S;
      break;
    case 'N' :
      event.etype=N;
      break;
    case 'I' :
      event.etype=I;
      break;
    case 'R' :
      event.etype=R;
      break;
    case 'P' :
      event.etype=P;
      break;
    case 'M' :
      event.etype=M;
      break;
    case 'c' :
      event.etype=c;
      break;
    case 'E' :
      event.etype=E;
      break;
    case 'w' :
      event.etype=w;
      break;
    case 'x' :
      event.etype=x;
      break;
    case 'y' :
      event.etype=y;
      break;
    case 'z' :
      event.etype=z;
      break;
    case 'o' :
      event.etype=o;
      break;
    case 'W' :
      retira=1000;
      event.etype=W;
      break;
    case 'X' :
      retira=2000;
      event.etype=X;
      break;
    case 'Y' :
      retira=3000;
      event.etype=Y;
      break;
    case 'Z' :
      retira=4000;
      event.etype=Z;
      break;
    case 'O' :
      printf("Cuanto quiere retirar?\n");
      scanf("%f",&retira);
      event.etype=O;
      break;
    case 'n' :
      event.etype=n;
      break;
    case 'B' :
      event.etype=B;
      break;
    default:
      event.etype=-1;
      break;

    }//switch
}// getevent


/**********************************FUNCION QUE INICIA EL PROGRAMA DE LA MÁQUINA DE ESTADO**********************************/
void initialise(void)
{
  char i,j;
  tipousuario *nuevo,*temp,*inicio=NULL;
  FILE *lectura;
  double d;
  long unsigned ultimo;
  system("clear");
  printf("Maria Gabriela Uribe\nDavid Halabe Husny\nEmanuel Zuriel Bajonero\n");
  i=getchar();
  system("sleep 1");
  printf("DESCRIPCIÓN DEL PROGRAMA:\nEste pograma ejecuta la simulación de un cajero automático. El diseño y el programa se realizaron mediante el método de maquina de estado.El programa simula de manera completa los estados de un cajero convencional con el uso de listas dinámicas como variable global");
  getchar();

  system("clear");
  state=0;
  lectura=fopen("usuarios.txt","rt");
  if(lectura!=NULL){
    while(fscanf(lectura,"%lf\n",&d)==1){
      nuevo=(tipousuario*)malloc(sizeof(tipousuario));
      nuevo->dinero=d;
      fgets(nuevo->nombre,199,lectura);
      fgets(nuevo->nip,5,lectura);
      fscanf(lectura,"%lu\n",&nuevo->tarjeta);
      nuevo->nombre[strlen(nuevo->nombre)-1]='\0';
      nuevo->nip[4]='\0';
      nuevo->sig=NULL;
      if(inicio!=NULL){
        temp=inicio;
        while(temp->sig!=NULL)
          temp=temp->sig;
        temp->sig=nuevo;
      }
      else
        inicio=nuevo;
    }
    fclose(lectura);
  }
  principio=inicio;
  printf("(T)Numero de cuenta\t (S)alir\n");
}

/* FUNCIONES DE IMPLEMENTACION */


int nul(void)
{
}//nul




/***********************************************************************************************************/

int NumeroCuenta(void)//FUNCION QUE VALIDA SI EL NUMERO DE CUENTA ES CORRECTO O INCORRECTO, RECORRIENDO LA LISTA DINÁMICA
{
  tipousuario *temp;
  long unsigned cuenta;
  temp=principio;
  system("clear");
  printf("Número de cuenta:  ");
  __fpurge(stdin);
  scanf("%lu",&cuenta);
  __fpurge(stdin);
  while(temp!=NULL&&temp->tarjeta!=cuenta)
    temp=temp->sig;
  if(temp==NULL){
    system("clear");
    printf("(T)Numero de cuenta\t (S)alir\n");
    return 0;
  }
  else
    {

      usuario=temp;
      system("clear");
      printf("(N)Nip\t(C)Cancelar\n");
      __fpurge(stdin);
      return 1;
    }
}

int MsgBorrar(void) //FUNCION QUE INDICA AL USUARIO QUE ESTÁ SALIENDO DEL PROGRAMA Y QUE BORRA LA LISTA DINÁMICA DE MEMORIA
{
  tipousuario *temp;
  while(principio!=NULL){
    temp=principio;
    principio=temp->sig;
    free(temp);
  }
  printf("SALIENDO DEL PROGRAMA....\n\n");
  exit(0);
}

int ExisteNIP(void)// FUNCIÓN QUE VALIDA SI EL NIP DEL USUARIO ES CORRECTO O INCORRECTO CON UN STRING COMPARE
{
  char num[4];
  printf("NIP:");
  __fpurge(stdin);
  gets(num);
  if(strcmp(num, usuario->nip)==0)
    {
      system("clear");
      printf("(I)nsertar dinero\t(R)etirar dinero\n(P)nueva contraseña\t(M)ovimientos\n(c)onsultar saldo\t(E)xit\n");
      return 3;
    }
  else
    return 2;
}

int Bitacora(void)// FUNCION QUE IMPRIME EN PANTALLA LOS MOVIMIENTOS QUE HA HECHO EL USUARIO, REFIRIENDOSE A DEPÓSITO O RETIRO
{
  char nombre[200],basura[200];
  FILE *bit;
  sprintf(nombre,"%lu",usuario->tarjeta);
  strcat(nombre,".txt");
  bit=fopen(nombre,"rt");
  if(bit!=NULL){
    while(fgets(basura,199,bit)){
      basura[strlen(basura)-1]='\0';
      puts(basura);
    }
    fclose(bit);
    printf("inserte cualquie tecla para continuar");
    getchar();
    system("sleep 1.5");
  }
  else{
    printf("Esta cuenta no ha hecho movimientos\n");
  system("sleep 1.5");
  }
  system("clear");
  printf("(I)nsertar dinero\t(R)etirar dinero\n(P)nueva contraseña\t(M)ovimientos\n(c)onsultar saldo\t(E)xit\n");
}

int MsgInserta(void)//FUNCION QUE LE MANDA UN MENSAJE AL USUARIO PARA QUE ELIJA CUÁNTO DINERO QUIERE DEPOSITAR
{
  system("clear");
  printf("SELECCIONE CUÁNTO DINERO DESEA DEPOSITAR:\n");
  printf("(w)Insertar $1000\n(x)Insertar $2000\n(y)Insertar $3000\n(z)$Insertar $4000\n(o)Escoge cantidad\n");
}

int Cancelar(void)//FUNCIÓN QUE LE MANDA UN MENSAJE AL USUARIO, INDICANDO QUE SE CANCELA EL CAMBIO DE CONTRASEÑA
{
  printf("Operación cancelada...\n");
  system("sleep 1.5");
  printf("Regresando al menu principal\n");
  system("sleep 1.5");
  system("clear");
  printf("(I)nsertar dinero\t(R)etirar dinero\n(P)nueva contraseña\t(M)ovimientos\n(c)onsultar saldo\t(E)xit\n");
  return 0;
}

int MsgRetira(void)//FUNCIÓN QUE LE PREGUNTA AL USUARIO CUÁNTO DESEA RETIRAR MANDANDO EN PANTALLA UN MENSAJE
{
  system("clear");
  printf("SELECCIONE CUÁNTO DINERO DESEA RETIRAR:\n");
  printf("(W)Retirar 1000\n(X) Retirar 2000\n(Y)Retirar 3000\n(Z)Retirar 4000\n(O)Escoge cantidad\n");
  return 4;
}

int MsgContra(void)//FUNCION QUE IMPRIME UN MENSAJE AL USUARIO PREGUNTANDO SI DESEA CAMBIAR CONTRASEÑA O DESEA CANCELAR
{
  system("clear");
  printf("CAMBIO DE CONTRASEÑA\n");
  printf("(n)Inserte nueva contraseña\n(B)Cancelar\n");
  return 5;
}

void BitacoraMov(float cantidad,int acc)// FUNCION QUE IMPRIME EN EL ARCHIVO LOS MOVIMIENTOS QUE HA HECHO EL USUARIO, REFIRIENDOSE A DEPÓSITO O RETIRO
{
  FILE *bit;
  char tim[200],nombre[200];
  time_t tiempo;
  struct tm *timo;
  time(&tiempo);
  timo=localtime(&tiempo);
  strftime(tim,sizeof(tim),"%Y%m%d-%H:%M:%S",timo);
  sprintf(nombre,"%lu",usuario->tarjeta);
  strcat(nombre,".txt");
  bit=fopen(nombre,"at");
  if(acc==1)
    fprintf(bit,"%s Se añadio %.2f\n",tim,cantidad);
  else
    fprintf(bit,"%s Se retiro %.2f\n",tim,cantidad);
  fclose(bit);
}

int ConsultarSaldo(void)//FUNCION QUE IMPRIME EL SALDO DISPONIBLE DEL USUARIO
{
  system("clear");
  printf("Su saldo es: %.2lf\n",usuario->dinero);
  system("sleep 1.5");
  printf("(I)nsertar dinero\t(R)etirar dinero\n(P)Nueva contraseña\t(M)ovimientos\n(c)Consultar saldo\t(E)xit\n");

}

int Exit(void)//FUNCIÓN QUE REGRESA AL MENÚ PRINCIPAL DEL ESTADO DE MOVIMIENTOS AL ESTADO DE ESPERA
{
  tipousuario *viejo;
  FILE *escritura;
  escritura=fopen("usuarios.txt","wt");
  if(escritura!=NULL){
    viejo=principio;
    while(viejo!=NULL){
      fprintf(escritura,"%lf\n",viejo->dinero);
      fputs(viejo->nombre,escritura);
      fprintf(escritura,"\n");
      fputs(viejo->nip,escritura);
      fprintf(escritura,"\n");
      fprintf(escritura,"%lu\n",viejo->tarjeta);
      viejo=viejo->sig;
    }
    fclose(escritura);
  }
  printf("Regresando al menu principal...\n");
  system("sleep 1.5");
  system("clear");
  printf("(T)Numero de cuenta\t (S)alir\n");

}

int Inserta1000(void)//FUNCION QUE DEPOSITA 1000
{
  float a=1000;
  int b=1;
  printf("Se deposito la cantidad de: $1000\n");
  usuario->dinero=usuario->dinero+1000;
  system("clear");
  printf("(I)nsertar dinero\t(R)etirar dinero\n(P)Nueva contraseña\t(M)ovimientos\n(c)Consultar saldo\t(E)xit\n");
  BitacoraMov(a,b);
}

int Inserta2000(void)//FUNCION QUE DEPOSITA 2000
{
  float a=2000;
  int b=1;
  printf("Se deposito la cantidad de: $2000\n");
  usuario->dinero=usuario->dinero+2000;
  system("clear");
  printf("(I)nsertar dinero\t(R)etirar dinero\n(P)Nueva contraseña\t(M)ovimientos\n(c)Consultar saldo\t(E)xit\n");
  BitacoraMov(a,b);
}

int Inserta3000(void)//FUNCION QUE DEPOSITA 3000
{
  float a=3000;
  int b=1;
  printf("Se deposito la cantidad de: $3000\n");
  usuario->dinero=usuario->dinero+3000;
  system("clear");
  printf("(I)nsertar dinero\t(R)etirar dinero\n(P)Nueva contraseña\t(M)ovimientos\n(c)Consultar saldo\t(E)xit\n");
  BitacoraMov(a,b);
}

int Inserta4000(void)//FUNCION QUE DEPOSITA 4000
{
  float a=4000;
  int b=1;
  printf("Se deposito la cantidad de: $4000\n");
  usuario->dinero=usuario->dinero+4000;
  system("clear");
  printf("(I)nsertar dinero\t(R)etirar dinero\n(P)Nueva contraseña\t(M)ovimientos\n(c)Consultar saldo\t(E)xit\n");
  BitacoraMov(a,b);
}

int EscogeCuanto(void)//FUNCION QUE DEPOSITA LO QUE DESEE EL  USUARIO
{
  float inserta;
  int b=1;
  printf("Inserte la cantidad que desea depositar:\n");
  __fpurge(stdin);
  scanf("%f", &inserta);
  printf("Se deposito la cantidad de: %f\n", inserta);
  usuario->dinero=usuario->dinero+inserta;
  system("clear");
  printf("(I)nsertar dinero\t(R)etirar dinero\n(P)Nueva contraseña\t(M)ovimientos\n(c)Consultar saldo\t(E)xit\n");
  BitacoraMov(inserta,b);
}

int Alcanza(void)//FUNCIÓN QUE VALIDA SU AL USUARIO LE ALCANZA PARA RETIRAR DINERO O NO
{
  int b=2;
  if(usuario->dinero>=retira){
    usuario->dinero-=retira;
    BitacoraMov(retira,b);
    return 5;
  }
  else{
    printf("No tines suficiente dinero\n");
    return 4;
  }
}

int Contra(void)//FUNCION QUE CAMBIA LA CONTRASEÑA
{
  char nueva[50];
  printf("Favor de ingresar su nueva contraseña:\n");
  __fpurge(stdin);
  gets(nueva);
  strcpy(usuario->nip,nueva);
  system("clear");
  printf("\n(I)nsertar dinero\t(R)etirar dinero\n(P)nueva contraseña\t(M)ovimientos\n(c)onsultar saldo\t(E)xit\n");
}

int MsgNoValido(void)
{
  printf("NUMERO DE CUENTA INVÁLIDO...\n");
  system("sleep 1.5");
  system("clear");
  printf("(T)Numero de cuenta\t (S)alir\n");

}

int NipIncorrecto(void)
{
  printf("NIP INCORRECTO...\n");
  system("sleep 1.5");
  system("clear");
  printf("(T)Numero de cuenta\t (S)alir\n");
}

int MsgNoAlcanza(void)
{
  printf("NO TIENES SALDO SUFICIENTE PARA RETIRAR..\n");
  system("sleep 1.5");
  system("clear");
  printf("(I)nsertar dinero\t(R)etirar dinero\n(P)nueva contraseña\t(M)ovimientos\n(c)onsultar saldo\t(E)xit\n");
}

int RetiraDinero(void)
{
  printf("Operación finalizada, retire su dinero\n");
  system("sleep 1.5");
  printf("Gracias por utilizar nuestros servicios, elije la opción deseada\n");
  system("sleep 1.5");
  system("clear");
  printf("(I)nsertar dinero\t(R)etirar dinero\n(P)nueva contraseña\t(M)ovimientos\n(c)onsultar saldo\t(E)xit\n");
}







/*******************************************************************************************************************************/
/*****************************************************FUNCIONES DE ADMINISTRADOR************************************************/
/*******************************************************************************************************************************/

void alta(void){
  tipousuario *nuevo,*temp;
  nuevo=(tipousuario*)malloc(sizeof(tipousuario));
  printf("Cual es el nombre del cuentahabiente?\n");
  __fpurge(stdin);
  gets(nuevo->nombre);
  (ultimo)++;
  printf("Su cuenta tiene el numero: %lu\n",ultimo);
  nuevo->tarjeta=(ultimo);
  printf("Cual es el nip?\n");
  __fpurge(stdin);
  gets(nuevo->nip);
  nuevo->dinero=0;
  nuevo->sig=NULL;
  if(principio!=NULL){
    temp=principio;
    while(temp->sig!=NULL)
      temp=temp->sig;
    temp->sig=nuevo;
  }
  else
    principio=nuevo;
}

void leer(void){
  tipousuario *nuevo,*temp;
  FILE *lectura;
  double d;
  lectura=fopen("usuarios.txt","rt");
  if(lectura!=NULL){
    while(fscanf(lectura,"%lf\n",&d)==1){
      nuevo=(tipousuario*)malloc(sizeof(tipousuario));
      nuevo->dinero=d;
      fgets(nuevo->nombre,199,lectura);
      fgets(nuevo->nip,5,lectura);
      fscanf(lectura,"%lu\n",&nuevo->tarjeta);
      nuevo->nombre[strlen(nuevo->nombre)-1]='\0';
      nuevo->nip[4]='\0';
      nuevo->sig=NULL;
      if(principio!=NULL){
        temp=principio;
        while(temp->sig!=NULL)
          temp=temp->sig;
        temp->sig=nuevo;
      }
      else
        principio=nuevo;
    }
    fclose(lectura);
  }
  lectura=fopen("ultus.txt","rt");
  fscanf(lectura,"%lu",&ultimo);
  fclose(lectura);
}

void escribir(void){
  tipousuario *viejo;
  FILE *escritura;
  escritura=fopen("usuarios.txt","wt");
  if(escritura!=NULL){
    viejo=principio;
    while(viejo!=NULL){
      fprintf(escritura,"%lf\n",viejo->dinero);
      fputs(viejo->nombre,escritura);
      fprintf(escritura,"\n");
      fputs(viejo->nip,escritura);
      fprintf(escritura,"\n");
      fprintf(escritura,"%lu\n",viejo->tarjeta);
      viejo=viejo->sig;
    }
    fclose(escritura);
  }
  escritura=fopen("ultus.txt","wt");
  fprintf(escritura,"%lu",ultimo);
  fclose(escritura);
}

void imprimir(void){
  tipousuario *temp;
  temp=principio;
  while(temp!=NULL){
    printf("Usuario: %s, Tarjeta: %lu, Nip: %s, Dinero: %.2lf\n",temp->nombre,temp->tarjeta,temp->nip,temp->dinero);
    temp=temp->sig;
  }
  printf("\nOprima cualquier tecla para continuar");
  getchar();
  getchar();
  system("sleep 1.5");
}

void borrar(void){
  tipousuario *temp;
  while(principio!=NULL){
    temp=principio;
    principio=temp->sig;
    free(temp);
  }
}
