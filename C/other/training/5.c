#include <stdio.h>
#include <unistd.h>

int main()
{
	int i = 0;
	while(i < 10)
	{ 
		printf("%i sec\n", i);
		sleep(1);
		i++;
	}
	return 0;
}
