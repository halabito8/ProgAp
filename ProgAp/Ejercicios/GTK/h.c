#include<stdio.h>
#include <string.h>

int main(void){
  char g[7];
  FILE *j;
  j=fopen("hola dav.txt","rt");
  fgets(g,7,j);
  puts(g);
}
