#include<stdio.h>
#include<stdlib.h>

typedef struct nodo{
  char dato;
  struct nodo *der,*izq;
}tiponodo;

void insertar(tiponodo *raiz,tiponodo *nuevo);
void imprime(tiponodo *raiz);
void borra(tiponodo *raiz);

int main(void){
  char letra;
  tiponodo *raiz,*nuevo;
  raiz=NULL;
  printf("Inserta letras, teclea un numero para acabar.\n");
  do{
    __fpurge(stdin);
    scanf("%c",&letra);
    if((letra>='a'&&letra<='z')||(letra>='A'&&letra<='Z')){
      nuevo=(struct nodo*)malloc(sizeof(struct nodo));
      nuevo->dato=letra;
      nuevo->izq=NULL;
      nuevo->der=NULL;
      if(raiz==NULL)
        raiz=nuevo;
      else
        insertar(raiz,nuevo);
    }
  }while((letra>='a'&&letra<='z')||(letra>='A'&&letra<='Z'));
  printf("Sus letras en orden son:\n");
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
  struct nodo *temp,*temp2=NULL;
  if(raiz!=NULL){
    while(raiz!=NULL){
      temp=raiz;
      if(temp->izq!=NULL&&temp!=temp2)
        temp=temp->izq;
      else{
        printf("%c",temp->dato);
        temp2=temp;
      }
      if(temp->der!=NULL&&temp!=temp2)
        temp=temp->der;
    }
  }
  else
    printf("No hay nada en el arbol.\n");
}

void borra(tiponodo *raiz){
  //Lo borramos en post orden
  if(raiz!=NULL){
    borra(raiz->izq);
    borra(raiz->der);
    free(raiz);
  }
}
