#include <signal.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <unistd.h>

int main(){
	pid_t proc = fork();

	if (proc == -1){
		fprintf(stderr , "fork failed\n");
	}
	if (proc == 0){
		//sleep(5);
		//printf("fini\n");
		char *argu [3] = {"", "-a", NULL};
		execv("/bin/ls",argu);
	}else{
		sleep(2);
                //exit(0);
		printf("bye\n");
		//kill(proc, SIGQUIT);
	}
}
