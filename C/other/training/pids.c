#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("PID A = %i PPID A = %i\n", getpid(), getppid());
	if (fork() == 0)
	{
		printf("PID B = %i; PPID B = %i\n", getpid(), getppid());	
		if (fork() == 0)
		{
			printf("PID C = %i; PPID C = %i\n", getpid(), getppid());	
			return 0;
		}
		return 0;
	}
}
