#include<stdio.h>
#include<stdlib.h>

typedef struct nodo{
  int dato;
  struct nodo *der,*izq;
}tiponodo;

void insertar(tiponodo *raiz,tiponodo *nuevo);
void imprime(tiponodo *raiz);
void borra(tiponodo *raiz);
void elimina(tiponodo *raiz,tiponodo *avanza);
void encuentra(tiponodo *raiz);

int main(void){
  int numero,op,i=0;
  tiponodo *raiz,*nuevo;
  raiz=NULL;
  do{
    printf("Que quieres hacer?\n1. Insertar numero\n2. Eliminar numero\n3. Imprimir todo\n4. Salir\nOpcion: ");
    scanf("%i",&op);
    switch(op){
      case 1:
        scanf("%i",&numero);
        nuevo=(struct nodo*)malloc(sizeof(struct nodo));
        nuevo->dato=numero;
        nuevo->izq=NULL;
        nuevo->der=NULL;
        if(raiz==NULL)
          raiz=nuevo;
        else
          insertar(raiz,nuevo);
      break;
      case 3:
        if(raiz!=NULL)
          imprime(raiz);
        else
          printf("No hay numeros insertados\n");
      break;
      default:
        printf("Elige una opcion valida");
      break;
      case 2:
        if(raiz!=NULL)
          encuentra(raiz);
        else
          printf("No hay numeros insertados\n");
      break;
      case 4:
        printf("Adios\n");
        i=1;
      break;
    }
  }while(i==0);
  borra(raiz);
}

void encuentra(tiponodo *raiz){
  int elim;
  tiponodo *avanza;
  avanza=raiz;
  printf("Que numero quieres eliminar?\n");
  scanf("%i",&elim);
  if(elim>avanza->dato){
    if(avanza->der!=NULL)
      encuentra(raiz->der);
    else
      printf("Ese numero no existe en la lista\n");
  }
  if(elim<=avanza->dato){
    if(avanza->izq!=NULL&&elim!=avanza->dato)
      encuentra(raiz->izq);
    else
      elimina(raiz,avanza);
  }
}

void elimina(tiponodo *raiz,tiponodo *avanza){
  tiponodo *comp;
  comp=raiz;
  printf("En construccion\n");
}

void insertar(tiponodo *raiz,tiponodo *nuevo){
  tiponodo *avanza;
  avanza=raiz;
  if(avanza!=NULL){
    if(nuevo->dato>avanza->dato){
      if(avanza->der!=NULL)
        insertar(raiz->der,nuevo);
      else{
        avanza->der=nuevo;
        return;
      }
    }
    if(nuevo->dato<=avanza->dato){
      if(avanza->izq!=NULL)
        insertar(raiz->izq,nuevo);
      else{
        avanza->izq=nuevo;
        return;
      }
    }
  }
}

void imprime(tiponodo *raiz){
  if(raiz!=NULL){
    imprime(raiz->izq);
    printf("%i\n",raiz->dato);
    imprime(raiz->der);
  }
}

void borra(tiponodo *raiz){
  if(raiz!=NULL){
    borra(raiz->izq);
    borra(raiz->der);
    free(raiz);
  }
}
