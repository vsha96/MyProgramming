#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "packline.hpp"

int is_it_sep(int c, const char *sep)
{   
    int i;
    for (i=0; sep[i]; i++) {
        if (c == sep[i]) {
            return 1;
        }
    }
    return 0;
}

int word_count(const char *line, const char *sep)
{
    if (line == NULL) return 0;
    int i,f=0,len, count=0;
    for(len=0; line[len]; len++);
    for (i=0;i<len;i++) {
        if (!is_it_sep(line[i], sep)) {
            f = 1;
        } else {
            if (f == 1) {
                count++;
                f = 0;
            }
        }
    }
    if (f == 1) { count++; }
    return count;
}

void packline_print(char **packline)
{
	if (packline) {
		printf("packline_print:");
		for (int i=0; packline[i]; i++) {
			printf("[%s]", packline[i]);
		}
		printf("\n");
	} else {
		printf("packline_print:NULL\n");
	}
}

int packline_size(const char **packline)
{
	int size;
	for(size=0;packline[size];size++);
	return size;
}

void packline_free(const char **packline)
{
	int size = packline_size(packline);
	//printf("PACKLINE SIZE %i\n", size);
	for(int i=0; i<size; i++)
		delete[] packline[i];
}

char **make_packline(const char *line, const char *sep)
{
    if (line == NULL) return NULL;
    char **packline;
    char *temp;
    int i, j, f, len, size = word_count(line, sep);
    /*copy of line*/
    for(len=0; line[len]; len++);
	temp = new char[len+1]; //TODO
	/* TODO
			 ^
		here | we have some leaks if first chars are separators
	*/
    for(i=0; i<len+1; i++) temp[i] = line[i];
	packline = new char*[size+1];

    packline[size] = NULL;
    j = 0; f = 0;
    for (i=0;i<len;i++) {
        if (!is_it_sep(line[i], sep)) {
            if (f == 0) {
                packline[j] = &(temp[i]);
                j++;
            }
            f = 1;
        } else {
            temp[i] = 0;
            if (f) {
                f = 0;
            }
        }
    }
	return packline;
}

