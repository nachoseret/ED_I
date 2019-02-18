#ifndef __TABLAHASH_H__
#define __TABLAHASH_H__

#include "slist.h"

/**
 * Tipo de las funciones hash a ser consideradas por las tablas hash.
 */
typedef unsigned (*FuncionHash)(void* clave);

/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef struct {
  SList lista;
} CasillaHash;

/**
 * Estructura principal que representa la tabla hash.
 */
typedef struct {
  CasillaHash* tabla;
  unsigned numElems;
  unsigned capacidad;
  FuncionHash hash;
} TablaHash;

/**
 * Crea una nueva tabla Hash vacía, con la capacidad dada.
 */
TablaHash* tablahash_crear(unsigned capacidad, FuncionHash fun);

/**
 * Inserta el dato en la tabla, asociado a la clave dada.
 */
void tablahash_insertar(TablaHash* tabla, void* clave, void* dato);

void tablahash_redimensionar(TablaHash* tabla);

/**
 * Busca un elemento dado en la tabla, y retorna un puntero al mismo.
 * En caso de no existir, se retorna un puntero nulo.
 */
int* tablahash_buscar(TablaHash* tabla, void* clave);
void tablahash_print(TablaHash* tabla, void* clave);

/**
 * Elimina un elemento de la tabla.
 */
void tablahash_eliminar(TablaHash* tabla, void* clave);

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash* tabla);

#endif /* __TABLAHASH_H__ */
