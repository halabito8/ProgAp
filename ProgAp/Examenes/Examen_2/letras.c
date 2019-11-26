#include<stdio.h>
#include<stdlib.h>

typedef struct nodo{
  char dato;
  struct nodo *der,*izq;
}tiponodo;

void insertar(tiponodo *raiz,tiponodo *nuevo);
void altura(tiponodo *raiz,int *conta,int actual);
void hojas(tiponodo *raiz,int *conta);
void nodos(tiponodo *raiz,int *conta);
void imprime(tiponodo *raiz);
void borra(tiponodo *raiz);

int main(void){
  int op,i=0,conta=0,actual=0;
  char letra,nombre[200];
  tiponodo *raiz,*nuevo;
  FILE *algo;
  raiz=NULL;
  printf("Que archivo se va a leer?\n");
  __fpurge(stdin);
  gets(nombre);
  algo=fopen(nombre,"rt");
  if(algo!=NULL){
    while(fscanf(algo,"%c\n",&letra)==1){
      nuevo=(struct nodo*)malloc(sizeof(struct nodo));
      nuevo->dato=letra;
      nuevo->izq=NULL;
      nuevo->der=NULL;
      if(raiz==NULL)
        raiz=nuevo;
      else
        insertar(raiz,nuevo);
    }
  }
  else{
    printf("No existe el archivo\n");
    exit(0);
  }
  fclose(algo);
  do{
    printf("1. Imprimir en orden\n2. Numero de nodos\n3. Altura de arbol\n4. Numero de hojas\n5. Salir\nOpcion: ");
    __fpurge(stdin);
    scanf("%i",&op);
    switch(op){
      case 1:
        printf("Sus letras en orden son:\n");
        imprime(raiz);
        break;
        case 5:
          printf("Adios\n");
          i=1;
        break;
        case 2:
          nodos(raiz,&conta);
          printf("Hay %i nodos en el arbol\n",conta);
          conta=0;
        break;
        case 4:
          hojas(raiz,&conta);
          printf("Hay %i hojas en el arbol\n",conta);
          conta=0;
        break;
        case 3:
          altura(raiz,&conta,actual);
          printf("El arbol tiene una altura de %i\n",conta);
          conta=0;
        break;
        default:
          printf("Escoja una opcion valida\n");
        break;
    }
  }while(i==0);
  borra(raiz);
}

void altura(tiponodo *raiz,int *conta,int actual){
  if(raiz!=NULL){
    if(raiz->der!=NULL||raiz->izq!=NULL)
      actual++;
    if(actual>*conta)
      *conta=actual;
    altura(raiz->izq,conta,actual);
    altura(raiz->der,conta,actual);
  }
}

void hojas(tiponodo *raiz, int *contadora){
  if(raiz!=NULL){
    if(raiz->der==NULL&&raiz->izq==NULL)
      (*contadora)++;
    hojas(raiz->izq,contadora);
    hojas(raiz->der,contadora);
  }
}

void nodos(tiponodo *raiz,int *contadora){
  if(raiz!=NULL){
    (*contadora)++;
    nodos(raiz->izq,contadora);
    nodos(raiz->der,contadora);
  }
}

void imprime(tiponodo *raiz){
  //Recorremos el arbol en orden
  if(raiz!=NULL){
    imprime(raiz->izq);
    printf("%c\n",raiz->dato);
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
