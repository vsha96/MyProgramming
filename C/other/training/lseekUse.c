#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void initmas(int fd)
{
	int i;
	for (i=10;i>0;i--)
	{
		write(fd, &i, sizeof(int));
		printf("%d\n", i);
	}
	printf("\n");
}

int main(int c, char **v)
{
	int fd = open(v[1],O_RDWR|O_CREAT,0666);
	initmas(fd);

}






