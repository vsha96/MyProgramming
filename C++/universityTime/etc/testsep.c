#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void packline_print(char **packline)
{
    int i=0; 
    printf("packline_print:");
    while(packline[i]) {
        printf("[%s]", packline[i]);
        i++; 
    }    
    printf("\n");
}

int is_it_sep(int c, char *sep)
{
	int i;
	for (i=0; sep[i]; i++) {
		if (c == sep[i]) {
			return 1;
		}
	}
	return 0;
}

int word_count(const char *line, char *sep)
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

char **session_handle_packline(const char *line, char *sep)
{
	if (line == NULL) return NULL;
    char **packline;
	char *temp; 
    int i, j, f, len, size = word_count(line, sep);
	/*copy of line*/
    for(len=0; line[len]; len++);
	temp = malloc((len+1)*sizeof(char));
	for(i=0; i<len+1; i++) temp[i] = line[i];
		printf("[%s]\n", temp);
		fflush(stdout);
	packline = malloc((size+1)*sizeof(char*));
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

int main(int argc, char **argv)
{
	char *sep = " :";
	char **packline;
	//printf("%i\n", word_count(argv[1], sep));
        //printf("[%s]\n", argv[1]);
	packline = session_handle_packline(argv[1], sep);
	packline_print(packline);



}
