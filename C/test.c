#include <stdio.h>
#include <stdlib.h>
struct CommandWord {
	struct string *string;
	//int sizeOfString; //it may be useful for new procedures
	struct CommandWord *next;
};
enum {
	chunk_size = 8
};
struct string {
	int x[chunk_size]; //elements of chunk
	struct string *next;
};

struct string *StringFill()
{
	struct string *str,*temp; //we use it when we create another buffer
	int i=0;
	int c; //our char with EOF
	str = malloc(sizeof(*str));
	temp = str;
	while((c = getchar()) != EOF)
	{
		if (i == chunk_size)
		{
			temp->next=malloc(sizeof(*str));
			temp=temp->next;
			i = 0;
		}
		temp->x[i]=c;
		i++;
	}
	//if (c == EOF)
	if (i != chunk_size)
	{
		temp->x[i]=EOF;
	}
	temp->next=NULL;
	
	return str;
}

void StringPrint(const struct string *str)
{
	const struct string *temp; //what it does?
	int i=0;
	int c; //our char with EOF
	temp = str;
	while(temp!=NULL)
	{
		while((c=(temp->x[i]))!=EOF) 
		{
			putchar(c);
			if (i==chunk_size)
			{
				i=0;
				temp=temp->next;
				c=EOF;
			} else {
				i++;
			}
		}
		
		temp=temp->next;
	}
	
}

void StringFree(struct string *str) //we need test for this thing
{
	if (str != NULL)
	{
		StringFree(str->next);
		free(str);
	}
}

/*we need some procedures to separate string into words*/

int main()
{
	struct string *str;
	printf("Input string:\n");
	str = StringFill();
	printf("Your string:\n");
	StringPrint(str);
	
	return 0;
}