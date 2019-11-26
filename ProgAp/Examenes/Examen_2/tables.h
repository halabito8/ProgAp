/************************************************************************
 *									*
 * Archivo:	tables.h						*
 * Descripcion: Tablas para la maquina de estados y funciones externas	*
 *		Aqui se definen todos las tablas que se utilizan	*
 *		en el programa						*
 *									*
 ************************************************************************/

/*************** ARCHIVOS DE INCLUSION ***************/
#include "local.h"
#include <stdio.h>


/*************** FUNCIONES EXTERNAS *********************
 * En esta seccion se declaran los encabezados de 	*
 * todas las funciones que se utilizan en las     	*
 * tablas del programa. Todas las funciones deben 	*
 * ser de tipo entero y no deben recibir parametros	*
 ********************************************************/
extern int funcion1(void);
extern int funcion2(void);
extern int funcion3(void);
extern int funcion4(void);
extern int nul(void);

/******************** TABLAS ********************
 * En esta seccion se declaran las tablas	*
 * que se van a usar en el programa		*
 ************************************************/

/*************** TABLA DE ACCION ***************/
ACTION_TAB action_table[]={
        /*etype     accion     bandera   sigEdo. */
    { ENTRADA_A,  msj_edo_a,  	-1,	    1},
    { ENTRADA_B,  msj_edo_b,	    -1,	    2},
    { ASTERISCO,  nul,	         0,	    0},
    { ENTRADA_C,  lleno,	    -1,	    -1},
    { ASTERISCO,  nul,	         0,	    0},
    { ENTRADA_D,  msj_conf_bajo,	    -1,	    3},
    { ENTRADA_E,  Error_P,	    -1,	    4},
    { ASTERISCO,  nul,	         0,	    0},
    { ENTRADA_F,  Error_P,	    -1,	    -1},
    { ASTERISCO1,  nul,	         0,	    3},
    { ENTRADA_G,  Error_P,	    -1,	    -1},
    { ASTERISCO,  nul,	         0,	    0},
};

/*************** TABLA AUXILIAR ***************/
    AUX_TAB aux_table[]={
/*    accion       bandera           sigEdo */
    { funcion1,        -1,          ESTADO_0},
    { funcion2,	       -1,          ESTADO_0},
};

/*************** TABLA DE ESTADOS ***************/
STATE_TAB state_table[]={
   /*estado      inicio   fin */
    {ESPERA,     0,      2},
    {ESTADO_A,     3,      4},
    {ESTADO_B,     5,      7},
    {ESTADO_D,     8,      9},
    {ESTADO_E,     10,      11},
};
