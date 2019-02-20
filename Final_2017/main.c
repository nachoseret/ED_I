#include <stdlib.h>
#include <stdio.h>

typedef struct {
	char * dni, * nombre, * descripcionCargo;
	int prioridad;
} _Invitado;

typedef _Invitado * Invitado;

typedef struct _Nodo
{
	Invitado invitado;
	struct _Nodo * r;
	struct _Nodo * l;
} Nodo;

typedef Nodo * Arbol;

#define MAX_HEAP 20

typedef struct
{
	Invitado datos[MAX_HEAP];
	int nelems;
} _BHeap;

typedef _BHeap * BHeap;

int padre(int i){
	if(i%2==0) return (i-2)/2;
	return (i-1)/2;
}

int left(int i){
	return (2*i)+1;
}

int right(int i){
	return (2*i)+2;
}

BHeap crearHeap(){
	BHeap a = malloc(sizeof(_BHeap));
	a->nelems = 0;
	return a;
}

Invitado crearInvitado(int prioridad){
	Invitado a = malloc(sizeof(_Invitado));
	a->dni = malloc(sizeof(char)*10);
	a->nombre = malloc(sizeof(char)*10);
	a->descripcionCargo = malloc(sizeof(char)*10);
	a->prioridad = prioridad;
	return a;
}

BHeap agregar(BHeap heap, Invitado a){
	if(heap->nelems==MAX_HEAP) return heap;
	heap->datos[heap->nelems]=a;
	heap->nelems+=1;
	Invitado aux;
	for(int i=heap->nelems-1;i>0;i=padre(i)){
		if(heap->datos[i]->prioridad > heap->datos[padre(i)]->prioridad){
			aux = heap->datos[padre(i)];
			heap->datos[padre(i)] = heap->datos[i];
			heap->datos[i] = aux;
		}
	}
	return heap;
}

void mostrarHeap(BHeap a){
	for(int i=0;i<a->nelems;i++){
		printf("%d ", a->datos[i]->prioridad);
	}
	printf("\n");
}

Arbol crearNodo(Invitado a){
	Arbol b = malloc(sizeof(Nodo));
	b->invitado = a;
	b->l = NULL;
	b->r = NULL;
	return b;
}

Arbol insertaHeapEnArbol(BHeap heap, int pos){
	Arbol a = crearNodo(heap->datos[pos]);
	if(left(pos)<heap->nelems){
		a->l = insertaHeapEnArbol(heap, left(pos));
	}
	if(right(pos)<heap->nelems){
		a->r = insertaHeapEnArbol(heap, right(pos));
	}
	return a;
}


Arbol convierteHeapEnArbol(BHeap heap){
	if(heap->nelems==0) return NULL;
	Arbol a = insertaHeapEnArbol(heap,0);
	return a;
}

void mostrarArbolPreorder(Arbol a){
	if(a==NULL) return;
	printf("%d ",a->invitado->prioridad);
	mostrarArbolPreorder(a->l);
	mostrarArbolPreorder(a->r);
	return;
}

void insertaArbolEnHeap(Arbol arbol, BHeap heap){
	if(arbol==NULL) return;
	heap = agregar(heap, arbol->invitado);
	insertaArbolEnHeap(arbol->l, heap);
	insertaArbolEnHeap(arbol->r, heap);
}

BHeap convierteArbolEnHeap(Arbol inicio){
	BHeap a = crearHeap();
	insertaArbolEnHeap(inicio,a);
	return a;
}

int main()
{
	BHeap heap = crearHeap();
	Invitado a = crearInvitado(35);
	Invitado b = crearInvitado(33);
	Invitado c = crearInvitado(42);
	Invitado d = crearInvitado(10);
	Invitado e = crearInvitado(14);
	Invitado f = crearInvitado(19);
	heap = agregar(heap,a);
	mostrarHeap(heap);
	heap = agregar(heap,b);
	mostrarHeap(heap);
	heap = agregar(heap,c);
	mostrarHeap(heap);
	heap = agregar(heap,d);
	mostrarHeap(heap);
	heap = agregar(heap,e);
	mostrarHeap(heap);
	heap = agregar(heap,f);
	mostrarHeap(heap);
	Arbol arbol = convierteHeapEnArbol(heap);
	mostrarArbolPreorder(arbol);
	printf("\n");
	BHeap heap2 = convierteArbolEnHeap(arbol);
	mostrarHeap(heap2);

	return 0;
}