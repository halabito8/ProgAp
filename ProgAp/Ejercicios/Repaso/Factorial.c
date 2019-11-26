#include<stdio.h>

void factorial(int num,long unsigned *fac);

int main (void){
  int num;
  unsigned long fac=1;
  printf ("Introduzca un numero: ");
  scanf ("%i",&num);
  factorial(num,&fac);
  printf ("El factorial de %i es: %lu\n",num,fac);
}

void factorial(int num,long unsigned *fac){
  if(num>0){
    *fac=(*fac)*num;
    factorial(num-1,fac);
  }
}
