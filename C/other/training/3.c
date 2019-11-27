#include <stdio.h>

int main(int argc, char **argv)
{
	while(*argv)
	{
		printf("[%s]",argv[0]);
		argv++;
	}
	printf("\n");
}
