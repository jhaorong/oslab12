#include <semaphore.h>

#include <pthread.h>

#include <stdio.h>

#include <unistd.h>

int count=0;

void *inc(void);

void *dec(void);

/*int sem_init(sem_t *sem,int pshared,unsigned value);
int sem_destroy(sem_t *sem);
int sem_getvalue(sem_t *sem,int *value);
int sem_post(sem_t *sem);
int sem_wait(sem_t *sem);*/
sem_t mutex;
int main(void){

  	int i=0;
  	sem_t sem;
	sem_init(&mutex,0,1);
  	pthread_t id[2]; 
  	pthread_create(&id[0],NULL,(void*)dec,NULL);
	pthread_create(&id[1],NULL,(void*)inc,NULL);
	for(i=0;i<2;i++){
  		pthread_join(id[i],NULL); 
  	}
	sem_destroy(&mutex);

  	printf("\noutput is %d\n",count);

  	pthread_exit(NULL);
	return 0;
}

void *inc(void){

  int i=0;
  sem_wait(&mutex);
  for(i=0;i<25000000;i++){
  	count++;
  }
  sem_post(&mutex);
  pthread_exit(NULL);

}

void *dec(void){

  int i=0;
  sem_wait(&mutex);
  for(i=0;i<25000000;i++){
	count--;
  }
  sem_post(&mutex);
  pthread_exit(NULL);

}
