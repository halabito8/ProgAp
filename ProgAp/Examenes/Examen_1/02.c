#include<stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct documento{
  int id;
  int hojas;
  char nombre[200];
  int impresas;
  struct documento *ant;
  struct documento *sig;
}tipodocumento;

void nuevo(tipodocumento **Inicio,int *id,tipodocumento **fin);
void todo(tipodocumento *Inicio,tipodocumento *fin);
void eliminar(tipodocumento **Inicio,tipodocumento **fin);
void imprimir(tipodocumento **Inicio,tipodocumento **fin);
void guardar(tipodocumento *Inicio,tipodocumento *fin);
void leer(tipodocumento **Inicio,int *id,tipodocumento **fin);
void borrar(tipodocumento *Inicio);

int main(void){
  tipodocumento *principio=NULL,*fin=NULL;
  int op,val,i=0,id=100;
  system("clear");
  do{
    printf("Que quieres hacer?\n1. Introducir nuevo documento a la cola\n2. Ver cola de impresion\n3. Eliminar documento de la cola de impresion\n");
    printf("4. Imprimir documento\n5. Guardar cola en Archivo\n6. Leer cola de archivos\n7. Salir\n");
    do{
      printf("Opcion: ");
      __fpurge(stdin);
      val=scanf("%i",&op);
    }while(val!=1);
    switch(op){
      case 1:
        system("clear");
        nuevo(&principio,&id,&fin);
        system("clear");
      break;
      case 2:
        system("clear");
        todo(principio,fin);
      break;
      case 3:
        system("clear");
        eliminar(&principio,&fin);
      break;
      case 6:
        system("clear");
        leer(&principio,&id,&fin);
        system("clear");
        printf("Se ha leido tu cola de impresion con exito\n");
      break;
      case 5:
        system("clear");
        guardar(principio,fin);
        system("clear");
        printf("Se ha guardado tu cola de impresion exitosamente!\n");
      break;
      case 4:
        system("clear");
        imprimir(&principio,&fin);
      break;
      case 7:
        printf("Hasta luego.\n");
        i=1;
      break;
      default:
        printf("Porfavor selecciones una opcion valida\n");
      break;
    }
  }while(i!=1);
  borrar(principio);
}

void imprimir(tipodocumento **Inicio,tipodocumento **fin){
  tipodocumento *temp,*temp2;
  if(*Inicio!=NULL){
    temp=*Inicio;
    temp->impresas++;
    if(temp->hojas==temp->impresas){
      temp2=temp;
      if(temp->sig!=NULL){
        *Inicio=temp->sig;
        temp=temp->sig;
        temp->ant=NULL;
        free(temp2);
      }
      else{
        *Inicio=NULL;
        free(temp);
      }
    }
    printf("Hoja imprimida\n");
  }
  else
    printf("No hay documentos en la cola de impresion.\n");
}

void nuevo(tipodocumento **Inicio,int *id,tipodocumento **fin){
  tipodocumento *temp,*temp2;
  temp=(tipodocumento*)malloc(sizeof(tipodocumento));
  printf("Nombre del documento?\n");
  __fpurge(stdin);
  gets(temp->nombre);
  printf("Cuantas hojas tiene?\n");
  __fpurge(stdin);
  scanf("%i",&temp->hojas);
  temp->id=*id;
  (*id)++;
  temp->impresas=0;
  temp->ant=NULL;
  temp->sig=NULL;
  if(*Inicio!=NULL){
    temp2=*Inicio;
    while(temp2->sig!=NULL)
      temp2=temp2->sig;
    temp2->sig=temp;
    temp->ant=temp2;
    *fin=temp;
  }
  else{
    *Inicio=temp;
    *fin=temp;
  }
}

void borrar(tipodocumento *Inicio){
  tipodocumento *temp;
  temp=Inicio;
  while(temp!=NULL){
    Inicio=temp->sig;
    free(temp);
    temp=Inicio;
  }
}

void todo(tipodocumento *Inicio,tipodocumento *fin){
  tipodocumento *temp;
  temp=fin;
  if(Inicio!=NULL){
    while(temp!=NULL){
      printf("%i: %s, %i hojas, ",temp->id,temp->nombre,temp->hojas);
      if(temp==Inicio)
        printf("imprimiendo, %i hojas impresas.\n",temp->impresas);
      else
        printf("espera.\n");
      temp=temp->ant;
    }
  }
else
  printf("No hay documentos en la cola de impresion.\n");
}

void eliminar(tipodocumento **Inicio,tipodocumento **fin){
  int busca;
  tipodocumento *temp,*temp2,*temp3;
  temp=*Inicio;
  if(*Inicio!=NULL){
    printf("Que numero de documento quieres eliminar?\n");
    __fpurge(stdin);
    scanf("%i",&busca);
    while(temp!=NULL&&temp->id!=busca)
      temp=temp->sig;
    if(temp==NULL)
      printf("No existe el documento con ese ID.\n");
    else{
      if(temp==*Inicio){
        temp2=temp;
        *Inicio=temp->sig;
        temp->ant=NULL;
        free(temp2);
      }
      else if(temp->sig==NULL){
          temp2=temp->ant;
          temp2->sig=NULL;
          *fin=temp2;
          free(temp);
      }
      else{
        temp2=*Inicio;
        while(temp2->sig!=temp)
          temp2=temp2->sig;
        temp3=temp->sig;
        temp3->ant=temp2;
        temp2->sig=temp->sig;
        free(temp);
      }
    }
  }
  else
    printf("No hay documentos en la cola de impresion.\n");
}

void guardar(tipodocumento *Inicio,tipodocumento *fin){
  char nombre[200];
  FILE *algo;
  tipodocumento *temp;
  temp=Inicio;
  if(Inicio!=NULL){
    printf("En que archivo quieres guardar tu cola de impresion?\n");
    __fpurge(stdin);
    gets(nombre);
    algo=fopen(nombre,"wt");
    while(temp!=NULL){
      fputs(temp->nombre,algo);
      fprintf(algo,"\n%i\n%i\n",temp->hojas,temp->impresas);
      temp=temp->sig;
    }
  }
  else
    printf("No hay documentos en la cola de impresion.\n");
}

void leer(tipodocumento **Inicio,int *id,tipodocumento **fin){
  char nombre[200],leer[200];
  FILE *algo;
  tipodocumento *temp,*temp2;
  printf("En que archivo esta tu cola de impresion?\n");
  __fpurge(stdin);
  gets(nombre);
  algo=fopen(nombre,"rt");
  while(fgets(leer,200,algo)){
    temp=(tipodocumento*)malloc(sizeof(tipodocumento));
    leer[strlen(leer)-1]='\0';
    strcpy(temp->nombre,leer);
    fscanf(algo,"%i\n%i\n",&temp->hojas,&temp->impresas);
    temp->id=*id;
    (*id)++;
    temp->ant=NULL;
    temp->sig=NULL;
    if(*Inicio!=NULL){
      temp2=*Inicio;
      while(temp2->sig!=NULL)
        temp2=temp2->sig;
      temp2->sig=temp;
      temp->ant=temp2;
      *fin=temp;
    }
    else{
      *Inicio=temp;
      *fin=temp;
    }
  }
}
