//Compilar usand o comando: gcc BlackScholes.c -o bs -lm -lgmp
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

void black_scholes(){
	int i, M;
	double S, E, r, sigma, T;
	double t, aux1, aux2;
	double soma = 0;
	double soma2 = 0;
	double variancia, intervaloDeConfianca, confiancaMin, confiancaMax, stddev, max;
	scanf("%lf %lf %lf %lf %lf %d ", &S, &E, &r, &sigma, &T, &M);
	double trials[M], media;
	srand(time(NULL));

	for(i = 0; i < M; i++){
		//calculando t
		aux1 = T*(r - 0.5*sigma*sigma);
		aux2 = sigma*sqrt(T)*((double)rand()/(double)RAND_MAX);
		aux1 = aux1+aux2;
		t = S*pow(M_E, aux1);

		//maximo entre 0 e t-E
		if(t-E > 0){
			max = t-E;
		}else{
			max = 0;
		}

		//calculo do trials
		aux2 = pow(M_E, -r*T);
		trials[i] = aux2*max;
	}

	//calculo da media
	for(i = 0 ; i < M ; i++){
		soma = soma + trials[i];
	}
	media = soma/(double)M;

	//calculo da variancia e desvio padrao
	for(i = 0 ; i < M; i++){
		soma2 = soma2 + ((trials[i]-media)*(trials[i]-media));
	}
	variancia = soma2/(double)M;
	stddev = sqrt(variancia);

	//calculo do intervalo de confianca
	intervaloDeConfianca = (1.96*stddev)/(double)(sqrt(M));
	confiancaMin = media - intervaloDeConfianca;
	confiancaMax = media + intervaloDeConfianca;


	//imprimindo o intervalo de confianca
	printf("S        %0.lf\n",S);
	printf("E        %0.lf\n",E);
	printf("r        %0.lf\n",r);
	printf("sigma    %0.lf\n",sigma);
	printf("T        %0.lf\n",T);
	printf("M        %d\n",M);
	printf("Confidence interval: (%lf,%lf)\n", confiancaMin,confiancaMax);

}

int main(){
	black_scholes();
	return 0;
}
