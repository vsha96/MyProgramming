#include <unistd.h>
#include <stdio.h>

int main() {
	printf("create char[]\n");
	char *line = new char[10];
	printf("delete char[]\n");
	delete[] line;
}
