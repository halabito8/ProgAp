#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct defempleado{
  char nombre[200];
  int edad;
  int dia;
  int mes;
  int ano;
  float sueldo;
}tipoempleado;

void nbuscar(tipoempleado empleado[],int cantidad);
void mayusculas(tipoempleado empleado[],char mayu[],int i);
void nuevo(tipoempleado empleado[],int *cantidad);
void imprimir(tipoempleado empleado[],int cantidad);
void pornombre(tipoempleado empleado[],int cantidad);
void viejo(tipoempleado empleado[],int cantidad);

int main(void){
    tipoempleado empleado[10];
    int i=0,opcion,cantidad=0;
    system("clear");
    do{
      printf("Que desea hacer?\n1. Nuevo empleado\n2. Buscar por nombre\n3. Buscar por antiguedad\n4. Imprimir todo\n5. Despedir a alguien\n6. Pasar a mayusculas\n7. Salir\nOpcion: ");
      scanf("%i",&opcion);
      switch(opcion){
        case 1:
          system("clear");
          if(cantidad>=10)
            printf("Ya tienes muchos empleados.\n");
          else
            nuevo(empleado,&cantidad);
          system("clear");
        break;
        case 2:
          system("clear");
          pornombre(empleado,cantidad);
        break;
        case 3:
          system("clear");
          viejo(empleado,cantidad);
        break;
        case 4:
          system("clear");
          imprimir(empleado,cantidad);
        break;
        case 5:
          system("clear");
          printf("\nNo puedes hacer eso eres el Dios de la misericordia.\n\n");
        break;
        case 6:
          system("clear");
          nbuscar(empleado,cantidad);
        break;
        case 7:
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
}

void nuevo(tipoempleado empleado[],int *cantidad){
  int val,val1;
  printf("Nombre del empleado?\n");
    __fpurge(stdin);
    gets(empleado[*cantidad].nombre);
    do{
      printf("Que edad tiene?\n");
      __fpurge(stdin);
      val1=scanf("%i",&empleado[*cantidad].edad);
      if(val1!=1)
        printf("Las edades solo son numeros.\n");
    }while(val1!=1);
    printf("Cuanto le va a pagar por sus 'servicios'?\n");
    __fpurge(stdin);
    scanf("%f",&empleado[*cantidad].sueldo);
    printf("Que tacano...\n\n");
    do{
      printf("Que dia entra a trabajar?\nFavor de poner la fecha en formato dd/mm/aaaa\n");
      __fpurge(stdin);
      val=scanf("%i/%i/%i",&empleado[*cantidad].dia,&empleado[*cantidad].mes,&empleado[*cantidad].ano);
      if(val!=3)
        printf("Porfavor llene todos los campos.\n");
    }while(val!=3);
    (*cantidad)++;
}

void pornombre(tipoempleado empleado[],int cantidad){
  int i=0;
  char busca[200];
  printf("Que empleado desea buscar?\n");
  __fpurge(stdin);
  gets(busca);
  system("clear");
  while(i<=cantidad&&strcmp(busca,empleado[i].nombre)!=0)
    i++;
  if(i>cantidad)
    printf("Ese empleado no existe o lo escribio mal.\n");
  else{
    printf("%s\nTiene: %i anos.\nEntro el dia %i/%i/%i.\nY se le paga %.2f.\n\n",empleado[i].nombre,empleado[i].edad,empleado[i].dia,empleado[i].mes,empleado[i].ano,empleado[i].sueldo);
  }
}

void viejo(tipoempleado empleado[],int cantidad){
  int i,busca;
  printf("Desde que ano busca?\n");
  scanf("%i",&busca);
  system("clear");
  for(i=0;i<cantidad;i++){
    if(empleado[i].ano>=busca)
      printf("%s\nTiene: %i anos.\nEntro el dia %i/%i/%i.\nY se le paga %.2f.\n\n",empleado[i].nombre,empleado[i].edad,empleado[i].dia,empleado[i].mes,empleado[i].ano,empleado[i].sueldo);
  }
}

void imprimir(tipoempleado empleado[],int cantidad){
  int i;
  if(cantidad==0)
    printf("Nadie trabaja contigo\n");
  else{
    for(i=0;i<cantidad;i++)
      printf("%s\nTiene: %i anos.\nEntro el dia %i/%i/%i.\nY se le paga %.2f.\n\n",empleado[i].nombre,empleado[i].edad,empleado[i].dia,empleado[i].mes,empleado[i].ano,empleado[i].sueldo);
  }
}

void nbuscar(tipoempleado empleado[],int cantidad){
  int i=0;
  char busca[200];
  printf("Que empleado quiere pasar a mayusculas?\n");
  __fpurge(stdin);
  gets(busca);
  while (strcmp(empleado[i].nombre,busca)!=0&&i<cantidad) {
    i++;
  }
  if(i==cantidad)
    printf("Ese empleado no existe o lo escribio mal.\n");
  else
    mayusculas(empleado,busca,i);
}

void mayusculas(tipoempleado empleado[],char mayu[],int i){
  int j;
  for(j=0;j<strlen(mayu);j++)
    mayu[j]=toupper(mayu[j]);
  strcpy(empleado[i].nombre,mayu);
}

