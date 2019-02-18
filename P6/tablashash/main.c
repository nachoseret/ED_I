#include <stdio.h>
#include <stdlib.h>
#include "tablahash.h"
#include "slist.h"

unsigned hash(void* clave) {
  int* p = clave;
  return *p;
}

static void imprimir_entero(SList data) {
  printf("(%d,%d)\t", *(int*)data->clave, data->dato);
}

int main(void) {
  int claves[10] = {42,12,13,0,4,3,14,8,5,10};
  int elems[10]  = {0 ,1 ,2 ,3,4,5,6 ,7,8,9 };
  int* temp;
  TablaHash *th = tablahash_crear(10, hash);

  for(int i = 0; i<10; i++){
    tablahash_insertar(th, claves+i, elems+i);
  }

  tablahash_redimensionar(th);

  for(int i=0;i<20;i++){
    printf("%d : ", i);
    slist_recorrer(th->tabla[i].lista, imprimir_entero);
    printf("\n");
  }
  //tablahash_eliminar(th, &x);

  tablahash_destruir(th);

  return 0;
}
