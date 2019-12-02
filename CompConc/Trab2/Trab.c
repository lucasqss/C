#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "pthread.h"
#include "semaphore.h"

pthread_mutex_t lock;           /* lock para terminar as threads */
sem_t mutex;
sem_t resource;                 /* semaforos */
int rc = 0;
int wc = 0;                     /* rc = reader count, wc = writer count */
int nreaders, nwriters;         /* inicializa quantidade de threads leitoras e escritoras */
int reads, writes;              /* quantidade de leituras/escritas por realizadas pelas threads */
int var;                        /* variavel compartilhada das leituras/escritas */
//FILE * fExit;

void *Leitura (void *threadid) {
    int *tid = (int*) threadid;
    //char nome[sizeof("%02d.txt")];
    //char saida[25];
    //FILE * fPtr;
    printf("inicializa leitor %d \n", *tid);
    //sprintf(nome, "%02d.txt", *tid);
    //fPtr = fopen(nome, "w");
    while (reads >= 0) {
        sem_wait(&mutex);
        if((wc > 0)  || (rc == 0)){
            sem_post(&mutex);
            sem_wait(&resource);
            sem_wait(&mutex);
        }
        rc += 1;
        reads -=1;
        if (reads>=0) {
            sem_post(&mutex);
            /* inicia leitura */
            printf("Leitor : %d esta executando...\n", *tid);
            //sprintf(saida, "Leitura da thread %d, %d", *tid, var);

            //fputs(saida, fExit);
            //fputs(var, fPtr);
            /* termina leitura */
            sem_wait(&mutex);
            rc -= 1;
            if (rc==0) {
                sem_post(&resource);
            }
            sem_post(&mutex);
            }
        else{
          sem_post(&mutex);
          sem_post(&resource);
        }
    }
    //fclose(fPtr);
    return 0;
}

void *Escrita (void *threadid) {
    int *tid = (int*) threadid;
    //char saida[25];
    printf("inicializa escritor %d \n", *tid);

    while (writes >= 0) {
        sem_wait(&mutex);
        wc += 1;
        writes -= 1;
        if (writes>=0){
            sem_post(&mutex);
            sem_wait(&resource);
            /* inicia escrita */
            printf("Escritor : %d esta executando...\n", *tid);
            var = *tid;
            //sprintf(saida, "Escrita da thread %d, %d", *tid, var);
            //fputs(saida, fExit);
            /* termina escrita */
            sem_wait(&mutex);
            wc -= 1;
            sem_post(&mutex);
            sem_post(&resource);
        }
        else{
          sem_post(&mutex);
          sem_post(&resource);
        }
    }
    return 0;
}
//funcao principal
int main(int argc, char *argv[]) {
  pthread_t *w, *r;
  int *id;
  sem_init(&mutex, 0, 1);
  sem_init(&resource, 0, 1);
  printf("%s %s %s %s %s \n", argv[1], argv[2], argv[3], argv[4], argv[5]);
  nreaders = (int)atoi(argv[1]);
  nwriters = (int)atoi(argv[2]);
  reads = (int)atoi(argv[3]);
  writes = (int)atoi(argv[4]);
  //fExit = fopen(argv[5], "w");
  w = malloc(nwriters * sizeof(pthread_t));if (w == NULL) {printf("malloc failed\n");return -1;}
  r = malloc(nreaders * sizeof(pthread_t));if (r == NULL) {printf("malloc failed\n");return -1;}

  for (size_t i = 0; i < nreaders; i++) {
    //aloca espaco para o identificar da thread
    if ((id = malloc(sizeof(int))) == NULL) {
       pthread_exit(NULL); return 1;
    }
    *id=i;
    //Cria a thread
    if (pthread_create(&r[i], NULL, Leitura, (void *)id)) {
      printf("--ERRO: pthread_create()\n"); exit(-1);
    }
  }
  for (size_t i = 0; i < nwriters; i++) {
    //aloca espaco para o identificar da thread
    if ((id = malloc(sizeof(int))) == NULL) {
       pthread_exit(NULL); return 1;
    }
    *id=i;
    //Cria a thread
    if (pthread_create(&w[i], NULL, Escrita, (void *)id)) {
      printf("--ERRO: pthread_create()\n"); exit(-1);
    }
  }
  //espera todas as threads terminarem
  for (size_t i = 0; i < nwriters; i++) {
    if (pthread_join(w[i], NULL)) {
        printf("--ERRO: pthread_join() \n"); exit(-1);
    }
  }
  for (size_t i = 0; i < nreaders; i++) {
    if (pthread_join(r[i], NULL)) {
        printf("--ERRO: pthread_join() \n"); exit(-1);
    }
  }
  pthread_exit(NULL);
  return 0;
}
