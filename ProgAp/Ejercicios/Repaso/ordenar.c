#include<stdio.h>

void pedir(int array[100],int *numero);
void ordenar(int array[100],int *insertados,int numero);
void imprimir(int array[100],int insertados);

int main(void){
  int array[100],i,largo,insertados=0,numero;
  do{
    printf("Cuantos numeros va a introducir (menos de 100)?\n");
    fflush(stdin);
    scanf("%i",&largo);
    if(largo>100)
      printf("Introdujiste un numero mayor a 100.\n");
  }while(largo>100);
  for(i=0;i<largo;i++){
    pedir(array,&numero);
    ordenar(array,&insertados,numero);
  }
  imprimir(array,insertados);
}

void pedir(int array[100],int *numero){
  printf("Introduzca un valor\n");
  fflush(stdin);
  scanf("%i",numero);
}

void ordenar(int array[100],int *insertados,int numero){
  int i=0,j;
  if(*insertados!=0){
    while(i<*insertados&&array[i]<numero)
      i++;
    if(i==*insertados)
      array[i]=numero;
    else{
      for(j=*insertados-1;j>=i;j--)
        array[j+1]=array[j];
      array[i]=numero;
    }
  }
  else
    array[0]=numero;
  (*insertados)++;
}

void imprimir(int array[100],int insertados){
  int i;
  printf("Los numeros son:\n");
  for(i=0;i<insertados;i++)
    printf("%i\n",array[i]);
}
