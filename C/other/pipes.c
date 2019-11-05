#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(){
	
	char **cline, **cline1;
	int pid;

	cline = malloc((2+1)*sizeof(*cline));
	cline[0] = "echo";
	cline[1] = "hello";
	cline[2] = NULL;
	
	cline1 = malloc((1+1)*sizeof(*cline1));
	cline1[0] = "./streamtest";
	cline1[1] = NULL;
	
	int fd[2];
	pipe(fd);

	

	pid = fork();
	if (pid == 0)
	{
	dup2(fd[0],0); /*main theme!*/
	dup2(1,fd[1]);
	printf("start [%s]\n",cline1[0]);
	execvp(cline1[0],cline1);
	perror(cline1[0]);
	fflush(stderr);
	exit(1);
	}
	
	
	close(fd[0]);
	write(fd[1],"fuck you",8);
	
	

}
