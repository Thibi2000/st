#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdio.h>
int shmid;
key_t key = 2000;
int
main()
{	
	if((shmid = shmget(key, sizeof(char),0666)) < 0){
		perror("shmget ain't working bb, therefore you ain't got shit to clean");
	}else{
		printf("Cleaning memory\n");
		shmctl(shmid, IPC_RMID, NULL);
	}
	return 0;
}
