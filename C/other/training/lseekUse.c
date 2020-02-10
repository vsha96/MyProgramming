#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void initmas(int fd)
{
	int i;
	for (i=10;i>0;i--)
	{
		write(fd,&i,sizeof(i));
		printf("%i\n",i);
	}
	printf("\n");

}

int main()
{
	int fd;
	fd = open("test.txt",O_RDWR|O_CREAT|O_TRUNC,0666);
	initmas(fd);
	int size = lseek(fd,0,SEEK_END) / sizeof(int);
	printf("size = %i\n",size);
	
	int i,j;
	int a,b;
	lseek(fd,0,SEEK_SET);
	for (j=size-1;j>0;j--)
	{
		for (i=0;i<j;i++)
		{
			lseek(fd,i*sizeof(int),SEEK_SET);
			read(fd,&a,sizeof(int));
			read(fd,&b,sizeof(int));
			if (a > b)
			{
				lseek(fd,-2*sizeof(int),SEEK_CUR);
				write(fd,&b,sizeof(int));
				write(fd,&a,sizeof(int));
			}
			lseek(fd,-1*sizeof(int),SEEK_CUR);
		}
	}
	lseek(fd,0,SEEK_SET);
	for (i=10;i>0;i--)
	{
		read(fd,&j,sizeof(j));
		printf("%i\n",j);
	}
	printf("\n");

	return 0;
}



