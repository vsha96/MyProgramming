#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
struct CommandLine {
	char *word;
	struct CommandLine *next;
};

int main()
{
	
	int c;
	while((c = getchar()) != EOF || c != '\n')
	{
		putchar(c);
	}

			
	
	
	
	
	
	
	
}
