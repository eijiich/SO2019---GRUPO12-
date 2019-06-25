//Compilar no terminal usando: gcc Borwein.c -o bw -lm -lgmp -lpthread

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <gmp.h>
#include <pthread.h>

#define iterations 100000

void *valueAux2(void *iteration);
void *valueAux3(void *iteration);
void *valueAux4(void *iteration);
void *valueAux5(void *iteration);
void *valueAux6(void *iteration);
void borwein();

//declaração das variaveis
mpf_t aux, aux2, aux3, aux4, aux5, aux6, aux7;
mpf_t k8, pi, c1, c2, c4, c8, c16;

int main (){

	borwein();

	//limpando variaveis
	mpf_clear(k8);
	mpf_clear(pi);
	mpf_clear(aux);
	mpf_clear(aux2);
	mpf_clear(aux3);
	mpf_clear(aux4);
	mpf_clear(aux5);
	mpf_clear(aux6);
	mpf_clear(aux7);
	mpf_clear(c1);
	mpf_clear(c2);
	mpf_clear(c4);
	mpf_clear(c8);
	mpf_clear(c16);
	return 0;
}

void *valueAux2(void *iteration){
	int i = *((int *)iteration);
	//aux2 = 1 / (16^i);
	mpf_pow_ui(aux2, c16, i);
	mpf_div(aux2, c1, aux2);
	pthread_exit(0);
}

void *valueAux3(void *iteration){
	int thrnum3 = *((int *)iteration);

	//aux3 = 4 / (8*i + 1);
	mpf_add_ui(aux3,k8, 1);
	mpf_div(aux3, c4, aux3);
	pthread_exit(0);
}

void *valueAux4(void *iteration){
	int thrnum4 = *((int *)iteration);

	//aux4 = 2 / (8*i + 4);
	mpf_add_ui(aux4, k8, 4);
	mpf_div(aux4, c2, aux4);
	pthread_exit(0);
}

void *valueAux5(void *iteration){
	int thrnum5 = *((int *)iteration);

	//aux5 = 1 / (8*i + 5);
	mpf_add_ui(aux5, k8, 5);
	mpf_div(aux5, c1, aux5);
	pthread_exit(0);
}

void *valueAux6(void *iteration){
	int thrnum6 = *((int *)iteration);

	//aux6 = 1 / (8*i + 6);
	mpf_add_ui(aux6, k8, 6);
	mpf_div(aux6, c1, aux6);
	pthread_exit(0);
}

void borwein(){
	//máx precisao
	mpf_set_default_prec(pow(10,5));

	//inicializando variaveis
	int i = 0;
	mpf_init(pi);
	mpf_init(k8);
	mpf_init(aux);
	mpf_init(aux2);
	mpf_init(aux3);
	mpf_init(aux4);
	mpf_init(aux5);
	mpf_init(aux6);
	mpf_init(aux7);

	//setando constantes
	mpf_init_set_ui(c1,1);
	mpf_init_set_ui(c2,2);
	mpf_init_set_ui(c4,4);
	mpf_init_set_ui(c8,8);
	mpf_init_set_ui(c16,16);

	// ID das threads
	pthread_t tidAux2[iterations];
	pthread_t tidAux3[iterations];
	pthread_t tidAux4[iterations];
	pthread_t tidAux5[iterations];
	pthread_t tidAux6[iterations];

	for(i = 0; i < iterations; i++){

		mpf_mul_ui(k8, c8, i);
		// Calculo dos valores auxiliares
		pthread_create (&tidAux2[i], NULL, valueAux2, &i);
		pthread_create (&tidAux3[i], NULL, valueAux3, &i);
		pthread_create (&tidAux4[i], NULL, valueAux4, &i);
		pthread_create (&tidAux5[i], NULL, valueAux5, &i);
		pthread_create (&tidAux6[i], NULL, valueAux6, &i);


		//Espera o fim das threads
		pthread_join (tidAux2[i], NULL);
		pthread_join (tidAux3[i], NULL);
		pthread_join (tidAux4[i], NULL);
		pthread_join (tidAux5[i], NULL);
		pthread_join (tidAux6[i], NULL);

		//Calcula o resultado de uma iteração
		//aux7 = (aux3) - (aux4) - (aux5) - (aux6)
		//aux = (1/aux2) * (aux7);
		mpf_sub(aux7,aux3,aux4);
		mpf_sub(aux7,aux7,aux5);
		mpf_sub(aux7,aux7,aux6);
		mpf_mul(aux,aux2,aux7);
		mpf_add(pi, pi, aux);
	}

	gmp_printf("Borwein : %.6Ff\n", pi);
}
