#include <stdio.h>
#include <stdlib.h>

struct nums {
	long long int number;
	int count;
	struct nums *next;
};

void NumsPrint(const struct nums *n)
{
	if (n != NULL)
	{
		NumsPrint(n->next);
		printf("[%lli][count:%i]\n", n->number, n->count);
	}
}

struct nums *NumsAdd(struct nums *n, long long int c)
{
	struct nums *p;
	p = n;
	while(p != NULL)
	{
		if (p->number == c)
		{
			p->count++;
			return n;
		}
		p = p->next;
	}
	/* I didnt find element, create new one */
	p = malloc(sizeof(*p));
	p->number = c;
	p->count = 1;
	p->next = n;
	n = p;
	return n;
}

int main()
{
	long long int c;
	struct nums *n;
	n = NULL;
	int f=0;
	printf("enter numbers and end with EOF\n");
	while (f != -1)
	{
		f = scanf("%lli",&c);
		if (f != -1)
		{
			n = NumsAdd(n,c);
		}
	}
	NumsPrint(n);
	return 0;
}
