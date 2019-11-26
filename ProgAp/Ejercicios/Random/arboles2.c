#include<stdio.h>
#include<stdlib.h>

typedef struct nodo{
  int dato;
  struct nodo *der,*izq;
}tiponodo;

void insertar(tiponodo *raiz,tiponodo *nuevo);
void imprime(tiponodo *raiz);
void borra(tiponodo *raiz);

int main(void){
  int numero;
  tiponodo *raiz,*nuevo;
  raiz=NULL;
  printf("Inserta numeros enteros, teclea una letra para acabar.\n");
  while(scanf("%i",&numero)==1){
    nuevo=(struct nodo*)malloc(sizeof(struct nodo));
    nuevo->dato=numero;
    nuevo->izq=NULL;
    nuevo->der=NULL;
    if(raiz==NULL)
      raiz=nuevo;
    else
      insertar(raiz,nuevo);
  }
  printf("Sus numeros en orden son:\n");
  imprime(raiz);
  borra(raiz);
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
