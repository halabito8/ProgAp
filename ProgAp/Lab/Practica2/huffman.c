#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct codigo
{
  char simbolo,binario[10];
  float probabilidad;
  int suma;
  struct codigo *sig;
  struct codigo *izq,*der;
}tipocodigo;

void agregar(tipocodigo **inicio);
void eliminar(tipocodigo **inicio);
void imprimir(tipocodigo *inicio);
void borrar(tipocodigo *inicio);
void leer(tipocodigo **inicio);
void guardar(tipocodigo *inicio);
void modificar(tipocodigo *inicio);
void arbol(tipocodigo *inicio,tipocodigo **raiz);
void ordena(tipocodigo **inicio,tipocodigo *nuevo);
void asignar(tipocodigo *raiz,char gaby[10],int pos,int *max);
void impcod(tipocodigo *raiz);
void codificar(tipocodigo *inicio);
void decodificar(tipocodigo *inicio,int max);

int main(void)
{
  int i=0,op,max=0;
  char gaby[10], j;
  gaby[0]='\0';
  tipocodigo *inicio=NULL,*raiz=NULL;
  system("clear");
  printf("Desarrolladores:\n");
  printf("1.Maria Gabriela Uribe\n2.David Halabe Husny\n3.Emanuel Zuriel Bajonero\n\n");
  printf("Presione enter para continuar\n");
  j=getchar();
  system("clear");
  do{
    printf("\n");
  printf("Seleccione la opción deseada:\n1. Agregar simbolo\n2. Eliminar simbolo\n3. Ver la lista de los codigos\n4. Leer diccionario\n5. Guardar diccionario\n6. Modificar probabilidad de un simbolo\n7. Crear codigos\n8. Codificar archivo \n9. Decodificar archivo\n10. Salir\nOpcion: ");
  __fpurge(stdin);
  scanf("%i",&op);
  switch(op)
    {
    case 1:
      system("clear");
      agregar(&inicio);
      system("clear");
    break;
    case 2:
      system("clear");
      eliminar(&inicio);
      system("clear");
    break;
    case 3:
      system("clear");
      imprimir(inicio);
    break;
    case 10:
      system("clear");
      printf("Saliendo del programa...\n");
      i=1;
    break;
    default:
      system("clear");
      printf("Opción inválida. Seleccionar una opcion valida\n");
    break;
    case 4:
      system("clear");
      leer(&inicio);
      system("clear");
    break;
    case 5:
      system("clear");
      guardar(inicio);
      system("clear");
    break;
    case 6:
      system("clear");
      modificar(inicio);
      system("clear");
    break;
    case 7:
      system("clear");
      arbol(inicio,&raiz);
      asignar(raiz,gaby,i,&max);
      system("clear");
      impcod(raiz);
    break;
    case 8:
      system("clear");
      codificar(inicio);
    break;
    case 9:
      system("clear");
      decodificar(inicio,max);
    break;
  }
  }while(i==0);
  borrar(inicio);
}

void codificar(tipocodigo *inicio)
{
  char arch[200],nuevo[200],a;
  FILE *algo,*bajo;
  tipocodigo *flex;
  printf("¿Qué archivo desea codificar?\n");
  __fpurge(stdin);
  gets(arch);
  algo=fopen(arch,"rt");
  if(algo!=NULL)
    {
    printf("¿En que archivo desea guardar el mensaje codificado?\n");
    __fpurge(stdin);
    gets(nuevo);
    bajo=fopen(nuevo,"wt");
    while(fscanf(algo,"%c",&a)==1)
      {
      if(a!=10 && a!=' ')
	{
        flex=inicio;
        while(flex!=NULL&&flex->simbolo!=a)
          flex=flex->sig;
        if(flex==NULL){
          printf("Error, la letra '%c' no esta en el diccionario\n", a);
          fclose(algo);
          fclose(bajo);
          return;
        }
        fprintf(bajo,"%s",flex->binario);
      }
      else
        fprintf(bajo,"%c",a);
    }
    fclose(algo);
    fclose(bajo);
    }
  else
    printf("El archivo no existe\n");
}

void decodificar(tipocodigo *inicio,int max)
{
  int pos=0;
  char leer[200],escribir[200],codigo[max+1],a;
  FILE *david,*cosa;
  tipocodigo *flex;
  printf("¿Qué archivo quieres decodificar?\n");
  __fpurge(stdin);
  gets(leer);
  david=fopen(leer,"rt");
  if(david!=NULL)
    {
      printf("¿Qué archivo quieres escribir?\n");
      __fpurge(stdin);
      gets(escribir);
      cosa=fopen(escribir,"wt");
      while(pos<=max&&fscanf(david,"%c",&a)==1)
	{
	  if(a!=10&& a!=' ')
	    {
	      codigo[pos]=a;
	      codigo[pos+1]='\0';
	      flex=inicio;
	      while(flex!=NULL&&strcmp(flex->binario,codigo)!=0)
		flex=flex->sig;
	      if(flex==NULL)
		pos++;
	      else
		{
		  fprintf(cosa,"%c",flex->simbolo);
		  pos=0;
		  codigo[0]='\0';
		}
	    }
	  else
	    {
	      fprintf(cosa,"%c",a);
	      pos=0;
	      codigo[0]='\0';
	    }
	  if(pos>max)
	    {
	      printf("El codigo '%s' no esta en el diccionario\n",codigo);
	    }
	}
    }
  else
    printf("Error, el archivo no existe\n");
  if(david!=NULL)
    {
      fclose(david);
      fclose(cosa);
    }
}

void impcod(tipocodigo *raiz)
{
  if(raiz!=NULL)
    {
      impcod(raiz->izq);
      if(raiz->suma==0)
	printf("Simbolo %c codigo %s\n", raiz->simbolo,raiz->binario);
      impcod(raiz->der);
    }
}

void asignar(tipocodigo *raiz,char gaby[10],int pos,int *max){
  if(raiz!=NULL){
    if(raiz->izq!=NULL){
      gaby[pos]='0';
      gaby[pos+1]='\0';
      asignar(raiz->izq,gaby,pos+1,max);
    }
    if(raiz->der!=NULL){
      gaby[pos]='1';
      gaby[pos+1]='\0';
      asignar(raiz->der,gaby,pos+1,max);
    }
    if(raiz->suma==0){
      strcpy(raiz->binario,gaby);
      if(pos>*max)
        *max=pos;
    }
  }
}

void arbol(tipocodigo *inicio,tipocodigo **raiz)
{
  float porcentaje=0;
  tipocodigo *flex,*nuevo,*flex2;
  flex=inicio;
  while(flex!=NULL)
    {
    porcentaje=porcentaje+flex->probabilidad;
    flex=flex->sig;
  }
  if(porcentaje==100)
    {
    while(inicio!=NULL)
      {
      flex=inicio;
      nuevo=(tipocodigo*)malloc(sizeof(tipocodigo));
      nuevo->suma=1;
      nuevo->binario[0]='2';
      nuevo->izq=flex;
      nuevo->der=flex->sig;
      nuevo->probabilidad=flex->probabilidad+flex->sig->probabilidad;
      *raiz=nuevo;
      inicio=flex->sig->sig;
      if(nuevo->probabilidad!=100)
	{
        flex=inicio;
        while(flex!=NULL&&flex->probabilidad<nuevo->probabilidad)
          flex=flex->sig;
        if(flex==NULL)
	  {
          flex=inicio;
          while(flex->sig!=NULL)
            flex=flex->sig;
          flex->sig=nuevo;
        }
        else if(flex==inicio)
	  {
          nuevo->sig=inicio;
          inicio=nuevo;
        }
        else
	  {
          flex2=inicio;
          while(flex2->sig!=flex)
            flex2=flex2->sig;
          nuevo->sig=flex;
          flex2->sig=nuevo;
        }
      }
    }
  }
  else{
    printf("Las probabilidades no suman 100%%, porfavor revisa las probabilidades introducidas.\n");
    imprimir(inicio);
  }
}

void agregar(tipocodigo **inicio)
{
  int val;
  char letra;
  tipocodigo *nuevo,*busca,*temp;
  printf("Cual es el simbolo nuevo?\n");
  __fpurge(stdin);
  scanf("%c",&letra);
  busca=*inicio;
  while(busca!=NULL&&busca->simbolo!=letra)
    busca=busca->sig;
  if(busca==NULL)
    {
    nuevo=(tipocodigo*)malloc(sizeof(tipocodigo));
    nuevo->simbolo=letra;
    printf("Cual es la probabilidad?\n");
    __fpurge(stdin);
    do
      {
      val=scanf("%f",&nuevo->probabilidad);
    }while(val!=1);
    nuevo->sig=NULL;
    nuevo->suma=0;
    ordena(inicio,nuevo);
  }
  else
    printf("Ese simbolo ya existe en la lista.\n");
}

void eliminar(tipocodigo **inicio)
{
  char borra;
  struct codigo *busca,*temp;
  printf("¿Que simbolo desea eliminar?\n");
  __fpurge(stdin);
  scanf("%c",&borra);
  busca=*inicio;
  while(busca!=NULL&&busca->simbolo!=borra)
    busca=busca->sig;
  if(busca==NULL)
    printf("Error, ese simbolo no esta en la lista.\n");
  else if(busca==*inicio)
    {
    *inicio=busca->sig;
    free(busca);
  }
  else
    {
    temp=*inicio;
    while(temp->sig!=busca)
      temp=temp->sig;
    temp->sig=busca->sig;
    free(busca);
    }
}

void imprimir(tipocodigo *inicio){
  tipocodigo *nuevo;
  if(inicio!=NULL)
    {
      nuevo=inicio;
      printf("Las probabilidades son:\n");
      while(nuevo!=NULL)
	{
	  if(nuevo->suma==0)
	    printf("Simbolo '%c' probabilidad %f%%\n", nuevo->simbolo,nuevo->probabilidad);
	  nuevo=nuevo->sig;
	}
    }
  else
    printf("No hay nada para imprimir, lo siento\n");
}

void borrar(tipocodigo *inicio)
{
  tipocodigo *temp;
  temp=inicio;
  while(temp!=NULL)
    {
      inicio=inicio->sig;
      free(temp);
      temp=inicio;
    }
}

void leer(tipocodigo **inicio)
{
  char nombre[200],letra;
  FILE *algo;
  tipocodigo *nuevo;
  printf("¿En que archivo esta su diccionario?\n");
  __fpurge(stdin);
  gets(nombre);
  algo=fopen(nombre,"rt");
  if(algo!=NULL)
    {
      while(fscanf(algo,"%c\n",&letra)==1)
	{
	  nuevo=(tipocodigo*)malloc(sizeof(tipocodigo));
	  nuevo->simbolo=letra;
	  fscanf(algo,"%f\n",&nuevo->probabilidad);
	  nuevo->sig=NULL;
	  nuevo->suma=0;
	  ordena(inicio,nuevo);
	}
    }
  else
    printf("Lo siento, ese archivo no existe\n");
}

void guardar(tipocodigo *inicio)
{
  char nombre[200];
  FILE *algo;
  tipocodigo *nuevo;
  printf("¿En que archivo desea guardar su diccionario?\n");
  __fpurge(stdin);
  gets(nombre);
  algo=fopen(nombre,"wt");
  nuevo=inicio;
  while(nuevo!=NULL)
    {
      if(nuevo->suma==0)
	{
	  fprintf(algo,"%c\n%f\n",nuevo->simbolo,nuevo->probabilidad);
	  nuevo=nuevo->sig;
	}
    }
  fclose(algo);
}

void modificar(tipocodigo *inicio)
{
  char letra;
  tipocodigo *busca;
  printf("¿Que simbolo desea modificar su probabilidad?\n");
  __fpurge(stdin);
  scanf("%c",&letra);
  busca=inicio;
  while(busca!=NULL&&busca->simbolo!=letra)
    busca=busca->sig;
  if(busca!=NULL)
    {
      printf("El simbolo '%c' tiene una probabilidad de %f%%.\n¿Cual quiere que sea la nueva probabilidad?\n",busca->simbolo,busca->probabilidad);
      scanf("%f",&busca->probabilidad);
    }
  else
    printf("Error, ese simbolo no existe en la lista.\n");
}

void ordena(tipocodigo **inicio,tipocodigo *nuevo)
{
  tipocodigo *busca,*temp;
  if(*inicio!=NULL)
    {
      busca=*inicio;
      while(busca!=NULL&&nuevo->probabilidad>busca->probabilidad)
	busca=busca->sig;
      if(busca==NULL)
	{
	  busca=*inicio;
	  while(busca->sig!=NULL)
	    busca=busca->sig;
	  busca->sig=nuevo;
	}
      else if(busca==*inicio)
	{
	  nuevo->sig=busca;
	  *inicio=nuevo;
	}
      else{
	temp=*inicio;
	while(temp->sig!=busca)
	  temp=temp->sig;
	nuevo->sig=busca;
	temp->sig=nuevo;
      }
    }
  else
    *inicio=nuevo;
}
