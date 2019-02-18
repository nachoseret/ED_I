#include <stdlib.h>
#include <stdio.h>

//////////////////////////////////
// ARBOLES BINARIOS DE BUSQUEDA //
//////////////////////////////////

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

void btree_recorrer(BTree raiz, BTreeOrdenDeRecorrido orden, FuncionVisitante visit){
  if(raiz==NULL) return;
  if(orden==1) visit(raiz->dato); 
  btree_recorrer(raiz->left,orden,visit);
  if(orden==0) visit(raiz->dato);
  btree_recorrer(raiz->right,orden,visit);
  if(orden==2) visit(raiz->dato);
}

BTree btree_insertar(BTree raiz, int dato){
  if(raiz==NULL){
  	BTree nodo = malloc(sizeof(BTNodo));
  	nodo->left = NULL;
  	nodo->right = NULL;
  	nodo->dato = dato;
  	return nodo;
  }
  if(dato<=raiz->dato){
  	raiz->left = btree_insertar(raiz->left,dato);
  }
  else{
  	raiz->right = btree_insertar(raiz->right,dato);
  }
  return raiz;
}

BTree btree_buscar(BTree raiz, int dato){
	if(raiz == NULL) return NULL;
	if(raiz->dato == dato) return raiz;
	if(dato < raiz->dato) return btree_buscar(raiz->left,dato);
	return btree_buscar(raiz->right,dato);
}

BTree btree_eliminar(BTree raiz, int dato){
	if(raiz == NULL) return NULL;
	if(dato < raiz->dato){
		raiz->left = btree_eliminar(raiz->left,dato);
		return raiz;
	}
	if(dato > raiz->dato){
		raiz->right = btree_eliminar(raiz->right,dato);
		return raiz;
	}

	if(raiz->left == NULL && raiz->right == NULL){
		return NULL;
	}

	if(raiz->left == NULL){
		return raiz->right;
	}

	if(raiz->right == NULL){
		return raiz->left;
	}

 	BTree nodo = raiz->right;
	while(nodo->left){
		nodo = nodo->left;
	}
	raiz->dato = nodo->dato;
	raiz->right = btree_eliminar(raiz->right,nodo->dato);

	return raiz;
}

int main() {
  BTree raiz = btree_crear();
  raiz = btree_insertar(raiz,5);
  raiz = btree_insertar(raiz,3);
  raiz = btree_insertar(raiz,2);
  raiz = btree_insertar(raiz,4);
  raiz = btree_insertar(raiz,8);
  raiz = btree_insertar(raiz,9);
  btree_recorrer(raiz, BTREE_RECORRIDO_PRE, imprimir_entero);
  printf("\n");
  raiz = btree_eliminar(raiz,3);
  btree_recorrer(raiz, BTREE_RECORRIDO_PRE, imprimir_entero);
  printf("\n");
  btree_destruir(raiz);

  return 0;
}