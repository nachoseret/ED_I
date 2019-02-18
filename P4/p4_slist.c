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
  printf("\n");
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

int * slist_head(SList lista){
  if(lista == NULL) return NULL;
  int * ret = malloc(sizeof(int));
  *ret = lista->dato;
  return ret;
}

// PRACTICA 4 - ORDENAMIENTO

typedef struct _arreglo {
  int * datos;
  int nelems;
  int capacidad;
} _arreglo;

typedef _arreglo * arreglo;

arreglo ar_crear(int capacidad){
  arreglo a = malloc(sizeof(_arreglo));
  a->datos = malloc(sizeof(int)*capacidad);
  a->capacidad = capacidad;
  a->nelems = 0;
  return a;
}

void ar_print(arreglo a){
  for(int i=0;i<a->nelems;i++){
    printf("%d ",a->datos[i]);
  }
  printf("\n");
}

void ar_agregar(arreglo a, int dato){
  a->datos[a->nelems]=dato;
  a->nelems++;
}

void ar_eliminar(arreglo a){
  for(int i=0;i<a->nelems-1;i++){
    a->datos[i] = a->datos[i+1];
  }
  a->nelems--;
}

void isort(arreglo a){
  int j, aux, k;
  for(int i=0;i<a->capacidad-1;i++){
    j = i+1;
    k = i;
    while(k>=0 && a->datos[k]>a->datos[j]){
      aux = a->datos[k];
      a->datos[k] = a->datos[j];
      a->datos[j] = aux;
      j--;
      k--;
    }
  }
}

void ssort(SList * _lista){
  SList lista = *_lista;
  SList ord = NULL;
  SList nodo;
  int i,minpos,min,j=0;
  while(lista!=NULL){
    min = lista->dato;
    minpos = 1;
    i = 1;
    for(nodo=lista;nodo!=NULL;nodo=nodo->sig,i++){
      if(nodo->dato<min){
        minpos = i;
        min = nodo->dato;
      }
    }
    lista = slist_eliminar(lista,minpos);
    ord = slist_agregar_final(ord,min);
  }
  *_lista = ord;
}

SList slist_msort(SList lista){
  // SPLIT
  int i=1, len = slist_longitud(lista);
  if(len<=1) return lista;
  SList left = slist_crear();
  SList right = slist_crear();
  SList nodo = lista;
  for(;nodo!=NULL;nodo=nodo->sig,i++){
    if(i<=(int)(len/2)){
      left = slist_agregar_inicio(left,nodo->dato);
    }
    else{
      right = slist_agregar_inicio(right,nodo->dato);
    }
  }
  // LLAMADO RECURSIVO
  left = slist_msort(left);
  right = slist_msort(right);
  // MERGE
  SList ret = slist_crear();
  if(slist_vacia(left)) ret = right;
  if(slist_vacia(right)) ret = left;
  while(!slist_vacia(left) && !slist_vacia(right)){
    if(left->dato < right->dato){
      ret = slist_agregar_final(ret,left->dato);
      left = left->sig;
    }
    else{
      ret = slist_agregar_final(ret,right->dato);
      right = right->sig;
    }
  }
  while(!slist_vacia(left)){
    ret = slist_agregar_final(ret,left->dato);
    left = left->sig;
  }
  while(!slist_vacia(right)){
    ret = slist_agregar_final(ret,right->dato);
    right = right->sig;
  }
  return ret;
}

arreglo msort(arreglo a){
  // SPLIT
  if(a->nelems<=1){
    return a;
  }
  arreglo left = ar_crear(a->nelems);
  arreglo right = ar_crear(a->nelems);
  for(int i=0;i<a->nelems;i++){
    if(i<(int)(a->nelems/2)){
      ar_agregar(left,a->datos[i]);
    }
    else{
      ar_agregar(right,a->datos[i]);
    }
  }
  // LLAMADO RECURSIVO
  left = msort(left);
  right = msort(right);
  // MERGE
  arreglo ret = ar_crear(a->nelems);
  while(left->nelems>0 && right->nelems>0){
    if(left->datos[0]<right->datos[0]){
      ar_agregar(ret,left->datos[0]);
      ar_eliminar(left);
    }
    else{
      ar_agregar(ret,right->datos[0]);
      ar_eliminar(right);
    }
  }
  while(left->nelems>0){
      ar_agregar(ret,left->datos[0]);
      ar_eliminar(left);
  }
  while(right->nelems>0){
      ar_agregar(ret,right->datos[0]);
      ar_eliminar(right);
  }
  return ret;
}

SList slist_qsort(SList lista){
  if(lista==NULL||lista->sig==NULL) return lista;
  int pivot = lista->dato;
  SList menores = slist_crear();
  SList mayores = slist_crear();
  for(SList nodo = lista->sig;nodo!=NULL;nodo=nodo->sig){
    if(nodo->dato<=pivot){
      menores = slist_agregar_inicio(menores,nodo->dato);
    }
    else{
      mayores = slist_agregar_inicio(mayores,nodo->dato);
    }
  }
  menores = slist_qsort(menores);
  mayores = slist_qsort(mayores);
  SList m = slist_crear();
  m = slist_agregar_inicio(m,pivot);
  m->sig = mayores;
  SList nodo = menores;
  for(;nodo->sig!=NULL;nodo=nodo->sig);
  nodo->sig = m;
  return menores;
}

int main(int argc, char *argv[]) {

  SList lista = slist_crear();

  lista = slist_agregar_inicio(lista, 6);
  lista = slist_agregar_inicio(lista, 1);
  lista = slist_agregar_inicio(lista, 8);
  lista = slist_agregar_final(lista, 4);

  printf("msort en slist\n");
  slist_recorrer(lista, imprimir_entero);
  SList sorted = slist_msort(lista);
  slist_recorrer(sorted, imprimir_entero);

  printf("qsort en slist\n");
  slist_recorrer(lista, imprimir_entero);
  SList sorted2 = slist_qsort(lista);
  slist_recorrer(sorted2, imprimir_entero);

  printf("ssort en slist\n");
  slist_recorrer(lista, imprimir_entero);
  ssort(&lista);
  slist_recorrer(lista, imprimir_entero);
  slist_destruir(lista);

  printf("isort en arreglos\n");
  arreglo a = ar_crear(5);
  ar_agregar(a,5);
  ar_agregar(a,2);
  ar_agregar(a,7);
  ar_agregar(a,4);
  ar_agregar(a,1);
  ar_print(a);
  isort(a);
  ar_print(a);
  free(a->datos);
  free(a);

  printf("msort en arreglos\n");
  a = ar_crear(5);
  ar_agregar(a,5);
  ar_agregar(a,2);
  ar_agregar(a,7);
  ar_agregar(a,4);
  ar_agregar(a,1);
  ar_print(a);
  arreglo s = msort(a);
  ar_print(s);
  return 0;
}
