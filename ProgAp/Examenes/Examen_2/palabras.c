#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct codigo{
  char palabra[200];
  float probabilidad;
  int suma;
  struct codigo *sig;
  struct codigo *izq,*der;
}tipocodigo;

void leer(tipocodigo **inicio,int *total);
void calcular(tipocodigo *inicio,int total,tipocodigo **inicior);
void arbol(tipocodigo *inicior,tipocodigo **raiz);
void borrar(tipocodigo *inicio,tipocodigo *inicior);
void impcod(tipocodigo *raiz);

int main(void){
  int total=0;
  tipocodigo *inicio=NULL,*raiz=NULL,*inicior=NULL;
  leer(&inicio,&total);
  calcular(inicio,total,&inicior);
  arbol(inicior,&raiz);
  impcod(raiz);
  borrar(inicio,inicior);
}

void arbol(tipocodigo *inicior,tipocodigo **raiz){
  tipocodigo *flex,*flex2,*nuevo;
  while(inicior!=NULL){
    flex=inicior;
    nuevo=(tipocodigo*)malloc(sizeof(tipocodigo));
    nuevo->suma=0;
    nuevo->izq=flex;
    nuevo->der=flex->sig;
    nuevo->probabilidad=flex->probabilidad+flex->sig->probabilidad;
    *raiz=nuevo;
    inicior=flex->sig->sig;
    if(nuevo->probabilidad!=100){
      flex=inicior;
      while(flex!=NULL&&flex->probabilidad<nuevo->probabilidad)
        flex=flex->sig;
      if(flex==NULL){
        flex=inicior;
        while(flex->sig!=NULL)
          flex=flex->sig;
        flex->sig=nuevo;
      }
      else if(flex==inicior){
        nuevo->sig=inicior;
        inicior=nuevo;
      }
      else{
        flex2=inicior;
        while(flex2->sig!=flex)
          flex2=flex2->sig;
        nuevo->sig=flex;
        flex2->sig=nuevo;
      }
    }
  }
}

void impcod(tipocodigo *raiz){
  if(raiz!=NULL){
      impcod(raiz->izq);
      if(raiz->suma!=0)
	     printf("Simbolo %s\n",raiz->palabra);
      impcod(raiz->der);
    }
}


void calcular(tipocodigo *inicio,int total,tipocodigo **inicior){
  tipocodigo *flex,*flex2,*flex3;
  flex=inicio;
  while(flex!=NULL){
    flex->probabilidad=flex->suma/total;
    flex=flex->sig;
    flex2=*inicior;
    while(flex2!=NULL&&flex2->probabilidad>flex->probabilidad)
      flex2=flex->sig;
    if(flex2==NULL){
      flex2=*inicior;
      while(flex2->sig!=NULL)
        flex2=flex2->sig;
      flex2->sig=flex;
    }
    else if(flex2==*inicior){
      flex->sig=*inicior;
      *inicior=flex;
    }
    else{
      flex2=*inicior;
      while(flex3->sig!=flex2)
        flex3=flex->sig;
      flex3->sig=flex;
      flex->sig=flex2;
    }
  }
}

void leer(tipocodigo **inicio,int *total){
  tipocodigo *nuevo,*avanza,*temp;
  char reci[200],nombre[200];
  FILE *algo;
  printf("Que archivo se va a leer?\n");
  __fpurge(stdin);
  gets(nombre);
  algo=fopen(nombre,"rt");
  if(algo!=NULL){
    while(fgets(reci,199,algo)){
      reci[strlen(reci)-1]='\0';
      (*total)++;
      temp=*inicio;
      avanza=*inicio;
      while(avanza!=NULL&&strcmp(reci,avanza->palabra)!=0)
        avanza=avanza->sig;
      if(avanza==NULL){
        nuevo=(tipocodigo*)malloc(sizeof(tipocodigo));
        strcpy(nuevo->palabra,reci);
        nuevo->suma=1;
        nuevo->sig=NULL;
        nuevo->der=NULL;
        nuevo->izq=NULL;
        if(*inicio!=NULL){
          while(temp->sig!=NULL)
            temp=temp->sig;
          temp->sig=nuevo;
        }
        else
          *inicio=nuevo;
      }
      else
        avanza->suma++;
    }
  fclose(algo);
  }
  else{
    printf("No existe el archivo\n");
    exit(0);
  }
}

void borrar(tipocodigo *inicio,tipocodigo *inicior){
  tipocodigo *temp;
  temp=inicio;
  while(temp!=NULL){
    inicio=inicio->sig;
    free(temp);
    temp=inicio;
  }
}
