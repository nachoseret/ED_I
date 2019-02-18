#include <stdio.h>
#include <stdlib.h>

typedef void (*FuncionVisitante) (int dato);

typedef struct _SNodo {
  int dato;
  struct _SNodo *sig;
} SNodo;

typedef SNodo *SList;

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

  nodo->sig = nuevoNodo;
  return lista;
}

SList slist_agregar_inicio(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

void slist_recorrer(SList lista, FuncionVisitante visit) {
  for (SList nodo = lista; nodo != NULL; nodo = nodo->sig)
    visit(nodo->dato);
}

static void imprimir_entero(int dato) {
  printf("%d ", dato);
}

int slist_longitud(SList lista){
  if(lista == NULL) return 0;
  int i = 0;
  for(SList nodo = lista; nodo != NULL; nodo = nodo->sig, i++);
  return i;
}

SList slist_insertar(SList lista, int pos, int dato){
  if(lista == NULL) return lista;
  int i = 1;
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  if(pos == 1){
    nuevoNodo->sig = lista;
    return nuevoNodo;
  }
  SList nodo = lista;
  for(; i != pos-1 && nodo->sig != NULL; nodo = nodo->sig, i++);
  nuevoNodo->sig = nodo->sig;
  nodo->sig = nuevoNodo;
  return lista;
}

SList slist_eliminar(SList lista, int pos){
  if (lista == NULL || pos <= 0) return lista;
  SList nodo = lista;
  if(pos == 1) return lista->sig;
  lista->sig = slist_eliminar(lista->sig, pos-1);
  return lista;
}

int main(int argc, char *argv[]) {

  SList lista = slist_crear();

  lista = slist_agregar_inicio(lista, 3);
  lista = slist_agregar_inicio(lista, 2);
  lista = slist_agregar_inicio(lista, 1);
  lista = slist_agregar_final(lista, 4);

  slist_recorrer(lista, imprimir_entero);
  printf("\nlongitud = %d\n",slist_longitud(lista));
  printf("inserto 10 en pos 7\n");
  lista = slist_insertar(lista,7,10);
  slist_recorrer(lista, imprimir_entero);
  printf("elimino la pos 3\n");
  lista = slist_eliminar(lista,5);
  slist_recorrer(lista, imprimir_entero);


  slist_destruir(lista);

  return 0;
}
