#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
struct Pointeurs {
	 pthread_mutex_t *mainLock;
	 pthread_mutex_t *readLock;
};

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

void *run(struct Pointeurs *pointeurs) {
	printf (pointeurs->mainLock);
/*
	int nbLecteurs = 0;
	while (1) {

		if ((rand() % 2) == 0) {
			pthread_mutex_lock((*pointeurs).readLock);
			nbLecteurs++;
			if(nbLecteurs == 1){
				pthread_mutex_lock(*pointeurs.mainLock);
				lire();
			}
			pthread_mutex_unlock(*pointeurs.readLock);
			nbLecteurs--;

			if(nbLecteurs == 0){
				pthread_mutex_unlock(*pointeurs.mainLock);

			}
			pthread_mutex_unlock(*pointeurs.readLock);

		} else {
			pthread_mutex_lock(*pointeurs.mainLock);
			ecrire();
			pthread_mutex_unlock(*pointeurs.mainLock);
		}
	}
*/
}

int main(){
	pthread_mutex_t read = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t main = PTHREAD_MUTEX_INITIALIZER;

	struct Pointeurs pointeurs;
	pointeurs.mainLock = &main;
	pointeurs.readLock = &read;
	pthread_t t1;

	if(pthread_create(&t1, NULL,  &run, &pointeurs)){
        	fprintf(stderr, "Error creating thread 1\n");
	        return 1;
	}else{
        	printf("TREAD 1\n");
	}

	pthread_t t2;
        if(pthread_create(&t2, NULL,  &run, &pointeurs)){
                fprintf(stderr, "Error creating thread 2\n");
                return 2;
        }else{
                printf("TREAD 2\n");
        }

	pthread_t t3;
        if(pthread_create(&t3, NULL,  &run, &pointeurs)){
                fprintf(stderr, "Error creating thread 3\n");
                return 3;
        }else{
                printf("TREAD 3\n");
        }

	pthread_join(t1,NULL);
}
