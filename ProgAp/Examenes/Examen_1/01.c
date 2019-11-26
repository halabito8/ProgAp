#include<stdio.h>
#include <string.h>
#include <stdlib.h>


int main(void){
  int min=0,may=0,letras=0,pal=0,esp=0,i;
  char nombre[200],temp[1000];
  FILE *algo;
  printf("Como se llama el archivo?\n");
  gets(nombre);
  algo=fopen(nombre,"rt");
  while(fgets(temp,1000,algo)){
    temp[strlen(temp)-1]='\0';
    pal++;
    if(temp[strlen(temp)-1]==' ')
      pal--;
    for(i=0;i<strlen(temp);i++){
      if(temp[i]<='z'&&temp[i]>='a')
        min++;
      if(temp[i]>='A'&&temp[i]<='Z')
        may++;
      if(temp[i]==' ')
        esp++;
      letras=min+may;
      if((temp[i]==' '&&temp[i-1]!=' ')||(temp[i]=='\0'&&temp[i-1]!=' '))
        pal++;
    }
  }
  printf("En el documento aparecen %i minusculas.\n",min);
  printf("En el documento aparecen %i mayusculas.\n",may);
  printf("En el documento aparecen %i espacios.\n",esp);
  printf("En el documento aparecen %i letras.\n",letras);
  printf("En el documento aparecen %i palabras.\n",pal);
}
