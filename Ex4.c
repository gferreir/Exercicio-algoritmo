#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int *v;
	int n;
	int max;
}VetorDinamico;

VetorDinamico criaVetor(int n){
	VetorDinamico vd;
	vd.v = malloc(sizeof(int)*n);
	vd.n = 0;
	vd.max = n;
	return vd;
}

void insereNumero(VetorDinamico *ve){
	ve->n = ve->n +1;
	int i, x;
	scanf("%d", &x);
	for(i = 0; i <= ve->max; i++){
		if(i == ve->n-1){
			ve->v[i] = x;
			return;
		}
	}
}

void buscaElemento(VetorDinamico *ve){
	int i, x;
	printf("Qual valor deseja localizar? ");
	scanf("%d", &x);

	for(i = 0; i < ve->max; i++){
		if(ve->v[i] == x){
            printf("\n");
			printf("O valor %d foi localizado", ve->v[i]);
			return;
		}
	}
	printf("Valor inexistente\n");
}

void deletaElemento(VetorDinamico *ve){
	int num;
	printf("Qual valor deseja excluir? " );
	scanf("%d", &num);
	printf("\n");
	int i, aux, del = 0;
	for(i = 0; i <= ve->n; i++){
		if(num == ve->v[i]){
			aux = ve->v[i+2];
			ve->v[i] = ve->v[i+1];
			ve->v[i+1] = aux;
			del = 1;
			ve->n = ve->n - 1;
		}
	}

	if (del == 0){
		printf("Valor inexistente");
	}

}

void imprimeVetor(VetorDinamico *ve){
	int i;
	for(i = 0; i < ve->n; i++){
		printf("%d  ", ve->v[i]);
	}
}

void copiaVetores(VetorDinamico *ve, VetorDinamico *va){
	int i;
	if(ve->n < va->n){
		printf("\n\nO segundo vetor possui mais elementos que o primeiro. Copiando apenas o que for possivel.\n");
		for(i = 0; i < ve->n; i++){
			ve->v[i] = va->v[i];
		}
	}

	if(ve->n > va->n){
		printf("\n\nO primeiro vetor possui mais valores que o segundo. Os valores restantes permanecerao inalterados.\n");
		for(i = 0; i < va->n; i++){
			ve->v[i] = va->v[i];
		}
	}
}

void inverteVetor(VetorDinamico *ve){
	int x, i;
	int aux;

	for(i = 0; i < ve->n/2; i++){
		x = ve->v[i];
		ve->v[i] = ve->v[ve->n - 1 - i];
		ve->v[ve->n - 1 - i] = x;
	}
}

int main(){
	int x;
	printf("Quantos elementos existem no primeiro vetor? ");
	scanf("%d", &x);
	VetorDinamico d = criaVetor(x);
	printf("\nInsira os %d valores a serem guardados: ", x);
	for(x = 0; x < d.max; x++){
		insereNumero(&d);
	}

	printf("\n\nQuantos elementos existem no segundo vetor? ");
	scanf("%d", &x);
	VetorDinamico c = criaVetor(x);
	printf("\nInsira os %d valores a serem guardados: ", x);
	for(x = 0; x < c.max; x++){
		insereNumero(&c);
	}

	printf("\nPrimeiro vetor: ");
	imprimeVetor(&d);
	printf("\n");
	printf("\nSegundo vetor: ");
	imprimeVetor(&c);

	printf("\n\nDeseja localizar elementos no primeiro ou no segundo vetor? Digite 1 ou 2: ");
	scanf("%d", &x);
	if(x == 1){
        printf("\n");
		buscaElemento(&d);
	}
	else if(x == 2){
        printf("\n");
		buscaElemento(&c);
	}
	else
		printf("\n\nVetor inexistente, pulando para deletar um valor.\n\n");

	printf("\n\nEm qual vetor deseja deletar um elemento? Digite 1 ou 2: ");
	scanf("%d", &x);
	printf("\n");
	if(x == 1)
		deletaElemento(&d);
	else if(x == 2)
		deletaElemento(&c);
	else
		printf("\n\nVetor inexistente, pulando para a copia dos vetores.");


	printf("\nPrimeiro vetor: ");
	imprimeVetor(&d);
	printf("\n");
	printf("\nSegundo vetor: ");
	imprimeVetor(&c);

	copiaVetores(&d, &c);
	printf("\n\n\nCopiando do segundo vetor para o primeiro vetor: \n");
	printf("\nPrimeiro vetor: ");
	imprimeVetor(&d);
	printf("\n");
	printf("\nSegundo vetor: ");
	imprimeVetor(&c);

	printf("\n\nInvertendo o primeiro vetor:");
	inverteVetor(&d);
	printf("\nPrimeiro vetor: ");
	imprimeVetor(&d);


	printf("\n\nInvertendo o segundo vetor:");
	inverteVetor(&c);
	printf("\nSegundo vetor: ");
	imprimeVetor(&c);
	printf("\n");
	return 0;
}
