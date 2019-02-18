#include <stdio.h>
#include <stdlib.h>

#define MAX_COLA 5

typedef struct _Cola {
	int datos[MAX_COLA];
	int primero,ultimo;
} _Cola;

typedef _Cola * Cola;

Cola cola_crear(){
	Cola a = malloc(sizeof(_Cola));
	a->primero = -1;
	a->ultimo = -1;
	return a;
}

int cola_es_vacia(Cola a){
	return a == NULL || a->primero == -1;
}

int cola_primero(Cola a){
	if(!cola_es_vacia(a)){
		return a->datos[a->primero];
	}
	return 0;
}

void cola_encolar(Cola a, int dato){
	if(cola_es_vacia(a)){
		a->primero = 0;
		a->datos[a->primero] = dato;
		a->ultimo = 1;
		return;
	}
	if(a->primero != a->ultimo){
		a->datos[a->ultimo] = dato;
		a->ultimo = (a->ultimo+1)%MAX_COLA;
	}
}

void cola_desencolar(Cola a){
	if(!cola_es_vacia(a)){
		a->primero = (a->primero+1)%MAX_COLA;
	}
	if(a->primero == a->ultimo){
		a->primero = -1;
	}
}

void cola_imprimir(Cola a){
	if(!cola_es_vacia(a)){
		int i = a->primero;
		while(1){
			printf("%d ",a->datos[i]);
			i=(i+1)%MAX_COLA;
			if(i==a->ultimo) break;
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