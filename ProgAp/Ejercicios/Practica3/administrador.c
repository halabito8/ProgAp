#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct usuario{
  char nombre[200],nip[6];
  long unsigned tarjeta;
  double dinero;
  struct usuario *sig;
}tipousuario;

void leer(tipousuario **inicio,unsigned long *ultimo);
void alta(tipousuario **inicio,unsigned long *ultimo);
void escribir(tipousuario *inicio,unsigned long ultimo);
void imprimir(tipousuario *inicio);
void borrar(tipousuario *inicio);

int main(void){
  unsigned long ultimo;
  tipousuario *inicio=NULL;
  int op,i=0;
  leer(&inicio,&ultimo);
  do{
    printf("Que quiere hacer?\n1. Alta usuario\n2. Ver lista de usuarios\n3. Salir\nOpcion: ");
    __fpurge(stdin);
    scanf("%i",&op);
    switch(op){
      case 1:
        alta(&inicio,&ultimo);
      break;
      case 2:
        imprimir(inicio);
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
  escribir(inicio,ultimo);
  borrar(inicio);
}

void alta(tipousuario **inicio,unsigned long *ultimo){
  tipousuario *nuevo,*temp;
  nuevo=(tipousuario*)malloc(sizeof(tipousuario));
  printf("Cual es el nombre del cuentahabiente?\n");
  __fpurge(stdin);
  gets(nuevo->nombre);
  (*ultimo)++;
  printf("Su cuenta tiene el numero: %lu\n",*ultimo);
  nuevo->tarjeta=(*ultimo);
  printf("Cual es el nip?\n");
  __fpurge(stdin);
  gets(nuevo->nip);
  nuevo->dinero=0;
  nuevo->sig=NULL;
  if(*inicio!=NULL){
    temp=*inicio;
    while(temp->sig!=NULL)
      temp=temp->sig;
    temp->sig=nuevo;
  }
  else
    *inicio=nuevo;
}

void leer(tipousuario **inicio,unsigned long *ultimo){
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
      if(*inicio!=NULL){
        temp=*inicio;
        while(temp->sig!=NULL)
          temp=temp->sig;
        temp->sig=nuevo;
      }
      else
        *inicio=nuevo;
    }
    fclose(lectura);
  }
  lectura=fopen("ultus.txt","rt");
  fscanf(lectura,"%lu",ultimo);
  fclose(lectura);
}

void escribir(tipousuario *inicio,unsigned long ultimo){
  tipousuario *viejo;
  FILE *escritura;
  escritura=fopen("usuarios.txt","wt");
  if(escritura!=NULL){
    viejo=inicio;
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

void imprimir(tipousuario *inicio){
  tipousuario *temp;
  temp=inicio;
  while(temp!=NULL){
    printf("Usuario: %s, Tarjeta: %lu, Nip: %s, Dinero: %.2lf\n",temp->nombre,temp->tarjeta,temp->nip,temp->dinero);
    temp=temp->sig;
  }
}

void borrar(tipousuario *inicio){
  tipousuario *temp;
  while(inicio!=NULL){
    temp=inicio;
    inicio=temp->sig;
    free(temp);
  }
}
