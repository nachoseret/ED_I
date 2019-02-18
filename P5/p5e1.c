#include <stdlib.h>
#include <stdio.h>

typedef void (*FuncionVisitante) (int dato);

typedef enum {
  BTREE_RECORRIDO_IN,
  BTREE_RECORRIDO_PRE,
  BTREE_RECORRIDO_POST
} BTreeOrdenDeRecorrido;

typedef struct _BTNodo {
  int dato;
  struct _BTNodo *left;
  struct _BTNodo *right;
} BTNodo;

typedef BTNodo * BTree;

//////////
// COLA //
//////////

typedef struct _SNodo {
  BTree dato;
  struct _SNodo *sig;
} SNodo;

typedef SNodo * SList;

typedef struct _Cola {
  SList primero;
  SList ultimo;
} _Cola;

typedef _Cola * Cola;

Cola cola_crear(){
  Cola a = malloc(sizeof(_Cola));
  a->primero = NULL;
  a->ultimo = NULL;
  return a;
}

int cola_es_vacia(Cola a){
  return a == NULL || a->primero == NULL;
}

BTree cola_primero(Cola a){
  if(!cola_es_vacia(a)){
    return a->primero->dato;
  }
  return NULL;
}

void cola_encolar(Cola a,BTree dato){
  SList nodo = malloc(sizeof(SNodo));
  nodo->dato = dato;
  nodo->sig = a->ultimo;
  a->ultimo = nodo;
  if(cola_es_vacia(a)){
    a->primero = nodo;
  }
}

void cola_desencolar(Cola a){
  if(cola_es_vacia(a)) return;
  if(a->ultimo->sig==NULL){
    free(a->ultimo);
    a->primero=NULL;
    a->ultimo=NULL;
    return;
  }
  SList nodo = a->ultimo;
  for(;nodo->sig->sig!=NULL;nodo=nodo->sig);
  free(a->primero);
  nodo->sig = NULL;
  a->primero = nodo;
}

/////////////
// ARBOLES //
/////////////

static void imprimir_entero(int data) {
  printf("%d ", data);
}

BTree btree_crear() {
  return NULL;
}

void btree_destruir(BTree nodo) {
  if (nodo != NULL) {
    btree_destruir(nodo->left);
    btree_destruir(nodo->right);
    free(nodo);
  }
}

BTree btree_unir(int dato, BTree left, BTree right) {
  BTree nuevoNodo = malloc(sizeof(BTNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->left = left;
  nuevoNodo->right = right;
  return nuevoNodo;
}

void btree_recorrer(BTree raiz, BTreeOrdenDeRecorrido orden, FuncionVisitante visit){
  if(raiz==NULL) return;
  if(orden==1) visit(raiz->dato); 
  btree_recorrer(raiz->left,orden,visit);
  if(orden==0) visit(raiz->dato);
  btree_recorrer(raiz->right,orden,visit);
  if(orden==2) visit(raiz->dato);
}

void btree_bfs(BTree raiz, FuncionVisitante visit){
  BTree temp = raiz;
  Cola a = cola_crear();
  while(temp){
    visit(temp->dato);
    if(temp->left){
      cola_encolar(a,temp->left);
    }
    if(temp->right){
      cola_encolar(a,temp->right);
    }
    temp = cola_primero(a);
    cola_desencolar(a);
  }
}

int main() {
  BTree ll = btree_unir(1, btree_crear(), btree_crear());
  BTree l = btree_unir(2, ll, btree_crear());
  BTree r = btree_unir(3, btree_crear(), btree_crear());
  BTree raiz = btree_unir(4, l, r);

  btree_recorrer(raiz, BTREE_RECORRIDO_PRE, imprimir_entero);
  printf("\n");
  btree_bfs(raiz,imprimir_entero);
  puts("");
  btree_destruir(raiz);

  return 0;
}