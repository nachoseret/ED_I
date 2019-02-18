#include "slist.h"
#include <stdlib.h>

SList slist_crear() {
  return NULL;
}

void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar);
  }
}

int slist_vacia(SList lista) {
  return lista == NULL;
}

SList slist_agregar_final(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  if (lista == NULL)
    return nuevoNodo;

  SList nodo = lista;
  for (;nodo->sig != NULL;nodo = nodo->sig);
  /* ahora 'nodo' apunta al ultimo elemento en la lista */

  nodo->sig = nuevoNodo;
  return lista;
}

SList slist_agregar_inicio(SList lista, int dato, void* clave) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->clave = clave;
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

SList slist_pop(SList lista) {
  if(!lista) return NULL;
  SList temp = lista;
  lista = lista->sig;
  temp->sig = NULL;
  return temp;
}


void slist_recorrer(SList lista, FuncionVisitante visit) {
  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig)
    visit(nodo);
}

int slist_longitud(SList lista){
  int total;
  if (lista==NULL) return 0;
  if (lista->sig==NULL) return 1;
  else{
    total = 1 + slist_longitud(lista->sig);
    return total;
  }
}

int slist_longitud2(SList lista){
  int i;
  for(i = 0; lista != NULL; lista = lista->sig, i++);
  return i;
}

 SList slist_concatenar (SList lista1, SList lista2){
   SNodo* temp;
   if (slist_vacia (lista1)) return lista2;
   if (slist_vacia (lista2)) return lista1;
   for(temp = lista1; temp->sig != NULL; temp = temp->sig);
   temp->sig = lista2;
   return lista1;

 }
/*
 SList slist_insertar(SList lista, int dato, int pos){
   SNodo* nuevoNodo;
   SNodo* temp = lista;
   int i;
   if((pos<0) || (slist_longitud2(lista) < pos)) return lista;
   if (pos == 0){
     lista = slist_agregar_inicio(lista,dato);
     return lista;
   }
   if (slist_longitud2(lista) == pos){
     lista = slist_agregar_final(lista,dato);
     return lista;
   }
   for(i = 0;i < pos-1; temp = temp->sig, i++);
   nuevoNodo = (SNodo*)malloc(sizeof(SNodo));
   nuevoNodo->dato = dato;
   nuevoNodo->sig = temp->sig;
   temp->sig = nuevoNodo;
   return lista;
 }

 int slist_contiene(SList lista, int dato) {
   for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig){
     if (nodo->dato == dato) return 1;
   }
   return 0;
 }
*/
SList slist_buscar(SList lista, void* clave){
  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig){
    if (*(int*)nodo->clave == *(int*)clave) return nodo;
  }
  return NULL;
}
