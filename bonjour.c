#include <signal.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <unistd.h>
#include <pthread.h>

void *run(){
	for(int c=0; c<10; c++){
		printf("bonjour\n");
		sleep(1);
	}
}

int main(){
	pthread_t run_thread;
	if(pthread_create(&run_thread, NULL, run, NULL)){
		fprintf(stderr, "Error creating thread\n");
	}
	if(pthread_join(run_thread, NULL)) {
		fprintf(stderr, "Error joining thread\n");
	}
}
