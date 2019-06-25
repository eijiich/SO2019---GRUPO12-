//Compilar no terminal usando: gcc GaussLegendre.c -o bw -lm -lgmp

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <gmp.h>

void gaussLegendre(int numero_iteracoesG);

int main (){
  int iterations = 10000;
  gaussLegendre(iterations);
  return 0;
}

void gaussLegendre(int numero_iteracoesG){
  //máx precisão
  mpf_set_default_prec(pow(10,5));

  //declarando e inicializanodo variáveis
  mpf_t a, b, t, p, sqrtab, tNextAux;
  mpf_t pi, aNext, bNext, tNext, aux, aux2;

  //setando valores iniciais de a,b,p e t
  mpf_init_set_d(a, 1);
  mpf_init_set_d(b, 1/sqrt(2));
  mpf_init_set_d(t, 0.25);
  mpf_init_set_d(p, 1);
  mpf_init(pi);
  mpf_init(aNext);
  mpf_init(bNext);
  mpf_init(tNext);
  mpf_init(aux);
  mpf_init(aux2);
  mpf_init(sqrtab);
  mpf_init(tNextAux);

  int i;
  for(i = 0; i < numero_iteracoesG; i++){
    //aNext = (a + b)/2 --> a(n+1)
    mpf_add(aux, a, b);
    mpf_div_ui(aNext,aux,2);

    //bNext = sqrt(a * b) --> b(n+1)
    mpf_mul(sqrtab, a, b);
    mpf_sqrt(bNext, sqrtab);

    //aux = a - aNext;
    mpf_sub(aux, a, aNext);

    //tNext = t - p*aux^2 --> t(n+1)
    mpf_pow_ui(aux, aux, 2);
    mpf_mul(tNextAux, p, aux);
    mpf_sub(tNext, t, tNextAux);

    //p = p * 2 --> p(n+1)
    mpf_mul_ui(p, p, 2);

    //atualiza as variáveis
    mpf_set(a,aNext);
    mpf_set(b,bNext);
    mpf_set(t,tNext);
  }
  //calculo de pi

  //aux = a + b;
  mpf_add(aux, a, b);

  //aux  = aux^2
  mpf_mul(aux, aux, aux);

  //aux2 = 4*t
  mpf_mul_ui(aux2,t, 4);

  //pi = aux / aux2
  mpf_div(pi, aux,aux2);
  gmp_printf("Gauss : %.6Ff\n", pi);

  //limpando variaveis
  mpf_clear(pi);
  mpf_clear(a);
  mpf_clear(b);
  mpf_clear(t);
  mpf_clear(p);
  mpf_clear(aNext);
  mpf_clear(bNext);
  mpf_clear(tNext);
  mpf_clear(aux);
  mpf_clear(aux2);
}
