#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

sig_atomic_t count;
const char msg[] = " PRESS IT AGAIN, I LIKE IT\n";

void hdl(int n)
{
	signal(n, hdl);
	count++;
	if (count>10)
		exit(0);
	write(1, msg, sizeof(msg));
}

int main()
{
	signal(SIGINT, hdl);

	for(;;)
		sleep(1);
	return 0;

}
