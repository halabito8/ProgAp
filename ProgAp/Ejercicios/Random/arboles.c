#include<stdio.h>
#include<stdlib.h>

typedef struct nodo{
  int dato;
  struct nodo *der,*izq;
}tiponodo;

void insertar(tiponodo **raiz,int numero);
void imprime(tiponodo *raiz);
void borra(tiponodo *raiz);

int main(void){
  int numero;
  tiponodo *raiz;
  raiz=NULL;
  printf("Inserta numeros enteros, teclea una letra para acabar.\n");
  while(scanf("%i",&numero)==1)
    insertar(&raiz,numero);
  printf("Sus numeros en orden son:\n");
  imprime(raiz);
  borra(raiz);
}

void insertar(tiponodo **raiz,int numero){
  tiponodo *avanza,*nuevo;
  avanza=*raiz;
  if((nuevo=(struct nodo*)malloc(sizeof(struct nodo)))==NULL){
    printf("No hay memoria.\n");
    exit(1);
  }
  nuevo->dato=numero;
  nuevo->izq=NULL;
  nuevo->der=NULL;
  while(avanza!=NULL){
    if(numero>avanza->dato){
      if(avanza->der!=NULL)
        avanza=avanza->der;
      else{
        avanza->der=nuevo;
        return;
      }
    }
    if(numero<=avanza->dato){
      if(avanza->izq!=NULL)
        avanza=avanza->izq;
      else{
        avanza->izq=nuevo;
        return;
      }
    }
  }
  avanza=nuevo;
  *raiz=avanza;
}

void imprime(tiponodo *raiz){
  //Esto se llama imprimir en orden
  if(raiz!=NULL){
    imprime(raiz->izq);
    printf("%i\n",raiz->dato);
    imprime(raiz->der);
  }
}

void borra(tiponodo *raiz){
  //Lo borramos en post orden
  if(raiz!=NULL){
    borra(raiz->izq);
    borra(raiz->der);
    free(raiz);
  }
}
