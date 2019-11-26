#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void guardar(tipoimagen foto[]){
  int i,j;
  char nombre[200];
  FILE *algo;
  printf("Bajo que nombre quieres guardar la nueva imagen?\n");
  __fpurge(stdin);
  gets(nombre);
  algo=fopen(nombre,"wt");
  fprintf(algo,"P5 %i %i %i ",foto[1].x,foto[1].y,foto[0].shades);
  for(i=0;i<foto[1].y;i++){
    for(j=0;j<foto[1].x;j++)
      fprintf(algo,"%c",foto[1].lista[i][j]);
  }
  fclose(algo);
}
