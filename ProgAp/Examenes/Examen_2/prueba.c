#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){
  int total=0;
  char reci[200],nombre[200],letra;
  FILE *algo;
  printf("Que archivo se va a leer?\n");
  __fpurge(stdin);
  gets(nombre);
  algo=fopen(nombre,"rt");
  if(algo!=NULL){
    while(fgets(reci,199,algo)){
      if(letra!=' ')
        reci[strlen(reci)]=letra;
      else{
        reci[strlen(reci)]=letra;
        puts(reci);
        total++;
      }
    }
  }
  printf("%i\n",total);
}
