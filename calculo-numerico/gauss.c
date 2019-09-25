#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define EPSILON 0.000001

/*Se houver memória disponível, aloca uma matriz bidimencional de double com l linhas e c colunas
 e devolve um ponteiro para essa matriz; Caso contrário, devolve um ponteiro nulo*/
double **aloca_matriz(int l, int c);

/*Lê valores para uma matriz de double alocada dinamicamente com l linhas e c colunas*/
void le_matriz(double **m, int l, int c);

/*imprime uma matriz de double com l linhas e c colunas*/
void imprime_matriz(double **m, int l, int c);

/*Recebe m, a matriz reduzida de um sl ts com n varapaveis. se o sl for determinado, coloca com x a solução do sl e devolve 0;
 se for determinado, coloca em x uma dsolução e devolve 1; se for incompativel=, devolve 2*/
 int sretro(double **m, int n, double x[]); 

/*recebe m, a matriz aumentada de um sl com n vários, e transforma m na matriz aumentadad de um sl ts equivalente*/
void gauss(double **m, int n);

int main(){
	
	int n, i, tipo;
	double **A, *x;
	printf("Quantidade de variaveis: ");
	scanf("%d", &n);
	A = aloca_matriz(n, n+1);
	x = malloc(sizeof(double)*n);
	if(A == NULL || x == NULL) /*falta de memória*/	
	{
		printf("Deu pau\nFalta de memória");
		return 1;
	}
	le_matriz(A, n, n+1);
	imprime_matriz(A, n, n+1);
	gauss(A,n);
	printf("SL TS:\n");
	imprime_matriz(A, n, n+1);
	tipo = sretro(A, n, x);
	if(tipo == 2){
		printf("LS INCOMPATIVEL");
	}else{
		printf("SL %sDETERMINADO\n", tipo?"IN":"");
		for(i=0; i<n; i++){
			printf("x[%d]: %10.2lf\n", i+1, x[i]);
		}
	}
	
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

int sretro(double **m, int n, double x[]){
	int i, j, tipo = 0;
	double soma;
	for(i=n-1; i>=0; i--){
		soma = 0;
		for (j=i+1; j<n; j++){
			soma += m[i][j]*x[j];
		}
		if(m[i][i] == 0){
			if( fabs(m[i][n]-soma) < EPSILON){  /*xi é variável livre*/
				tipo = 1;
				x[i] = 0;
			}
			else {	return 2; }							
		}
		else{
			x[i] = (m[i][n] - soma)/m[i][i];
		}
	}
	return tipo;
}/*fim do sretro*/

void gauss(double **m, int n){
	int i, j, k;
	double mult, *aux;
	for (i = 0; i<n-1; i++){
		if(m[i][i] == 0){/*pivô nulo*/
			j = i+1;
			while (j<n && m[j][i] == 0){j++;}
			if(j<n) /*trocando as linhas i e j*/
			{
				aux = m[i];
				m[i] = m[j];
				m[j] = aux;
			}
		}
		if(m[i][i] != 0){
			for(j=i+1; j<n; j++){
				mult = -m[j][i]/m[i][i];
				m[j][i] = 0;
				for(k=i+1; k <= n; k++){
					m[j][k] += mult*m[i][k];
				}
			}
			
		}
	}
}
