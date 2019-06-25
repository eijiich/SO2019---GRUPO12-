//Compilar no terminal usando: gcc MonteCarlo.c -o mc -lm -lgmp

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <gmp.h>

void monteCarlo(int iterations);

int main (){
  srand(time(NULL));
  int iterations = 1000000000; //numero de iterações
  monteCarlo(iterations);
  return 0;
}

void monteCarlo(int iterations){
  //máx precisão
  mpf_set_default_prec(pow(10,5));

  //variaveis
	mpf_t pts, ptsDentro, pi;

	//iniciando as variaveis
  int i;
  double x, y;
  mpf_init(pi);
  mpf_init(pts);
	mpf_init(ptsDentro);

	srand(time(NULL));
	for(i = 0; i < iterations; i++){
		x = ((double)rand()/(double)RAND_MAX);
		y = ((double)rand()/(double)RAND_MAX);

		//se x²+y² <= 1
    //adiciona o ponto ao array de pontos dentro
		if(x*x + y*y <= 1){
			mpf_add_ui(ptsDentro, ptsDentro, 1);
		}
	}

  //O número total de pontos é igual o de iterações
  //pi = 4*ptsDentro/pts
  mpf_mul_ui(ptsDentro, ptsDentro, 4);
  mpf_init_set_ui(pts, iterations);
	mpf_div(pi, ptsDentro, pts);
  gmp_printf("Monte Carlo : %.6Ff\n", pi);

  //limpando as variaveis
  mpf_clear(pi);
  mpf_clear(pts);
	mpf_clear(ptsDentro);
}
