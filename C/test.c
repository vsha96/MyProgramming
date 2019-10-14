#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
struct CommandLine {
	char *word;
	struct CommandLine *next;
};

int main()
{
	/*
	struct CommandLine *line;
	line = malloc(sizeof(*line));
	line->next = NULL;
	line->string = "123456789000\n";
	printf("%s\n",line->string);
	
	int i = 250;
	printf("%c\n",i);	
	*/
	
	/*
	char *p;
	p = "cd";
	
	if (p == "cd")
	{
		printf("FUCK YEAH");
	}
	if (RealStringComp(s1,"cd"))
	{
		//we must do smt
	}
	*/
	
	char **p;
	p = malloc(2*sizeof(**p));
	p[0] = "./shell";
	p[1] = NULL;
	exevp(p[0],p);



}
