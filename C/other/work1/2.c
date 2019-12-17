#include <stdio.h>

int size(char *p)
{
	int i;
	for(i=0;p[i];i++) {}
	return i;
}

int main(int argc, char **argv)
{
	int max=0, new=0;
	char *p;
	argv++;

	max = new;
	p = argv[0];

	while(*argv)
	{
		new = size(argv[0]);
		if (max < new)
		{
			max = new;
			p = argv[0];
		}
		argv++;
	}
	if (argc == 1)
	{
		printf("you must put some words in arguments\n");
	}
	if (argc > 1)
	{
		printf("argument of your string with max length [%i]%s\n",max,p);
	}
	return 0;
}
