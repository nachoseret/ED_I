#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int * direccion;
	int capacidad;
} ArregloEnteros;

ArregloEnteros * arreglo_enteros_crear(int capacidad){
	ArregloEnteros * a = malloc(sizeof(ArregloEnteros));
	a->direccion = malloc(sizeof(int)*capacidad);
	a->capacidad = capacidad;
	return a;
}

void arreglo_enteros_imprimir(ArregloEnteros * a){
	if(a==NULL || a->direccion==NULL){
		return;
	}
	int i = 0;
	for(i = 0;i<a->capacidad;i++){
		printf("%d ",a->direccion[i]);
	}
	printf("\n");
}

void arreglo_enteros_escribir(ArregloEnteros * a, int pos, int dato){
	if(a==NULL || a->direccion==NULL || pos >= a->capacidad){
		return;
	}
	a->direccion[pos] = dato;
}

void arreglo_enteros_ajustar(ArregloEnteros * a, int capacidad){
	if(a==NULL || capacidad <= 0){
		return;
	}
	a->direccion = realloc(a->direccion, sizeof(int)*capacidad);
	a->capacidad = capacidad;
}

void arreglo_enteros_insertar(ArregloEnteros * a, int pos, int dato){
	if(a==NULL || a->direccion==NULL || pos >= a->capacidad || pos <= 0){
		return;
	}
	arreglo_enteros_ajustar(a,a->capacidad+1);
	for(int i=a->capacidad-1; i>=pos; i--){
		a->direccion[i] = a->direccion[i-1];
	}
	a->direccion[pos-1] = dato;
}

void arreglo_enteros_eliminar(ArregloEnteros * a, int pos){
	if(a==NULL || a->direccion==NULL || pos > a->capacidad || pos <= 0){
		return;
	}
	for(int i=pos-1; i<a->capacidad; i++){
		a->direccion[i] = a->direccion[i+1];
	}
	arreglo_enteros_ajustar(a,a->capacidad-1);
}

int main()
{
	ArregloEnteros * a = arreglo_enteros_crear(5);
	arreglo_enteros_escribir(a,0,1);
	arreglo_enteros_escribir(a,1,2);
	arreglo_enteros_escribir(a,2,3);
	arreglo_enteros_escribir(a,3,4);
	arreglo_enteros_escribir(a,4,5);
	arreglo_enteros_imprimir(a);
	arreglo_enteros_eliminar(a,1);
	arreglo_enteros_imprimir(a);
	return 0;
}