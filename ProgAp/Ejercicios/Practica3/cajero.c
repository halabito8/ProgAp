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


/*************** FUNCION PRINCIPAL ***************/
int main(int argc, char **argv)
{
    int actx, auxx, outcome;




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

void initialise(void)
{
  tipousuario *nuevo,*temp,*inicio=NULL;
  FILE *lectura;
  double d;
  long unsigned ultimo;

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

int NumeroCuenta(void)
{
  tipousuario *temp;
  long unsigned cuenta;
  temp=principio;
  printf("Número de cuenta:  ");
  __fpurge(stdin);
  scanf("%lu",&cuenta);
  while(temp!=NULL&&temp->tarjeta!=cuenta)
    temp=temp->sig;
  if(temp==NULL){
    printf("(T)Numero de cuenta\t (S)alir\n");
  return 0;
  }
  else
    {

    usuario=temp;
    printf("(N)Nip\t(C)Cancelar\n");
    __fpurge(stdin);
    return 1;
  }
}

int MsgBorrar(void)
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

int ExisteNIP(void)
{
  char num[4];
  printf("NIP:");
  __fpurge(stdin);
  gets(num);
  if(strcmp(num, usuario->nip)==0)
    {
    printf("(I)nsertar dinero\t(R)etirar dinero\n(P)nueva contraseña\t(M)ovimientos\n(c)onsultar saldo\t(E)xit\n");
    return 3;
  }
  else
    return 2;
}

int Bitacora(void){
  char nombre[200],basura[200];
  FILE *bit;
  sprintf(nombre,"%lu",usuario->tarjeta);
  bit=fopen(nombre,"rt");
  if(bit!=NULL){
    while(fgets(basura,199,bit)){
      basura[strlen(basura)-1]='\0';
      puts(basura);
    }
    fclose(bit);
  }
  else
    printf("Esta cuenta no ha hecho movimientos\n");
    printf("\n\n(I)nsertar dinero\t(R)etirar dinero\n(P)nueva contraseña\t(M)ovimientos\n(c)onsultar saldo\t(E)xit\n");
}

int MsgInserta(void)
{
  printf("SELECCIONE CUÁNTO DINERO DESEA DEPOSITAR:\n");
  printf("(w)Insertar $1000\n(x)Insertar $2000\n(y)Insertar $3000\n(z)$Insertar $4000\n(o)Escoge cantidad\n");
}

int Cancelar(void)
  {
    printf("Operación cancelada...\n");
    printf("Regresando al menu principal\n");
    printf("\n\n(I)nsertar dinero\t(R)etirar dinero\n(P)nueva contraseña\t(M)ovimientos\n(c)onsultar saldo\t(E)xit\n");
    return 0;
  }

int MsgRetira(void)
{
  printf("SELECCIONE CUÁNTO DINERO DESEA RETIRAR:\n");
  printf("(W)Retirar 1000\n(X) Retirar 2000\n(Y)Retirar 3000\n(Z)Retirar 4000\n(O)Escoge cantidad\n");
  return 4;
}

int MsgContra(void)
{
  printf("CAMBIO DE CONTRASEÑA\n");
  printf("(n)Inserte nueva contraseña\n(B)Cancelar\n");
  return 5;
}

void BitacoraMov(float cantidad,int acc)
{
  FILE *bit;
  char tim[200],nombre[200];
  time_t tiempo;
  struct tm *timo;
  time(&tiempo);
  timo=localtime(&tiempo);
  strftime(tim,sizeof(tim),"%Y%m%d-%H:%M:%S",timo);
  sprintf(nombre,"%lu",usuario->tarjeta);
  bit=fopen(nombre,"at");
  if(acc==1)
    fprintf(bit,"%s Se añadio %.2f\n",tim,cantidad);
  else
    fprintf(bit,"%s Se retiro %.2f\n",tim,cantidad);
  fclose(bit);
}

int ConsultarSaldo(void)
{
  printf("Su saldo es: %.2lf\n",usuario->dinero);
  printf("(I)nsertar dinero\t(R)etirar dinero\n(P)Nueva contraseña\t(M)ovimientos\n(c)Consultar saldo\t(E)xit\n");

}

int Exit(void)
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
  printf("(T)Numero de cuenta\t (S)alir\n");

}

int Inserta1000(void)
{
  float a=1000;
  int b=1;
  printf("Se deposito la cantidad de: $1000\n");
  usuario->dinero=usuario->dinero+1000;
  system("clear");
  printf("(I)nsertar dinero\t(R)etirar dinero\n(P)Nueva contraseña\t(M)ovimientos\n(c)Consultar saldo\t(E)xit\n");
  BitacoraMov(a,b);
}

int Inserta2000(void)
{
  float a=2000;
  int b=1;
  printf("Se deposito la cantidad de: $2000\n");
  usuario->dinero=usuario->dinero+2000;
  system("clear");
  printf("(I)nsertar dinero\t(R)etirar dinero\n(P)Nueva contraseña\t(M)ovimientos\n(c)Consultar saldo\t(E)xit\n");
  BitacoraMov(a,b);
}

int Inserta3000(void)
{
  float a=3000;
  int b=1;
  printf("Se deposito la cantidad de: $3000\n");
  usuario->dinero=usuario->dinero+3000;
  system("clear");
  printf("(I)nsertar dinero\t(R)etirar dinero\n(P)Nueva contraseña\t(M)ovimientos\n(c)Consultar saldo\t(E)xit\n");
  BitacoraMov(a,b);
}

int Inserta4000(void)
{
  float a=4000;
  int b=1;
  printf("Se deposito la cantidad de: $4000\n");
  usuario->dinero=usuario->dinero+4000;
  system("clear");
  printf("(I)nsertar dinero\t(R)etirar dinero\n(P)Nueva contraseña\t(M)ovimientos\n(c)Consultar saldo\t(E)xit\n");
  BitacoraMov(a,b);
}

int EscogeCuanto(void)
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

int Alcanza(void)
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

int Contra(void)
{
  char nueva[50];
  printf("Favor de ingresar su nueva contraseña:\n");
  __fpurge(stdin);
  gets(nueva);
  strcpy(usuario->nip,nueva);
  printf("\n(I)nsertar dinero\t(R)etirar dinero\n(P)nueva contraseña\t(M)ovimientos\n(c)onsultar saldo\t(E)xit\n");
}

int MsgNoValido(void)
{
  printf("NUMERO DE CUENTA INVÁLIDO...\n");
  printf("(T)Numero de cuenta\t (S)alir\n");

}

int NipIncorrecto(void)
{
  printf("NIP INCORRECTO...\n");
  printf("(T)Numero de cuenta\t (S)alir\n");
}

int MsgNoAlcanza(void)
{
  printf("NO TIENES SALDO SUFICIENTE PARA RETIRAR..\n");
  printf("(I)nsertar dinero\t(R)etirar dinero\n(P)nueva contraseña\t(M)ovimientos\n(c)onsultar saldo\t(E)xit\n");
}

int RetiraDinero(void)
{
  printf("Operación finalizada, retire su dinero\n");
  printf("Gracias por utilizar nuestros servicios, elije la opción deseada\n");
  printf("(I)nsertar dinero\t(R)etirar dinero\n(P)nueva contraseña\t(M)ovimientos\n(c)onsultar saldo\t(E)xit\n");
}
