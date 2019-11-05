#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
struct CommandLine {
	char *word;
	struct CommandLine *next;
};

void changei(int *i)
{
	*i = 9;
}

int main()
{
	
	int i = 1;
	changei(&i);
	printf("%i\n",i);
	
	
	
	
}
