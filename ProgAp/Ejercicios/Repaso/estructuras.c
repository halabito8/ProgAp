#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct defempleado{
  char nombre[200];
  int edad;
  int dia;
  int mes;
  int ano;
  int sueldo;
  struct defempleado *sig;
}tipoempleado;

void BorrarLista(tipoempleado *Inicio);
void nuevo(tipoempleado **Inicio,int *cantidad);
void imprimir(tipoempleado *Inicio);
void pornombre(tipoempleado *Inicio);
void viejo(tipoempleado *Inicio);

int main(void){
  tipoempleado *principio=NULL;
  int i=0,opcion,cantidad=0;
  do{
    printf("Que desea hacer?\n1. Nuevo empleado\n2. Buscar por nombre\n3. Buscar por antiguedad\n4. Imprimir todo\n5. Despedir a alguien\n6. Salir\nOpcion: ");
    scanf("%i",&opcion);
    switch(opcion){
      case 1:
        system("clear");
        if(cantidad>=10)
          printf("Ya tienes muchos empleados.\n");
        else
          nuevo(&principio,&cantidad);
      break;
      case 2:
        system("clear");
        pornombre(principio);
      break;
      case 3:
        system("clear");
        viejo(principio);
      break;
      case 4:
        system("clear");
        imprimir(principio);
      break;
      case 5:
        system("clear");
        printf("\nNo puedes hacer eso eres el Dios de la misericordia.\n\n");
      break;
      case 6:
        system("clear");
        printf("Adios vaquero!\n");
        i=1;
      break;
      default:
        system("clear");
        printf("Escoge una opcion valida.\n");
      break;
    }
  }while(i==0);
  BorrarLista(principio);
}


void BorrarLista(tipoempleado *Inicio){
  tipoempleado *temp;
  temp=Inicio;
  while(temp!=NULL){
    Inicio=Inicio->sig;
    free(temp);
    temp=Inicio;
  }
}

void nuevo(tipoempleado **Inicio,int *cantidad){
  tipoempleado *temp,*temp2;
  int val;
  temp2=*Inicio;
  temp=(tipoempleado*)malloc(sizeof(tipoempleado));
  printf("Nombre del empleado?\n");
  __fpurge(stdin);
  gets(temp->nombre);
  printf("Que edad tiene?\n");
  __fpurge(stdin);
  scanf("%i",&temp->edad);
  printf("Cuanto le va a pagar por sus 'servicios'\n");
  __fpurge(stdin);
  scanf("%i",&temp->sueldo);
  printf("Que tacano...\n\n");
  do{
    printf("Que dia entra a trabajar?\nFavor de poner la fecha en formato dd/mm/aaaa\n");
    __fpurge(stdin);
    val=scanf("%i/%i/%i",&temp->dia,&temp->mes,&temp->ano);
    if(val!=3)
      printf("Porfavor llene todos los campos.\n");
  }while(val!=3);
  temp->sig=NULL;
  if(*Inicio!=NULL){
    while(temp2->sig!=NULL)
      temp2=temp2->sig;
    temp2->sig=temp;
  }
  else
    *Inicio=temp;
  (*cantidad)++;
}

void imprimir(tipoempleado *Inicio){
  tipoempleado *temp;
  temp=Inicio;
  if(Inicio==NULL)
    printf("Nadie trabaja contigo\n");
  while(temp!=NULL){
    puts(temp->nombre);
    printf("Tiene: %i anos.\nEntro el dia %i/%i/%i.\nY se le paga %i.\n\n",temp->edad,temp->dia,temp->mes,temp->ano,temp->sueldo);
    temp=temp->sig;
  }
}

void pornombre(tipoempleado *Inicio){
  char busca[200];
  tipoempleado *temp;
  temp=Inicio;
  printf("Que empleado desea buscar?\n");
  __fpurge(stdin);
  gets(busca);
  while(temp!=NULL&&strcmp(busca,temp->nombre)!=0)
    temp=temp->sig;
  if(temp==NULL)
    printf("Ese empleado no existe o lo escribio mal.\n");
  else{
    printf("Tiene: %i anos.\nEntro el dia %i/%i/%i.\nY se le paga %i.\n",temp->edad,temp->dia,temp->mes,temp->ano,temp->sueldo);
  }
}

void viejo(tipoempleado *Inicio){
  int busca;
  tipoempleado *temp;
  temp=Inicio;
  printf("Desde que ano buscas?\n");
  scanf("%i",&busca);
  while(temp!=NULL){
    if(temp->ano>=busca){
      puts(temp->nombre);
      printf("Tiene: %i anos.\nEntro el dia %i/%i/%i.\nY se le paga %i.\n",temp->edad,temp->dia,temp->mes,temp->ano,temp->sueldo);
    }
    temp=temp->sig;
  }
}

