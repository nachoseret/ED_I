#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*FuncionVisitante) (int dato);

typedef struct _SNodo {
  struct _SNodo *sig;
  char dato[];
} SNodo;

typedef SNodo * SList;

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

SList slist_agregar_inicio(SList lista, char dato[]) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  strcpy(nuevoNodo->dato,dato);
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

int slist_longitud(SList lista){
  if(lista == NULL) return 0;
  int i = 0;
  for(SList nodo = lista; nodo != NULL; nodo = nodo->sig, i++);
  return i;
}

SList slist_eliminar(SList lista, int pos){
  if (lista == NULL || pos <= 0) return lista;
  SList nodo = lista;
  if(pos == 1) return lista->sig;
  lista->sig = slist_eliminar(lista->sig, pos-1);
  return lista;
}

typedef struct _tablahash{
  SList * tabla;
  int capacidad;
} _tablahash;

typedef _tablahash * tablahash;

typedef int (*FuncionHash) (char dato[]);

tablahash tabla_crear(int capacidad){
  tablahash a = malloc(sizeof(_tablahash));
  a->capacidad = capacidad;
  a->tabla = malloc(sizeof(SList)*capacidad);
  for(int i = 0; i<capacidad; i++){
    a->tabla[i] = slist_crear();
  }
  return a;
}

void insertar(tablahash a, FuncionHash hash, char dato[]){
  int h = hash(dato)%a->capacidad;
  a->tabla[h] = slist_agregar_inicio(a->tabla[h], dato);
}

void dump(tablahash a){
  for(int i=0; i<a->capacidad; i++){
    printf("a[%d] - ",i);
    for(SList nodo = a->tabla[i]; nodo!=NULL; nodo=nodo->sig){
      printf("%s ",nodo->dato);
    }
    printf("\n");
  }
}

int f(char dato[]){
  return (int)dato[0];
}

int main()
{
  char a1[] = "Mattie";
  char a2[] = "Alisia";
  char a3[] = "Lizette";
  char a4[] = "Lynna";
  char a5[] = "Alejandrina";
  char a6[] = "Fidela";
  char a7[] = "Emmett";
  char a8[] = "Shela";
  char a9[] = "Zulema";
  char b1[] = "Gilma";
  char b2[] = "Arnold";
  char b3[] = "Aretha";
  char b4[] = "Malisa";
  char b5[] = "June";
  char b6[] = "Deedee";
  char b7[] = "Heather";
  char b8[] = "Stasia";
  char b9[] = "Kim";
  char c1[] = "Shirleen";
  char c2[] = "Earl";
  char c3[] = "Martin";
  char c4[] = "Zackary";
  char c5[] = "Tracey";
  char c6[] = "Katerine";
  char c7[] = "Isreal";
  char c8[] = "Julian";
  char c9[] = "Elna";
  char d1[] = "Rosanne";
  char d2[] = "Nestor";
  char d3[] = "Tameka";
  tablahash x = tabla_crear(24);
  insertar(x,f,a1);
  insertar(x,f,a2);
  insertar(x,f,a3);
  insertar(x,f,a4);
  insertar(x,f,a5);
  insertar(x,f,a6);
  insertar(x,f,a7);
  insertar(x,f,a8);
  insertar(x,f,a9);
  insertar(x,f,b1);
  insertar(x,f,b2);
  insertar(x,f,b3);
  insertar(x,f,b4);
  insertar(x,f,b5);
  insertar(x,f,b6);
  insertar(x,f,b7);
  insertar(x,f,b8);
  insertar(x,f,b9);
  insertar(x,f,c1);
  insertar(x,f,c2);
  insertar(x,f,c3);
  insertar(x,f,c4);
  insertar(x,f,c5);
  insertar(x,f,c6);
  insertar(x,f,c7);
  insertar(x,f,c8);
  insertar(x,f,c9);
  insertar(x,f,d1);
  insertar(x,f,d2);
  insertar(x,f,d3);
  dump(x);
  return 0;
}


















