#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>

void sigproc(int);
void launch_terminal();
void create_shared_memory();
void clean_memory();

char* shm;
int shmid;
key_t key = 2000;

int
main()
{	
        pid_t wpid;

        signal(SIGUSR1, sigproc);
	create_shared_memory();
        while((wpid = wait(NULL)) > 0);
	clean_memory();
	return 0;
} 
void
launch_terminal()
{
        pid_t pid;
        if ((pid=fork())==0) { 
                execv("/home/thibault/st/st",NULL);
        }
}
void
sigproc(int dummy)
{ 		 
        signal(SIGUSR1, sigproc); 
        launch_terminal() ;
}

void
clean_memory()
{
	if((shmid = shmget(key, sizeof(char),0666)) < 0){
		perror("shmget ain't working bb, therefore you ain't got shit to clean");
	}
	shmctl(shmid, IPC_RMID, NULL);
	printf("clean af\n");
}

void
create_shared_memory()
{
	if((shmid = shmget(key, sizeof(char), IPC_CREAT | 0666 | IPC_EXCL)) < 0){
		perror("can't create shared memory");
		exit(1);
	}
	shm = shmat(shmid, NULL, 0);
}
