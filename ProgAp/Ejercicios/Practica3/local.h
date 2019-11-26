/****************************************************************
 *								*
 * Archivo:	local.h						*
 * Descripcion: Archivo de encabezado para maquina de estados	*
 *		Aqui se definen todos los tipos de datos y 	*
 *		constantes que se utilizan en el programa	*
 *								*
 ****************************************************************/

/******************* CONSTANTES *******************
 * En esta seccion se declaran todas las 	  *
 * las constantes que se necesiten en el programa *
 **************************************************/
#define BUFFER        128
#define L_EVENT_ARGS  21


/****************** ESTRUCTURAS *****************
 * En esta seccion se declaran todas las	*
 * estructuras que se necesiten en el programa	*
 ************************************************/

// Este tipo de datos se utiliza para leer la informacion
// que teclea el usuario
struct event_s
{
    int etype;
    char args[L_EVENT_ARGS];
};
typedef struct event_s EVENT;

// Este tipo de datos se utiliza para implementar
// la tabla auxiliar
struct aux_table_s
{
    int (*action)();
    int moreacts;
    int nextstate;
};
typedef struct aux_table_s AUX_TAB;

// Este tipo de datos se utiliza para implementar
// la tabla de accion
struct action_tab_s
{
    int event;
    int (*action)();
    int moreacts;
    int nextstate;
};
typedef struct action_tab_s ACTION_TAB;

// Este tipo de datos se utiliza para implementar
// la tabla de estados
struct state_tab_s
{
    int state;
    int start;
    int end;
};
typedef struct state_tab_s STATE_TAB;



/********************* GLOBALES ***********************
 * En esta seccion se pueden declarar todas	      *
 * variables globales que se necesiten en el programa *
 ******************************************************/
typedef struct usuario{
char nombre[200], nip[6];
long unsigned tarjeta;
double dinero;
struct usuario *sig;
} tipousuario;

float retira;
tipousuario *usuario,*principio;

FILE *fp;



/********************* EVENTOS *******************
 * En esta seccion se declarar como constantes	 *
 * los eventos (entradas) que recibe el programa *
 *************************************************/
#define T   0
#define S   1
#define A1  -1
#define N   3
#define C   4
#define I   5
#define R   6
#define P   7
#define M   8
#define c   9
#define E   10
#define A2  -1
#define w   12
#define x   13
#define y   14
#define z   15
#define o   16
#define A3  -1
#define W   18
#define X   19
#define Y   20
#define Z   21
#define O   22
#define A4  -1
#define n   24
#define B   25
#define A5  26


/********************* ESTADOS ******************
 * En esta seccion se declarar como constantes	*
 * los estados de que consta el programa 	*
 ************************************************/
#define Espera      0
#define NIP         1
#define Movimientos 2
#define Ingresar    3
#define Retirar     4
#define Contrasena  5
