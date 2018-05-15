#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void sigproc(int);
void launch_terminal();

int
main()
{	
        pid_t wpid;
        signal(SIGUSR1, sigproc); 
        launch_terminal();
        while((wpid = wait(NULL)) > 0);
	return 0;
} 
void launch_terminal()
{
        pid_t pid;
        if ((pid=fork())==0) { 
                execv("/home/thibault/st/st",NULL);
                exit(127); 
        }
}
void sigproc(int dummy)
{ 		 
        signal(SIGUSR1, sigproc); 
        launch_terminal() ;
}

