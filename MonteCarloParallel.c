//Compilar no terminal usando: gcc MonteCarloParallel.c -o mc -lm -lgmp -lpthread

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <gmp.h>
#include <pthread.h>

#define parallelIterations 25000000 //numero total de iterações dividido por 4
#define threadNumber 4

void *monteCarlo(void *iterations);

//Variáveis globais
mpf_t threadPtsDentro[threadNumber], pi, ptsDentro;

int main (){
	//máx precisão
	mpf_set_default_prec(pow(10,5));
	srand(time(NULL));

	//iniciando variáveis
	int i;
	mpf_t pts;
	mpf_init(pi);
	mpf_init(pts);
	mpf_init(ptsDentro);

	//IDs das threads
	pthread_t tid[threadNumber];

	//Criação de threadNumber threads
	for (i = 0; i < threadNumber; i++){
		pthread_create (&tid[i], NULL, monteCarlo, &i);
  }

	//Espera que o termino das threads
	for (i = 0; i < threadNumber; i++){
		pthread_join (tid[i], NULL);
	}

	//Contagem do número de pontos dentro do circulo
	for (i = 0; i < threadNumber; i++){
		mpf_add(ptsDentro, ptsDentro, threadPtsDentro[i]);
	}

	mpf_mul_ui(pi, ptsDentro, 4);
	mpf_init_set_ui(pts, threadNumber*parallelIterations);
	mpf_div(pi,pi,pts);
	gmp_printf("Monte Carlo : %.6Ff\n", pi);

	//limpando as variaveis
	mpf_clear(pi);
	mpf_clear(pts);
	mpf_clear(ptsDentro);
}

void *monteCarlo(void *iterations){
	int thrnum = *((int *)iterations);

	//máx precisao
	mpf_set_default_prec(pow(10,5));


	int i;
	double x, y;
	mpf_init(threadPtsDentro[thrnum]);

	for(i = 0; i < parallelIterations; i++){
		x = ((double)rand()/(double)RAND_MAX);
		y = ((double)rand()/(double)RAND_MAX);

		//se x²+y² <= 1
		//adiciona o ponto ao array de pontos dentro
		if( ((x*x) + (y*y)) <= 1){
			mpf_add_ui(threadPtsDentro[thrnum], threadPtsDentro[thrnum],1);
		}
	}
	pthread_exit(0);
}
