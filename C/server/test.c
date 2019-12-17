#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int word_count(char *line)
{
    int size = 0;
	char test[128], *word, *sep = " ";
	strcpy(test, line);
	for (word = strtok(test, sep);
		word;
		word = strtok(NULL, sep))
     {
		 size++;
     }
	 return size;

}

void packline_print(char **packline)
{
    char **temp = packline;
    while(temp[0]) {
        printf("[%s]\n", temp[0]);
        temp++;
    }
}

char **handle_packline(const char *line)
{
    char **packline;
    char temp[128], *word, *sep = " ";
    int i = 0, size;
    size = word_count(line);
    packline = malloc((size+1)*sizeof(char*));
    packline[size] = NULL;

	strcpy(temp, line);
    for (word = strtok(temp, sep);
		word;
		word = strtok(NULL, sep))
     {
		 packline[i] = word;
		 i++;
     }
    /* DEBUG */ packline_print(packline);
    return packline;
}

int main()
{
	handle_packline("hello   bil  you   smoothy");
	
	
}





