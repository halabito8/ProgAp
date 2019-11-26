#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct defdato{
  int dato;
  struct defdato *sig;
  struct defdato *ant;
}tipodato;

void Menu();
void InsertaInicio(tipodato **Inicio,tipodato **final);
void Imprime(tipodato *Inicio);
void BorrarLista(tipodato *Inicio);
void imprimereves(tipodato *final);

int main(void){
  tipodato *primero=NULL,*final=NULL;
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
      system("clear");
    case 1:
      InsertaInicio(&primero,&final);
    break;
    case 2:
      Imprime(primero);
    break;
      case 3:
        imprimereves(final);
      break;
    case 4:
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


void InsertaInicio(tipodato **Inicio,tipodato **final){
  int numero;
  tipodato *temp,*temp2,*temp3;
  printf("Inserta un numero.\n");
  scanf("%i",&numero);
  temp=(tipodato*)malloc(sizeof(tipodato));
  temp->dato=numero;
  temp->sig=NULL;
  temp->ant=NULL;
  if(*Inicio!=NULL){
    temp2=*Inicio;
    while(temp2!=NULL&&numero>temp2->dato)
      temp2=temp2->sig;
    if(temp2==NULL){
      temp2=*Inicio;
      while(temp2->sig!=NULL)
        temp2=temp2->sig;
      temp2->sig=temp;
      temp->ant=temp2;
      *final=temp;
    }
    else if(temp2==*Inicio){
      temp2=*Inicio;
      temp2->ant=temp;
      temp->sig=temp2;
      *Inicio=temp;
    }
    else{
      temp3=*Inicio;
      while(temp3->sig!=temp2)
        temp3=temp3->sig;
      temp->sig=temp2;
      temp->ant=temp3;
      temp2->ant=temp;
      temp3->sig=temp;
    }
  }
  else{
    *Inicio=temp;
    *final=temp;
  }
}


void Imprime(tipodato *Inicio){
  tipodato *temp;
  temp=Inicio;
  while(temp!=NULL){
      printf("%i\n",temp->dato);
      temp=temp->sig;
    }
}

void imprimereves(tipodato *final){
  tipodato *temp;
  temp=final;
  while(temp!=NULL){
      printf("%i\n",temp->dato);
      temp=temp->ant;
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
  printf("2. Imprimir todos los numeros\n3. Imprimir al reves\n4. Salir\n");
}
