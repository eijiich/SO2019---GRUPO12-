#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

#define iterations 4

void *black_scholes(void *iteration);

//variaveis globais
double S, E, r, sigma, T;
double trials[100000];
int M;

int main(){

	int i = 0;
	double soma= 0;
	double soma2 = 0;
	double variancia, confiancaMin, confiancaMax, stddev, intervaloDeConfianca, media;
	scanf("%lf %lf %lf %lf %lf %d ", &S, &E, &r, &sigma, &T, &M);
	//ID das threads
	pthread_t tid[iterations];

	//criando threads
	//como são 4 threads optou-se criar cada uma manualmente para facilitar o controle das threads
	int i0, i1, i2, i3;
	i0 = 0;
	i1 = 1;
	i2 = 2;
	i3 = 3;
	pthread_create (&tid[i0], NULL, black_scholes, &i0);
	pthread_create (&tid[i1], NULL, black_scholes, &i1);
	pthread_create (&tid[i2], NULL, black_scholes, &i2);
	pthread_create (&tid[i3], NULL, black_scholes, &i3);

	//espera das threads
	for (i = 0; i < iterations ; i++){
		pthread_join (tid[i], NULL);
	}

	//calculo da media
	for(i = 0 ; i < M ; i++){
		soma = soma + trials[i];
	}
	media = soma/(double)M;

	//calculo da variancia e do desvio padrao
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

	return 0;
}

void *black_scholes(void *iteration){
	int *threadNumPtr = (int *)iteration;
	int threadNum = *threadNumPtr;
	int i = 0;
	double t, aux1, aux2, max;
	srand(time(NULL));

	if(threadNum == 0){
		for(i = 0; i < M/4; i++){
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

	}else if(threadNum == 1){
		for(i = M/4; i < M/2; i++){
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

	}else if(threadNum == 2){
		for(i = (M/2); i < 3*M/4; i++){
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

	}else if(threadNum == 3){
		for(i = (3*M/4); i < M; i++){

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
	}
}
