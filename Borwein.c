//Compilar no terminal usando: gcc Borwein.c -o bw -lm -lgmp

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <gmp.h>

void borwein(int iterations);

int main (){
	//numero de interações
	int iterations = 100000;

	borwein(iterations);
	return 0;
}


void borwein(int iterations){
	//definindo a precisao
	mpf_set_default_prec(pow(10,5));

	//declaração das variaveis
	int i;
	mpf_t pi, aux,aux2, aux3, aux4, aux5, aux6, aux7;

	//constantes cn onde n é o valor da constante
	//k8 é 8*k, sendo k a k-esima iteração
	mpf_t k8, c1, c2, c4, c8, c16;

	mpf_init(pi);
	mpf_init(k8);
	mpf_init(aux);
	mpf_init(aux2);
	mpf_init(aux3);
	mpf_init(aux4);
	mpf_init(aux5);
	mpf_init(aux6);
	mpf_init(aux7);

	//setando as constanstes
	mpf_init_set_ui(c1,1);
	mpf_init_set_ui(c2,2);
	mpf_init_set_ui(c4,4);
	mpf_init_set_ui(c8,8);
	mpf_init_set_ui(c16,16);

	for(i = 0; i < iterations; i++){
		//aux2 = 1 / (16^i);
		mpf_pow_ui(aux2, c16, i);
		mpf_div(aux2, c1, aux2);

		//aux3 = 4 / (8*i + 1);
		mpf_mul_ui(k8, c8, i);
		mpf_add_ui(aux3,k8, 1);
		mpf_div(aux3, c4, aux3);

		//aux4 = 2 / (8*i + 4);
		mpf_add_ui(aux4, k8, 4);
		mpf_div(aux4, c2, aux4);

		//aux5 = 1 / (8*i + 5);
		mpf_add_ui(aux5, k8, 5);
		mpf_div(aux5, c1, aux5);

		//aux6 = 1 / (8*i + 6);
		mpf_add_ui(aux6, k8, 6);
		mpf_div(aux6, c1, aux6);

		//aux7 = (aux3) - (aux4) - (aux5) - (aux6)
		//aux = (1/aux2) * (aux7);
		mpf_sub(aux7,aux3,aux4);
		mpf_sub(aux7,aux7,aux5);
		mpf_sub(aux7,aux7,aux6);
		mpf_mul(aux,aux2,aux7);

		//pi = pi + aux;
		mpf_add(pi, pi, aux);
	}
	gmp_printf("Borwein : %.6Ff\n", pi);

	mpf_clear(pi);
	mpf_clear(k8);
	mpf_clear(aux);
	mpf_clear(aux2);
	mpf_clear(aux3);
	mpf_clear(aux4);
	mpf_clear(aux5);
	mpf_clear(aux6);
	mpf_clear(aux7);
}
