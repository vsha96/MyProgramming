#include <unistd.h>
#include <stdio.h>

void say(char *s) {
	int i;
	for (i=0; s[i]; i++);
	write(1, s, i);
}

int main() {
	printf("hello, this is wrote in C++\n");

	double f = 30.4;
	for (int i=0; i<20; i++) {
		printf("kek [%c]\n", (char)(f+i));
	}
	char cmdt[] = "tessdasdasdasdtasdjasdnas\n";
	write(1, cmdt, sizeof(cmdt));
	say(cmdt);
}
