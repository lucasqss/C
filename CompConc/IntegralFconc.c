#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#include "timer.h"
#include <math.h>
#include <unistd.h> 


double resultado = 0; //variavel compartilhada entre as threads
pthread_mutex_t mutex; //variavel de lock para exclusao mutua
double a, b, erro;
int n, nthreads;

double func(double x){
    return (cos(exp(-x))*x);
}
void *Integral(void *tid){
    double h = (b-a)/n;
int id = * (int *) tid;
    for(int i=0; i<n; i+=nthreads){
	pthread_mutex_lock(&mutex);
        resultado += h*func((a + h/2) + i*h + id*h);
     	pthread_mutex_unlock(&mutex);
    }
  pthread_exit(NULL);
}
int main(int argc, char *argv[])
{
nthreads = atoi(argv[1]);

    printf("intervalo [a, b]:\n");
    printf("a:\n");
    scanf("%lf", &a);
    printf("b:\n");
    scanf("%lf", &b);
    printf("erro maximo\n");
    scanf("%lf", &erro);
    n = ceil(sqrt(1/(double) erro));


  pthread_t *tid_sistema;
  int t, *tid;
  double ini, fim;


tid_sistema = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
  if(tid_sistema==NULL) {
      printf("--ERRO: malloc()\n"); exit(-1);
  }

  GET_TIME(ini);

  //--inicilaiza o mutex (lock de exclusao mutua)
  pthread_mutex_init(&mutex, NULL);

  for(t=0; t<nthreads; t++) {
    tid = malloc(sizeof(int)); if(tid==NULL) { printf("--ERRO: malloc()\n"); exit(-1); }
    *tid = t;

    if (pthread_create(&tid_sistema[t], NULL, Integral, (void *) tid)) {
      printf("--ERRO: pthread_create()\n"); exit(-1);
    }
  }
  //--espera todas as threads terminarem
  for (t=0; t<nthreads; t++) {
    if (pthread_join(tid_sistema[t], NULL)) {
         printf("--ERRO: pthread_join() \n"); exit(-1); 
    } 
  } 
  pthread_mutex_destroy(&mutex);

  GET_TIME(fim);

  printf("Resultado = %f\n", resultado);
  printf("Tempo = %lf\n", fim-ini);
  pthread_exit(NULL);
}
