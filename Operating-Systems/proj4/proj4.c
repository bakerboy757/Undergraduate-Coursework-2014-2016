#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define BUFFER_SIZE 5
#define MAX 10000

typedef int buffer_item;
buffer_item buffer[BUFFER_SIZE];
int buf_count = 0;
int out = 0;
int in = 0;
int flag = 0;
pthread_mutex_t mutex;
sem_t empty, full;

void *producer(void *param);
void *consumer(void *param);
int insert_item(buffer_item);
int remove_item(buffer_item*);
void sig_handler(int sig);

int main(int argc, char *argv[]){

  unsigned int TIME, PROD, CONS;
  unsigned int i;
  int rc;
  if(argc != 4){
    perror("Invalid number of arguments");
    exit(EXIT_FAILURE);
  }
  if(signal(SIGINT, sig_handler)){
    perror("signal");
    exit(EXIT_FAILURE);
  }
  
  TIME = atoi(argv[1]);
  PROD = atoi(argv[2]);
  CONS = atoi(argv[3]);
  
  //initialize buffer
  memset(buffer, 0, BUFFER_SIZE * sizeof(buffer[0]));

  //init our mutex and semaphores
  if(pthread_mutex_init(&mutex, NULL)){
    perror("mutex init");
    exit(EXIT_FAILURE);
  }
  if(sem_init(&empty, 0, BUFFER_SIZE)){
    perror("sem_init empty");
    exit(EXIT_FAILURE);
  }
  if(sem_init(&full, 0, 0)){
    perror("sem_init full");
    exit(EXIT_FAILURE);
  }

  //setup threads
  pthread_t prod_threads[PROD];
  pthread_t cons_threads[CONS];
  //seed random number generator 
  srand(time(NULL));
  for(i = 0; i < PROD; i++){
     if(pthread_create(&prod_threads[i], NULL, producer, (void *) &TIME)){
       perror("pthread_create");
       exit(EXIT_FAILURE);
     }
  }
  for(i = 0; i < CONS; i++){
     if(pthread_create(&cons_threads[i], NULL, consumer, (void *) &TIME)){
       perror("pthread_create");
       exit(EXIT_FAILURE);
     }
  }
  for(i = 0; i < PROD; i++){
     rc = pthread_join(prod_threads[i], NULL);
     if(rc){
       printf("Error; return code from pthread_join is %d\n", rc);
       exit(EXIT_FAILURE);
     }
  }
  for(i = 0; i < CONS; i++){
     pthread_join(cons_threads[i], NULL);
     if(rc){
       printf("Error; return code from pthread_join is %d\n", rc);
       exit(EXIT_FAILURE);
     }
  }
 // printf("main\n");
  sleep(TIME);
  pthread_exit(NULL);

}
void sig_handler(int sig){
  if(sig == SIGINT)
    flag = 1;
}
void *producer(void *param) {
  buffer_item item;
  int time = *((int*)  param);
  while (1) {
     // sleep for a random period of time 
     sleep(rand()%time);
     // generate a random number 
     item = rand();
     if(flag){
   //    printf("prod\n");

       pthread_exit(NULL);
     }
     //gain locks before crit section
     if(sem_wait(&empty)){
       perror("lock empty sem prod");
       exit(EXIT_FAILURE);
     }
     if(pthread_mutex_lock(&mutex)){
       perror("mutex lock prod");
       exit(EXIT_FAILURE);
     }
     //crit section
     if (insert_item(item))
       printf("report error condition prod");
     //release lock
     if(pthread_mutex_unlock(&mutex)){
       perror("mutex unlock prod");
       exit(EXIT_FAILURE);
     }
     //increment full semaphore
     if(sem_post(&full)){
       perror("incr full sem prod");
       exit(EXIT_FAILURE);
     }
  }
}
void *consumer(void *param) {
  buffer_item item;
  int time = *((int*) param);
  while (1) {
     sleep(rand() % time);
     if(flag){
     //  printf("cons\n");

       pthread_exit(NULL);  
     }

     if(sem_wait(&full)){
       perror("lock full sem cons");
       exit(EXIT_FAILURE);
     }
     if(pthread_mutex_lock(&mutex)){
       perror("mutex lock cons");
       exit(EXIT_FAILURE);
     }

     if (remove_item(&item))
       printf("report error condition cons");

     if(pthread_mutex_unlock(&mutex)){
       perror("mutex unlock cons");
       exit(EXIT_FAILURE);
     }
     //increment empty semaphore
     if(sem_post(&empty)){
       perror("incr empty sem cons");
       exit(EXIT_FAILURE);
     }

  }
}

int insert_item(buffer_item item){
  if(buf_count >= BUFFER_SIZE)
    return -1;
  buffer[in] = item;
  printf("producer produced %d\n",item);

  in = (in+1)%BUFFER_SIZE;
  buf_count++;
  return 0;
}
int remove_item(buffer_item *item){
  if(buf_count <= 0)
    return -1;
  *item = buffer[out];
  printf("consumer consumed %d\n",*item);

  out = (out+1)%BUFFER_SIZE;
  buf_count--;
  return 0;


}

