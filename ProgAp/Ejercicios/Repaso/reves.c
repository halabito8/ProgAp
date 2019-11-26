#include<stdio.h>
#include<string.h>

void reves(char *frase,char *volteado);

int main(void){
  char linea[201],volteado[201];
  printf("Dame una frase de hasta 200 caracteres.\n");
  gets(linea);
  reves(linea,volteado);
  printf("Tu frase volteada es:\n");
  puts(volteado);
}

void reves(char *frase,char *volteado){
  int i,j=strlen(frase)-1;
  for(i=0;i<strlen(frase);i++){
      *(volteado+i)=*(frase+j);
      j--;
  }
  *(volteado+strlen(frase))='\0';
}
