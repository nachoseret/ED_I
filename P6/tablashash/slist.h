#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>


typedef struct _SNodo {
  int dato;
  void* clave;
  struct _SNodo *sig;
} SNodo;

typedef SNodo *SList;
typedef void (*FuncionVisitante) (SList data);

/**
 * Devuelve una lista vacía.
 */
SList slist_crear();

SList slist_pop(SList lista);

/**
 * Destruccion de la lista.
 */
void slist_destruir(SList lista);

/**
 * Determina si la lista es vacía.
 */
int slist_vacia(SList lista);

/**
 * Agrega un elemento al final de la lista.
 */
SList slist_agregar_final(SList lista, int dato);

/**
 * Agrega un elemento al inicio de la lista.
 */
SList slist_agregar_inicio(SList lista, int dato, void* clave);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void slist_recorrer(SList lista, FuncionVisitante visit);

SList slist_buscar(SList lista, void* clave);

/*
** Retorna la longitud de una lista.
*/
int slist_longitud(SList lista);

int slist_longitud2(SList lista);

/*SLIST
** Retorna la concatenacion de dos listas.
*/
SList slist_concatenar(SList lista1, SList lista2);


/*
** Inserta un dato en una lista en una posicion arbitraria.
*/
SList slist_insertar(SList lista, int dato, int pos);


/*
** Busca un dato.
*/
int slist_contiene(SList lista, int dato);

#endif /* __SLIST_H__ */
