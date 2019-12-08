#include <stdio.h>
#include <unistd.h>
int main()
{
	int pid1, pid2, p;
	int fd1[2], fd2[2];
	pipe(fd1); pipe(fd2);
	
	/* 1st process */
	pid1 = fork();
	if (pid1 == 0)
	{
		close(fd1[1]);
		close(fd2[0]);
		p = getpid(); /* catch our pid */
		write(fd2[1],&p,sizeof(int));
	}
	/* 2d process */
	pid2 = fork();
	if (pid1) /* i suppose 1st process is still running*/
		if (pid2 == 0)
		{
			close(fd1[0]);
			close(fd2[1]);
			p = getpid(); /* catch our pid*/
			write(fd1[1],&p,sizeof(int));
		}
	
	close(fd1[0]);
	close(fd1[1]);
	close(fd2[0]);
	close(fd2[1]);
}
