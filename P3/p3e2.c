#include <stdio.h>
#include <stdlib.h>

typedef struct _Pila {
	int * datos;
	int capacidad;
	int ultimo;
} _Pila;

typedef _Pila * Pila;

Pila pila_crear(int capacidad){
	Pila a = malloc(sizeof(_Pila));
	a->datos = malloc(sizeof(int)*capacidad);
	a->capacidad = capacidad;
	a->ultimo = -1;
	return a;
}

int pila_es_vacia(Pila a){
	return a->ultimo == -1;
}

int pila_top(Pila a){
	if(!(pila_es_vacia(a))){
		return a->datos[a->ultimo];
	}
	return 0;
}

void pila_push(Pila a, int dato){
	if(a->ultimo<a->capacidad-1){
		a->ultimo++;
		a->datos[a->ultimo] = dato;
	}
}

void pila_pop(Pila a){
	if(pila_es_vacia(a)){
		return;
	}
	a->ultimo--;
}

void pila_imprimir(Pila a){
	if(!(pila_es_vacia(a))){
		for(int i = 0; i<=a->ultimo; i++){
			printf("%d ",a->datos[i]);
		}
		printf("\n");
	}
}

int main()
{
	Pila a = pila_crear(5);
	printf("pila_es_vacia = %d\n", pila_es_vacia(a));
	printf("pila_top = %d\n", pila_top(a));
	pila_push(a,1);
	pila_push(a,2);
	pila_push(a,3);
	pila_push(a,4);
	pila_push(a,5);
	pila_push(a,6);
	pila_push(a,7);
	pila_push(a,8);
	pila_push(a,9);
	pila_push(a,10);
	pila_push(a,11);
	pila_imprimir(a);
	printf("pila_top = %d\n", pila_top(a));
	printf("pila_pop\n");
	pila_pop(a);
	pila_imprimir(a);
	printf("pila_es_vacia = %d\n", pila_es_vacia(a));
	pila_pop(a);
	pila_pop(a);
	pila_pop(a);
	pila_pop(a);
	pila_pop(a);
	pila_pop(a);
	pila_pop(a);
	printf("pila_es_vacia = %d\n", pila_es_vacia(a));
	return 0;
}