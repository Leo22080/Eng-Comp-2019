#include <stdio.h>
#include <stdlib.h>

/*Se houver memória disponível, aloca uma matriz bidimencional de double com l linhas e c colunas
 e devolve um ponteiro para essa matriz; Caso contrário, devolve um ponteiro nulo*/
double **aloca_matriz(int l, int c);

/*Lê valores para uma matriz de double alocada dinamicamente com l linhas e c colunas*/
void le_matriz(double **m, int l, int c);

/*imprime uma matriz de double com l linhas e c colunas*/
void imprime_matriz(double **m, int l, int c);	

int main(){
	
	int n;
	double **A;
	printf("Quantidade de variáveis: ");
	scanf("%d", &n);
	A = aloca_matriz(n, n+1);
	if(A == NULL) /*falta de memória*/	
	{
		printf("Deu pau\nFalta de memória");
		return 1;
	}
	le_matriz(A, n, n+1);
	imprime_matriz(A, n, n+1);
	return 0;
}/*fim do main*/

double **aloca_matriz(int l, int c){
	double **m;
	int i, j;
	m = malloc(sizeof(m)*l);
	if(m == NULL) /*falta de memória*/
		return NULL;
			
	for(i=0; i<l; i++){ /*alocar as linhas*/
		m[i] = malloc(sizeof(double)*c);
		if(m[i] == NULL){
			for(j=0; j<i; i++)
				free(m[j]);
			free(m);
			return NULL;
		} 
	}
	return m;
}/*fim do aloca_matriz*/

void le_matriz(double **m, int l, int c){
	int i, j;
	for(i=0; i<l; i++){
		for(j=0; j<c; j++){
			printf("m[%d][%d]: ", i+1, j+1);
			scanf("%lf", &m[i][j]);
		}
	}
}/*fim do le_matriz*/

void imprime_matriz(double **m, int l, int c){
	int i, j;
	for(i=0; i<l; i++){
		for(j=0; j<c; j++){
			printf("%10.4lf", m[i][j]);
		}
		printf("\n");
	}
}
