#include <stdio.h>
/*
task 1:
input words (until EOF), it must return number of words 
with length >7 and <=2
*/
int main()
{
	int i = 0;
	int n1 = 0, n2 = 0;
	int c;
	while((c = getchar()) != EOF)
	{
		if ((c != ' ') && (c != '\n'))
		{
			i++;
		} else {
			if (i > 7)
			{
				n1++;
			} else if ((i <= 2) && (i > 0)) {
				n2++;
			}
			i = 0;
		}
		if (c == '\n')
		{
			printf("count of words with length >7 is [%i] and <=2 is [%i]\n", n1, n2);
			n1 = 0; n2 = 0;
		}
	}
	return 0;
}
