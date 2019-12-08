#include <stdio.h>
#include <unistd.h>
int main()
{
	int pid1, pid2, p;
	int fd1[2], fd2[2];
	pipe(fd1); pipe(fd2);
	
	pid1 = fork();
	if (pid1 == 0)
	{
		close(fd1[1]);
		close(fd2[0]);
		
		p = getpid();
		write(fd2[1],&p,sizeof(int));
		
	}
	
	if (pid1)
	{
		pid2 = fork();
		if (pid2 == 0)
		{
			close(fd1[0]);
			close(fd2[1]);

			p = getpid();
			write(fd1[1],&p,sizeof(int));
			read(fd2[0],&p,sizeof(int));
			printf("%i\n",getpid());
			printf("I cathed p = %i\n",p);
			
		}
	}
	sleep(2);
	if (pid1 == 0)
	{
		printf("%i\n",getpid());
		read(fd1[0],&p,sizeof(int));
		printf("I cathed p = %i\n",p);
	}
	
	close(fd1[0]);
	close(fd1[1]);
	close(fd2[0]);
	close(fd2[1]);
}
