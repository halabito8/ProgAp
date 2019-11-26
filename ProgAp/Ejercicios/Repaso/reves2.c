#include<stdio.h>
#include<string.h>

void reves(char *frase);

int main(void){
  char linea[201];
  printf("Dame una frase de hasta 200 caracteres.\n");
  gets(linea);
  reves(linea);
  printf("Tu frase volteada es:\n");
  puts(linea);
}

void reves(char *frase){
  int i,j,mitad;
  char temp;
  j=strlen(frase)-1;
  mitad=strlen(frase)/2;
  if(mitad%2==0){
    for(i=0;i<mitad;i++){
      temp=frase[i];
      frase[i]=frase[j];
      frase[j]=temp;
      j--;
    }
  }
  else{
    for(i=0;i<=mitad;i++){
      temp=frase[i];
      frase[i]=frase[j];
      frase[j]=temp;
      j--;
    }
  }
  frase[strlen(frase)]='\0';
}
