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
		/*while((c=(temp->x[i]))!=EOF) 
		{
			putchar(c);
			if (i==chunk_size-1)
			{
				i=0;
				//temp=temp->next;
				goto nextchunk;
			} else {
				i++;
			}
		}
		nextchunk:;
		temp=temp->next;
		*/
		//===new version===
		while((c=(temp->x[i]))!=EOF && (i<chunk_size)) 
		{
			putchar(c);
			i++;
		}
		temp=temp->next;
		i=0;
		//===/new version===
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

int StringSize(const struct string *str)
{
	int n=0, i=0,c;
	const struct string *temp;
	temp = str;
	while(temp!=NULL)
	{
		while((c=(temp->x[i]))!=EOF && (i<chunk_size)) 
		{
			n++; i++;
		}
		temp=temp->next;
		i=0;
	}
	return n;
}

/*we need some procedures to separate string into words*/
/*
struct string *StringMakeNewFrom(const struct string *str,int s1,int s2)
{
	const struct string *temp;
	struct string *newstr;
	int i=0,j=0;
	//move to our 1st separator
	for (j=0;j<=s1;j++)
	{
		return 0;
	}
	
	
	return newstr;
}
*/

void StringSeparate(const struct string *str)
{
	
}

int main()
{
	struct string *str;
	printf("Input string:\n");
	str = StringFill();
	
	printf("Your string:\n");
	StringPrint(str);
	//printf("\n");
	
	/*
	printf("Size of your string:\n");
	printf("%i\n",StringSize(str));
	*/
	StringFree(str);
	str = NULL;
	printf("Your string after delete:\n");
	StringPrint(str);
	
	return 0;
}