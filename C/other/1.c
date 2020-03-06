#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int fd[2];
	pipe(fd);
	char x[]="10";
	int pid = fork();

	if (pid) {
		puts(x+1);
		write(fd[1],x,1);
		wait(NULL);
	} else {
		write(fd[1], &x[1], 1);
		read(fd[0], x, 1);
		read(fd[0], x+1, 1);
	}
	
	puts(x);
	return 0;
}
