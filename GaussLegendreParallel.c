//Compilar no terminal usando: gcc GaussLegendreParallel.c -o bw -lm -lgmp

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <gmp.h>
#include <pthread.h>

#define iterations 10000

void gauss();
void *ValueOfa();
void *ValueOfb();

//variáveis globais
mpf_t p, a, b, t;
mpf_t aNext, bNext, tNext, aux;

int main (){
  gauss();
  return 0;
}


void gauss(){
  //definindo a precisao
  mpf_set_default_prec(pow(10,5));

  //declarando e inicializanodo variáveis
  mpf_t pi,aux2;

  mpf_init(pi);
  mpf_init(aNext);
  mpf_init(bNext);
  mpf_init(tNext);
  mpf_init(aux);
  mpf_init(aux2);

  //definindo a,b,p e t iniciais
  mpf_init_set_d(a, 1);
  mpf_init_set_d(b, 1/sqrt(2));
  mpf_init_set_d(t, 0.25);
  mpf_init_set_d(p, 1);

  // ID das threads
  pthread_t tidAuxa[iterations];
  pthread_t tidAuxb[iterations];

    int i;
  for(i = 0; i < iterations; i++){

    // Calculo dos valores de a e b
    pthread_create (&tidAuxa[i], NULL, ValueOfa, &i);
    pthread_create (&tidAuxb[i], NULL, ValueOfb, &i);

    //Espera o fim das threads
    pthread_join(tidAuxa[i],NULL);
    pthread_join(tidAuxb[i],NULL);

    //tNext = t - p*(aux^2) --> t(n+1)
    mpf_mul(aux2, p, aux);
    mpf_sub(tNext, t, aux2);

    //atualiza as variáveis
    mpf_mul_ui(p, p, 2);
    mpf_set(a,aNext);
    mpf_set(b,bNext);
    mpf_set(t,tNext);
  }
  //calcula pi
  mpf_add(a, a, b);
  mpf_pow_ui(a, a, 2);
  mpf_mul_ui(t,t, 4);
  mpf_div(pi, a,t);
  gmp_printf("Gauss : %.6Ff\n", pi);

  //limpando variaveis
  mpf_clear(a);
  mpf_clear(b);
  mpf_clear(t);
  mpf_clear(p);
  mpf_clear(pi);
  mpf_clear(aNext);
  mpf_clear(bNext);
  mpf_clear(tNext);
  mpf_clear(aux);
  mpf_clear(aux2);
}

void *ValueOfa(){
  //aNext = (a + b)/2 --> a(n+1)
  mpf_add(aNext, a, b);
  mpf_div_ui(aNext,aNext,2);

  //aux = a - aNext;
  mpf_sub(aux, a, aNext);
  mpf_pow_ui(aux, aux, 2);

  pthread_exit(0);
}

void *ValueOfb(){
  //bNext = sqrt(a * b) --> b(n+1)
  mpf_mul(bNext, a, b);
  mpf_sqrt(bNext, bNext);

  pthread_exit(0);
}
