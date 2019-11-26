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
extern int NumeroCuenta(void);
extern int MsgBorrar(void);
extern int ExisteNIP(void);
extern int MsgInserta(void);
extern int MsgRetira(void);
extern int MsgContra(void);
extern void BitacoraMov(float cantidad,int acc);
extern int ConsultarSaldo(void);
extern int Exit(void);
extern int Inserta1000(void);
extern int Inserta2000(void);
extern int Inserta3000(void);
extern int Inserta4000(void);
extern int EscogeCuanto(void);
extern int Alcanza(void);
extern int Contra(void);
extern int Cancelar(void);
extern int MsgNoValido(void);
extern int NipIncorrecto(void);
extern int MsgNoAlcanza(void);
extern int RetiraDinero(void);
extern int ExisteNIP(void);
extern int nul(void);
extern int nul1(void);
extern int Bitacora(void);

/******************** TABLAS ********************
 * En esta seccion se declaran las tablas	*
 * que se van a usar en el programa		*
 ************************************************/

/*************** TABLA DE ACCION ***************/
ACTION_TAB action_table[]={
        /*etype     accion     bandera   sigEdo. */
    { T,           NumeroCuenta,    0,     -1},
    { S,           MsgBorrar,	   -1,	   -1},
    { A1,          nul, 	    0,	    0},
    { N,           ExisteNIP,	    0,	   -1},
    { C,           nul, 	   -1,	    0},
    { I,           MsgInserta,	   -1,	    3},
    { R,           MsgRetira,	   -1,	    4},
    { P,           MsgContra,      -1,	    5},
    { M,           Bitacora,	   -1,	    2},
    { c,           ConsultarSaldo, -1,	    2},
    { E,           Exit,	   -1,	    0},
    { A2,          nul,        	   -1,	    2},
    { w,           Inserta1000,    -1,	    2},
    { x,           Inserta2000,	   -1,	    2},
    { y,           Inserta3000,	   -1,	    2},
    { z,           Inserta4000,	   -1,	    2},
    { o,           EscogeCuanto,   -1,      2},
    { A3,          nul, 	   -1,	    3},
    { W,           Alcanza, 	    0,	   -1},
    { X,           Alcanza,	    0,     -1},
    { Y,           Alcanza, 	    0,	   -1},
    { Z,           Alcanza,	    0,	   -1},
    { O,           Alcanza,	    0,	   -1},
    { A4,          nul,        	   -1,	    4},
    { n,           Contra,     -1,	    2},
    { B,           Cancelar,	   -1,	    2},
    { A5,          nul,	           -1,	    5},


};

/*************** TABLA AUXILIAR ***************/
    AUX_TAB aux_table[]={
/*    accion       bandera           sigEdo */
    { MsgNoValido,     -1,              0},
    { nul,	       -1,              1},
    { NipIncorrecto,   -1,              0},
    { nul,	       -1,              2},
    { MsgNoAlcanza,    -1,              2},
    { RetiraDinero,    -1,              2},
};

/*************** TABLA DE ESTADOS ***************/
STATE_TAB state_table[]={
   /*estado      inicio   fin */
    {Espera,      0,      2},
    {NIP,         3,      4},
    {Movimientos, 5,      11},
    {Ingresar,    12,     17},
    {Retirar,     18,     23},
    {Contrasena,  24,     26},
};
