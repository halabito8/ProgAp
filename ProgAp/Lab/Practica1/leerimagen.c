#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct defimagen{
  int y,x,shades;
  char p,numero;
  unsigned char **lista;
}tipoimagen;

void leer(tipoimagen foto[]){
  int i,j;
  char nombre[200];
  FILE *algo;
  printf("Como se llama la imagen que quiere editar?\n");
  gets(nombre);
  algo=fopen(nombre,"rb");
  if(algo==NULL){
    printf("Ese archivo no existe.\n");
    printf("Saliendo del programa...\n");
    exit(0);
  }
  else{
    fscanf(algo,"%c%c %i %i %i ",&foto[0].p,&foto[0].numero,&foto[0].x,&foto[0].y,&foto[0].shades);
    foto[0].lista=(unsigned char**)malloc(sizeof(unsigned char*)*foto[0].y);
    for(i=0;i<foto[0].y;i++)
      foto[0].lista[i]=(unsigned char*)malloc(sizeof(unsigned char)*foto[0].x);
  }
  for(i=0;i<foto[0].y;i++){
    for(j=0;j<foto[0].x;j++)
      fread(&foto[0].lista[i][j],sizeof(unsigned char),1,algo);
  }
  fclose(algo);
}
