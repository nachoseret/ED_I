#include "tablahash.h"
#include "slist.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Crea una nueva tabla Hash vacía, con la capacidad dada.
 */
TablaHash* tablahash_crear(unsigned capacidad, FuncionHash hash) {
  // Pedimos memoria para la estructura principal y las casillas.
  TablaHash* tabla = malloc(sizeof(TablaHash));
  tabla->hash = hash;
  tabla->capacidad = capacidad;
  tabla->tabla = malloc(sizeof(CasillaHash) * capacidad);
  tabla->numElems = 0;

  // Inicializamos las casillas con datos nulos.
  for (unsigned idx = 0; idx < capacidad; ++idx) {
    tabla->tabla[idx].lista = NULL;
  }

  return tabla;
}

/**
 * Inserta el dato en la tabla, asociado a la clave dada.
 */
void tablahash_insertar(TablaHash* tabla, void* clave, void* dato) {
  // Calculamos la posición de la clave dada, de acuerdo a la función hash.
  unsigned idx = tabla->hash(clave);
  idx = idx % tabla->capacidad;

  tabla->numElems++;

  // Almacenamos los datos ingresados.
  tabla->tabla[idx].lista = slist_agregar_inicio(tabla->tabla[idx].lista, *(int*)dato, clave);
}

/**
 * Busca un elemento dado en la tabla, y retorna un puntero al mismo.
 // Calculamos la posición de la clave dada, de acuerdo a la función hash.
 * En caso de no existir, se retorna un puntero nulo.
 */
int* tablahash_buscar(TablaHash* tabla, void* clave) {
  unsigned idx = tabla->hash(clave);
  idx = idx % tabla->capacidad;
  SList a = slist_buscar(tabla->tabla[idx].lista, clave);

  if(a) return &(a->dato);
  return NULL;
}


void tablahash_print(TablaHash* tabla, void* clave) {
  unsigned idx = tabla->hash(clave);
  idx = idx % tabla->capacidad;

  SList a = slist_buscar(tabla->tabla[idx].lista, clave);
  if(a) printf("%d", a->dato);
  else printf("No esta\n");
  return;
}


void tablahash_redimensionar(TablaHash* tabla){
  SList pila = slist_crear(), temp;
  printf("%p",tabla->tabla[i].lista);
  for(int i = 0; i < tabla->capacidad; i++){
    while(tabla->tabla[i].lista){
      //printf("%p\n", tabla->tabla[i].lista);
      temp = slist_pop(tabla->tabla[i].lista);
      pila = slist_agregar_inicio(pila, temp->dato, temp->clave);
      free(temp);
    }
  }
  tabla->capacidad *=2;
  tabla->tabla = realloc(tabla->tabla, sizeof(CasillaHash) * tabla->capacidad);
  while(pila){
    temp = slist_pop(pila);
    tablahash_insertar(tabla,&(temp->clave),&(temp->dato));
    free(temp);
  }
}



/**
 * Elimina un elemento de la tabla.

void tablahash_eliminar(TablaHash* tabla, void* clave) {
  // Calculamos la posición de la clave dada, de acuerdo a la función hash.
  unsigned idx = tabla->hash(clave);
  idx = idx % tabla->capacidad;

  // Si el lugar estaba ocupado, decrementamos el número de elementos.
  if (tabla->tabla[idx].clave != NULL)
    tabla->numElems--;

  // Vaciamos la casilla.
  tabla->tabla[idx].clave = NULL;
  tabla->tabla[idx].dato = NULL;
}

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash* tabla) {
  free(tabla->tabla);
  free(tabla);
}
