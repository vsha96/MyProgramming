#include <stdio.h>
#include <signal.h>
#include <unistd.h>

sig_atomic_t seconds = 5;

void hdl(int n)
{
	signal(n, hdl);
	printf(" n = %i \n", n);
	seconds++;
	alarm(seconds);
	printf(" Im still alive for %i sec\n", seconds);
}

int main()
{
	alarm(seconds);
	signal(SIGINT, hdl);
	printf(" after %i sec I will close myself\n",seconds);
	for(;;)
	{
		sleep(10);
	}
	return 0;
}
