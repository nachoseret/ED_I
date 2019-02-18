#include <stdio.h>
#include <stdlib.h>

typedef struct _SNodo {
  int dato;
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

int cola_primero(Cola a){
	if(!cola_es_vacia(a)){
		return a->primero->dato;
	}
	return 0;
}

void cola_encolar(Cola a,int dato){
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

void cola_imprimir(Cola a){
	if(!cola_es_vacia(a)){
		SList nodo = a->ultimo;
		for(;nodo!=NULL;nodo=nodo->sig){
			printf("%d ",nodo->dato);
		}
		printf("\n");
	}
	else{
		printf("vacia\n");
	}
}

int main()
{
	Cola a = cola_crear();
	printf("cola_es_vacia = %d\n",cola_es_vacia(a));
	printf("cola_encolar 1 2 3 4 5 6 7 = ");
	cola_encolar(a,1);
	cola_encolar(a,2);
	cola_encolar(a,3);
	cola_encolar(a,4);
	cola_encolar(a,5);
	cola_encolar(a,6);
	cola_encolar(a,7);
	cola_imprimir(a);
	printf("cola_primero = %d\n",cola_primero(a));
	printf("cola_desencolar = ");
	cola_desencolar(a);
	cola_imprimir(a);
	printf("cola_desencolar = ");
	cola_desencolar(a);
	cola_imprimir(a);
	printf("cola_desencolar = ");
	cola_desencolar(a);
	cola_imprimir(a);
	printf("cola_desencolar = ");
	cola_desencolar(a);
	cola_imprimir(a);
	printf("cola_desencolar = ");
	cola_desencolar(a);
	cola_imprimir(a);
	printf("cola_desencolar = ");
	cola_desencolar(a);
	cola_imprimir(a);
	printf("cola_desencolar = ");
	cola_desencolar(a);
	cola_imprimir(a);
	printf("cola_desencolar = ");
	cola_desencolar(a);
	cola_imprimir(a);
	return 0;
}
