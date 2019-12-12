#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int word_count(char *line)
{
    int size = 0;
    char *word, *sep = " ";
    for(word=strtok(line,sep);
        word;
        word=strtok(NULL,sep))
        size++;
    return size;
}

int main()
{
	char test[80];
	char *sep = " ";
	char *word;
	
	strcpy(test, "This     is the   string   tokenizer");

	printf("%i\n", word_count(test));
    
	 for (word = strtok(test, sep);
          word;
          word = strtok(NULL, sep))
     {
            printf("So far we're at [%s]\n", word);
     }


}
