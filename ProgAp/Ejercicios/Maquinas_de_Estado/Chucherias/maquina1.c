/****************************************************************
 *                *
 * Archivo:  state_mach1.c          *
 * Descripcion: Codigo Fuente para implementar el programa  *
 *    de maquina de estados.         *
 *                *
 ****************************************************************/

/*************** ARCHIVOS DE INCLUSION ***************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tables2.h"


/*************** VARIABLES GLOBALES ***************/
EVENT event;
int state;
int dinero;
char buf[BUFFER];
int lista[10][2]={
	{1,10},
	{2,20},
	{3,30},
	{4,40},
	{5,50},
	{6,60},
	{7,70},
	{8,80},
	{9,90},
	{10,100},
};
int a;

/*************** PROTOTIPOS DE FUNCION ***************/
void initialise(void);
void getevent(void);

int Existe(void);
int jaumuch(void);
int alcanza(void);
int regresa(void);
int salida(void);
int msj_no(void);
int msj_precio(void);
int msj_no_alc(void);
int entrega_prod(void);
int msj_1(void);
int msj_2(void);
int Existe2(void);
int nul(void);


/*************** FUNCION PRINCIPAL ***************/
int main(int argc, char **argv){
	int actx, auxx, outcome;

	initialise();

	while(1){    /* loop infinito para la MFE */
		getevent();

		for ((actx = state_table[state].start);(action_table[actx].event != event.etype) && (actx < state_table[state].end);actx++);
		outcome = (*(action_table[actx].action))();
		if(action_table[actx].moreacts == -1)
			state = action_table[actx].nextstate;
		else{
			auxx = action_table[actx].moreacts + outcome;
			while (auxx != -1){
				outcome = (*(aux_table[auxx].action))();
				if (aux_table[auxx].moreacts == -1 ){
						state = aux_table[auxx].nextstate;
						auxx = -1;
				}
				else
					auxx = aux_table[auxx].moreacts + outcome;

			}
		}
	} /* while(1) */
}

void initialise(void){
	int i,j;
		state = 0;
		printf("Maquina prendida\n");
		for(i=0;i<10;i++)
			printf("Papas %i codigo %i precio %i\n",i+1,lista[i][0],lista[i][1]);
	printf("(C)onsultar (D)Comprar producto (S)alir\n");
}


void getevent(void){
	char *ptmp;
	ptmp = &buf[2];

	#ifdef DEBUG
		printf("wait event \n");
	#endif
		__fpurge(stdin);
		gets(buf);
 	switch (buf[0]){
	  case 'C':
			 event.etype=ENTRADA_c;
		break;
	  case 'D':
			 event.etype=ENTRADA_d;
		break;
	  case 'S':
        event.etype=ENTRADA_s;
    break;
    case 'T':
        event.etype=ENTRADA_t;
    break;
		case 'R':
			event.etype=ENTRADA_r;
		break;
		#ifdef DEBUG
			printf("---> %s \n",event.args);
		#endif
		break;
		default:
			event.etype=-1;
		break;
	}//switch
}// getevent


/* FUNCIONES DE IMPLEMENTACION */

int Existe(void){
	printf("Que producto quieres consultar?\n");
	__fpurge(stdin);
	scanf("%i",&a);
	if(a<0||a>9)
		return 0;
	else
		return 1;
}

int msj_no(void){
  printf("No existe el producto\n");
	printf("(C)onsultar (D)Comprar producto (S)alir\n");
}

int msj_precio(void){
	a--;
  printf("El precio del producto %i es %i\n",lista[a][0],lista[a][1]);
	printf("(C)onsultar (D)Comprar producto (S)alir\n");
}

int jaumuch(void){
  printf("Cuanto dinero vas a ingresar?\n");
	__fpurge(stdin);
	scanf("%i",&dinero);
	printf("(T)seleccionar producto (R)egresar dinero\n");
}

int alcanza(void){
	a--;
	if(dinero<lista[a][1])
		return 4;
	else
		return 5;
}

int salida(void){
	printf("Gracias por tu preferencia\n");
	exit(0);
}

int regresa(void){
	dinero=0;
	printf("Recoje tu dinero\n");
	printf("(C)onsultar (D)Comprar producto (S)alir\n");
}

int msj_no_alc(void){
	printf("No alcanza\n");
	printf("(T)seleccionar producto (R)egresar dinero\n");
}

int entrega_prod(void){
	printf("Recoje tu producto\n");
	dinero=dinero-lista[a][1];
	if(dinero!=0)
		printf("Tu cambio es de %i\n",dinero);
	dinero=0;
	printf("(C)onsultar (D)Comprar producto (S)alir\n");
}

int msj_1(void){
	printf("(C)onsultar (D)Comprar producto (S)alir\n");
}

int msj_2(void){
	printf("(T)seleccionar producto (R)egresar dinero\n");
}

int Existe2(void){
	printf("Que producto quieres?\n");
	__fpurge(stdin);
	scanf("%i",&a);
	if(a<0||a>9)
		return 2;
	else
		return 3;
}

int msj_no_ex(void){
	printf("No existe el producto\n");
	printf("(T)seleccionar producto (R)egresar dinero\n");
}

int nul(void){
  printf("Hola soy nul\n");
}
