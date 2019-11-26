/************************************************************************
 *									*
 * Archivo:	tables.h						*
 * Descripcion: Tablas para la maquina de estados y funciones externas	*
 *		Aqui se definen todos las tablas que se utilizan	*
 *		en el programa						*
 *									*
 ************************************************************************/

/*************** ARCHIVOS DE INCLUSION ***************/
#include "local2.h"
#include <stdio.h>


/*************** FUNCIONES EXTERNAS *********************
 * En esta seccion se declaran los encabezados de 	*
 * todas las funciones que se utilizan en las     	*
 * tablas del programa. Todas las funciones deben 	*
 * ser de tipo entero y no deben recibir parametros	*
 ********************************************************/
extern int Existe(void);
extern int jaumuch(void);
extern int alcanza(void);
extern int salida(void);
extern int regresa(void);
extern int msj_no(void);
extern int msj_precio(void);
extern int msj_no_alc(void);
extern int entrega_prod(void);
extern int msj_1(void);
extern int msj_2(void);
extern int Existe2(void);
extern int msj_no_ex(void);
extern int nul(void);

/******************** TABLAS ********************
 * En esta seccion se declaran las tablas	*
 * que se van a usar en el programa		*
 ************************************************/

/*************** TABLA DE ACCION ***************/
ACTION_TAB action_table[]={
        /*etype     accion     bandera   sigEdo. */
    { ENTRADA_c ,   Existe,  	    0,	   -1},
    { ENTRADA_d,      jaumuch,	  -1,  	  1},
    { ENTRADA_s,      salida,	    -1,	   -1},
    { ASTERISCO,     msj_1,	        -1,	  0},
    { ENTRADA_t,    Existe2,	     0,	   -1},
    { ENTRADA_r,     regresa,	    -1,	    0},
    { ASTERISCO1,    msj_2,         -1,    1},
};

/*************** TABLA AUXILIAR ***************/
    AUX_TAB aux_table[]={
/*    accion       bandera           sigEdo */
    { msj_no,        -1,        0},
    { msj_precio,   -1,         0},
    { msj_no_ex,    -1,         0},
    { alcanza,       0,        -1},
    { msj_no_alc,    -1,        1},
    { entrega_prod,   -1,       0},
};

/*************** TABLA DE ESTADOS ***************/
STATE_TAB state_table[]={
   /*estado      inicio   fin */
    {Espera,       0,      3},
    {Vender,     4,      6},
};
