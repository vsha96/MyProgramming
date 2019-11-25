#include <stdio.h>

int sumx(int x, int y)
{
	return x+y;
}

int main()
{
	int x, y;
	scanf("%i %i", &x, &y);
	/*and now we'll have pointer to function*/
	typedef int (*psumx)(int, int);
	psumx p;
	p = sumx;
	printf("%i \n", p(x,y));

}
