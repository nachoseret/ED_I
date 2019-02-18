#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP 7

typedef struct _BHeap {
	int datos[MAX_HEAP];
	int nelems;
} _BHeap;

typedef _BHeap * BHeap;

BHeap bheap_crear(){
	BHeap a = malloc(sizeof(_BHeap));
	a->nelems = 0;
	return a;
}

int bheap_es_vacio(BHeap a){
	return a == NULL || a->nelems == 0;
}

int bheap_minimo(BHeap a){
	if(!bheap_es_vacio(a)){
		return a->datos[0];
	}
	return 0;
}

int padre(int i){
	return (i-1)/2;
}

int l(int i){
	return (2*i)+1;
}

int r(int i){
	return (2*i)+2;
}

int min_hijo(BHeap a, int i){
	if(l(i)>a->nelems-1) return -1;
	if(l(i)==a->nelems-1 || r(i)>a->nelems-1) return l(i);
	int min = l(i);
	if(a->datos[r(i)]<a->datos[l(i)]) min = r(i);
	return min;
}

void bheap_eliminar_minimo(BHeap a){
	a->datos[0] = a->datos[a->nelems-1];
	a->nelems--;
	int min=min_hijo(a,0), aux, i=0;
	while(a->datos[i]>a->datos[min]){
		min = min_hijo(a,i);
		if(min==-1) break;
		aux = a->datos[min];
		a->datos[min] = a->datos[i];
		a->datos[i] = aux;
		i = min;
	}
}

void bheap_insertar(BHeap a, int dato){
	if(a->nelems >= MAX_HEAP) return;
	a->datos[a->nelems] = dato;
	int i = a->nelems;
	int aux;
	a->nelems++;
	while(i>=0 && a->datos[i]<a->datos[padre(i)]){
		aux = a->datos[i];
		a->datos[i] = a->datos[padre(i)];
		a->datos[padre(i)] = aux;
		i = padre(i);
	}
}

void bheap_imprimir(BHeap a){
	for(int i=0;i<a->nelems;i++){
		printf("%d ",a->datos[i]);
	}
	printf("\n");
}

int main()
{
	BHeap a = bheap_crear();
	printf("bheap_es_vacio = %d\n", bheap_es_vacio(a));
	bheap_insertar(a,4);
	bheap_insertar(a,5);
	bheap_insertar(a,17);
	bheap_insertar(a,19);
	bheap_insertar(a,36);
	printf("bheap_insertar 4 5 17 19 36\n");
	printf("nelems = %d\n",a->nelems);
	bheap_imprimir(a);
	bheap_insertar(a,1);
	printf("bheap_insertar 1\n");
	printf("nelems = %d\n",a->nelems);
	bheap_imprimir(a);
	bheap_insertar(a,2);
	printf("bheap_insertar 2\n");
	printf("nelems = %d\n",a->nelems);
	bheap_imprimir(a);

	printf("bheap_eliminar\n");
	bheap_eliminar_minimo(a);
	printf("nelems = %d\n",a->nelems);
	bheap_imprimir(a);
	printf("bheap_eliminar\n");
	bheap_eliminar_minimo(a);
	printf("nelems = %d\n",a->nelems);
	bheap_imprimir(a);
	return 0;
}