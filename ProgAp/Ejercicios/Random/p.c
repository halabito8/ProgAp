#include<stdio.h>
#include<string.h>

int main(void){
  int pos;
  char string[20],car;
  printf("Cadena\n");
  gets(string);
  printf("Pos?\n");
  scanf("%i",&pos);
  car=string[pos];
  printf("%c\n",car);
}
