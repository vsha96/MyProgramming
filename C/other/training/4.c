#include <stdio.h>
#include <signal.h>
#include <unistd.h>

const char msg[] = " Press it again! \n";
sig_atomic_t count = 0;

void hdl(int n)
{
	signal(n, hdl);
	printf(" %i %s", count, msg);
	count++;
}

int main()
{
	signal(SIGINT, hdl);
	while(count<5)
		sleep(1);
}
