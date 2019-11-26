#include<stdio.h>
#include"sumar.c"

extern void sumar(int *i);

int main(void){
  int k;
  printf("Numero?\n");
  scanf("%i",&k);
  sumar(&k);
  printf("%i\n",k);
}
