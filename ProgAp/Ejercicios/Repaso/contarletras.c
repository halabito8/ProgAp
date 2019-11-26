#include<stdio.h>
#include<string.h>

void leer(char string[]);
void minusculas(char string[]);
void contar (char string[],int contadora[]);
void imprimir (int contadora[]);

int main(void){
  char string[200];
  int contadora[26]={0};
  leer (string);
  minusculas (string);
  contar(string, contadora);
  imprimir (contadora);
}

void leer(char string[]){
  printf("Dame una frase, maximo de 199 caracteres: ");
  gets(string);
}

void minusculas(char string[]){
  int i;
  for(i=0;i<strlen(string);i++){
    string[i]=tolower(string[i]);
  }
}

void imprimir(int contadora []){
  int i;
  for(i=0;i<26;i++){
    if(contadora[i]!=0)
      printf("El caracter %c aparece %i veces en la funcion.\n", i+'A', contadora[i]);
  }
}

void contar(char string[], int contadora[]){
  int i=0;
  while(string[i]!='\0'){
    if(string[i]>='a'&&string[i]<='z');
      contadora[string[i]-'a']++;
  i++;
  }
}

