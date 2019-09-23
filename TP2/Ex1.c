#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>


void lire() {
	printf("lire debut\n");
	usleep(rand() % 500000);
	printf("lire fin\n");
}

void ecrire() {
	printf("ecrire debut\n");
	usleep(rand() % 500000);
	printf("ecrire fin\n");
}

void *run(void *main) {
	int nbLecteurs = 0;
	pthread_mutex_t lecture = PTHREAD_MUTEX_INITIALIZER;
	while (1) {

		if ((rand() % 2) == 0) {
			pthread_mutex_lock(lecture);
			nbLecteurs++;
			if(nbLecteurs == 1){
				pthread_mutex_lock(main[0]);
				lire();
			}
			pthread_mutex_unlock(lecture);
			nbLecteurs--;

			if(nbLecteurs == 0){
				pthread_mutex_unlock(main[0]);

			}
			pthread_mutex_unlock(lecture);

		} else {
			pthread_mutex_lock(main[0]);
			ecrire();
			pthread_mutex_unlock(main[0]);
		}
	}
}

int main(){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;


	pthread_t t1;
	if(pthread_create(&t1, NULL,  run, &mutex)){
        	fprintf(stderr, "Error creating thread 1\n");
	        return 1;
	}else{
        	printf("TREAD 1\n");
	}

	pthread_t t2;
        if(pthread_create(&t2, NULL,  run, &mutex)){
                fprintf(stderr, "Error creating thread 2\n");
                return 2;
        }else{
                printf("TREAD 2\n");
        }

	pthread_t t3;
        if(pthread_create(&t3, NULL,  run, &mutex)){
                fprintf(stderr, "Error creating thread 3\n");
                return 3;
        }else{
                printf("TREAD 3\n");
        }

	pthread_join(t1,NULL);
}
