#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"leerimagen.c"
#include "imprimirimagen.c"

extern void guardar(tipoimagen foto[]);
extern void leer(tipoimagen foto[]);
void negativo(tipoimagen foto[]);
void ecualizar(tipoimagen foto[]);
void ampliar(tipoimagen foto[]);
void reducir(tipoimagen foto[]);
void liberar(tipoimagen foto[]);

int main(void){
  int i=0,op,val;
  char t;
  tipoimagen foto[2];
  system("clear");
  printf("Creado por: David Halabe 209707.\nPresione enter para continuar.\n");
  t=getchar();
  system("clear");
  leer(foto);
  system("clear");
  do{
    do{
      printf("Que quieres hacer?\n1. Negativo\n2. Ecualizar\n3. Ampliar\n4. Reducir\n5. Salir\nOpcion: ");
      __fpurge(stdin);
      val=scanf("%i",&op);
    }while(val!=1);
    switch(op){
      case 1:
        system("clear");
        negativo(foto);
      break;
      case 2:
        system("clear");
        ecualizar(foto);
      break;
      case 3:
        system("clear");
        ampliar(foto);
      break;
      case 4:
        system("clear");
        reducir(foto);
      break;
      case 5:
        system("clear");
        printf("Hasta luego!\n");
        i=1;
      break;
      default:
        printf("Porfavor selecciona una opcion valida.\n");
      break;
    }
    system("clear");
    printf("Foto procesada correctamente.\n");
  }while(i!=1);
  liberar(foto);
}

void negativo(tipoimagen foto[]){
  int i,j;
  foto[1].y=foto[0].y;
  foto[1].x=foto[0].x;
  foto[1].lista=(unsigned char**)malloc(sizeof(unsigned char*)*foto[1].y);
  for(i=0;i<foto[1].y;i++)
    foto[1].lista[i]=(unsigned char*)malloc(sizeof(unsigned char)*foto[1].x);
  for(i=0;i<foto[1].y;i++){
    for(j=0;j<foto[1].x;j++)
      foto[1].lista[i][j]=-foto[0].lista[i][j]+255;
  }
  guardar(foto);
}

void ecualizar(tipoimagen foto[]){
  int i,j;
  unsigned char min=255,max=0;
  float m,b;
  foto[1].y=foto[0].y;
  foto[1].x=foto[0].x;
  foto[1].lista=(unsigned char**)malloc(sizeof(unsigned char*)*foto[1].y);
  for(i=0;i<foto[1].y;i++)
    foto[1].lista[i]=(unsigned char*)malloc(sizeof(unsigned char)*foto[1].x);
  for(i=0;i<foto[0].y;i++){
    for(j=0;j<foto[0].x;j++){
        if(foto[0].lista[i][j]>max)
          max=foto[0].lista[i][j];
        if(foto[0].lista[i][j]<min)
          min=foto[0].lista[i][j];
    }
  }
  m=255.0/(float)(max-min);
  b=-(m*min);
  for(i=0;i<foto[1].y;i++){
    for(j=0;j<foto[1].x;j++){
      foto[1].lista[i][j]=((foto[0].lista[i][j]*m)+(b));
    }
  }
  guardar(foto);
}

void ampliar(tipoimagen foto[]){
  int i,j;
  foto[1].y=foto[0].y*2;
  foto[1].x=foto[0].x*2;
  foto[1].lista=(unsigned char**)malloc(sizeof(unsigned char*)*foto[1].y);
  for(i=0;i<foto[1].y;i++)
    foto[1].lista[i]=(unsigned char*)malloc(sizeof(unsigned char)*foto[1].x);
  for(i=0;i<foto[1].y;i+=2){
    for(j=0;j<foto[1].x;j+=2){
      foto[1].lista[i][j]=foto[0].lista[i/2][j/2];
      foto[1].lista[i+1][j]=foto[0].lista[i/2][j/2];
      foto[1].lista[i][j+1]=foto[0].lista[i/2][j/2];
      foto[1].lista[i+1][j+1]=foto[0].lista[i/2][j/2];
    }
  }
  guardar(foto);
}

void reducir(tipoimagen foto[]){
  int i,j;
  foto[1].y=foto[0].y/2;
  foto[1].x=foto[0].x/2;
  foto[1].lista=(unsigned char**)malloc(sizeof(unsigned char*)*foto[1].y);
  for(i=0;i<foto[1].y;i++)
    foto[1].lista[i]=(unsigned char*)malloc(sizeof(unsigned char)*foto[1].x);
  for(i=0;i<foto[0].y;i++){
    for(j=0;j<foto[0].x;j++)
      foto[1].lista[i/2][j/2]=foto[0].lista[i][j];
  }
  guardar(foto);
}

void liberar(tipoimagen foto[]){
  int i,j;
  for(j=0;j<2;j++){
    for(i=0;i<foto[j].y;i++){
      free(foto[j].lista[i]);
    }
    free(foto[j].lista);
  }
}
