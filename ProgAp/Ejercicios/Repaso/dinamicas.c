#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct defdato{
  int dato;
  struct defdato *sig;
}tipodato;

void Menu();
void InsertaInicio(tipodato **Inicio);
void Imprime(tipodato *Inicio);
void BorrarLista(tipodato *Inicio);

int main(void){
  tipodato *primero=NULL;
  int op,i=0,val;
  do{
    Menu();
    do{
      printf("Opcion: ");
      __fpurge(stdin);
      val=scanf("%i",&op);
      if(val!=1)
	printf("Las opciones solo son numeros.\n");
    }while(val!=1);
    switch(op){
    case 1:
      InsertaInicio(&primero);
      break;
    case 2:
      Imprime(primero);
      break;
    case 3:
      i=1;
      printf("Bueno... cada quien sus cubas...\n");
      break;
    default:
      printf("Inserta una opcion valida!\n");
      break;
    }
  }while(i==0);
  BorrarLista(primero);
}


void InsertaInicio(tipodato **Inicio){
  tipodato *temp;
  int val,numero;
  temp=(tipodato*)malloc(sizeof(tipodato));
  do{
    printf("Inserta tu numero.\n");
    __fpurge(stdin);
    val=scanf("%i",&numero);
    if(val!=1)
      printf("Dije numero...\n");
  }while(val!=1);
  temp->dato=numero;
  temp->sig=*Inicio;
  *Inicio=temp;
}


void Imprime(tipodato *Inicio){
  tipodato *temp;
  temp=Inicio;
  while(temp!=NULL){
      printf("%i\n",temp->dato);
      temp=temp->sig;
    }
}


void BorrarLista(tipodato *Inicio){
  tipodato *temp;
  temp=Inicio;
  while(temp!=NULL){
      Inicio=Inicio->sig;
      free(temp);
      temp=Inicio;
    }
}

void Menu(void){
  printf("Que desea hacer?\n1. Ingresar un numero\n");
  printf("2. Imprmir todos los numeros\n3. Salir\n");
}
