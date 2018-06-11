#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int a;
	int b;
}XPTO;

void criaVetor(XPTO* v, int n){
	int i;
	for(i = 0; i < n; i++){
		v[i].a = i%3;
		v[i].b = 100 - i%5;
	}
}

void imprimeVetor(XPTO* v, int n){
	int i;
	for(i = 0; i < n; i++){
		printf("a = %d, b = %d\n", v[i].a, v[i].b);
	}
}

int porA(void* p1, void* p2){
	XPTO* pp1 = p1;
	XPTO* pp2 = p2;
	return pp1->a < pp2->a;
}

int porB(void* p1, void* p2){
	XPTO* pp1 = p1;
	XPTO* pp2 = p2;
	return pp1->b < pp2->b;
}

void merge(XPTO *v, int i, int m, int f){

	int a = i;
	int b = m;
	int k = 0;

	int *v2 = malloc(sizeof(int)* (f-i+1) );

	while( a < m && b <= f){
		if( v[a] < v[b]){
			v2[k] = v[a];
			a++;
		}else{
			v2[k] = v[b];
			b++;
		}
		k++;
	}

	while( a < m ){
		v2[k] = v[a];
		a++;
		k++;
	}
	while( b <= f ){
		v2[k] = v[b];
		b++;
		k++;
	}

	copiaVetor(v+i, v2, f-i+1);

	free(v2);

}

int main(int argc, char* argv[]){
	XPTO v[10];
	criaVetor(v, 10);

	merge(&v, sizeof(XPTO), 10, porA);

	imprimeVetor(v, 10);

	return 0;
}
