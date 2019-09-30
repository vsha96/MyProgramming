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

struct string *StringMakeNewFrom(struct string *str,int s1,int s2)
{
	struct string *temp, *newstr, *newtemp;
	int i,j,l,m;
	temp = str;
	s2 = s2 - s1; //pass few lines we'll make another base
//printf("\n%i\n",s2);
	//move to our 1st separator
	for (i=0;i<(s1/chunk_size);i++)
	{
		temp = temp->next;
	}
	s1 = s1 % chunk_size; //we made another base
//printf("\n%i\n",s1);
	s2 = s1 + s2; //s2 points in new base
//printf("\n%i\n",s2);
	newstr = malloc(sizeof(*newstr));
	newtemp = newstr;
	//copy every chunk we needed
	for (i=0;i<=(s2/chunk_size);i++)
	{
		//if first chunk
		if (i==0)
		{
			if (s2/chunk_size!=0) //if 2nd separator not in our chunk
			{
				for (j=s1-1;j<chunk_size;j++)
				{
					newtemp->x[j-s1+1]=temp->x[j];
				}
			} else { // 2nd separator in our chunk, we need ending
				for (j=s1-1;j<s2;j++)
				{
					newtemp->x[j-s1+1]=temp->x[j];
				}
				//ending
				if (j != chunk_size)
				{
					newtemp->x[j-s1+1]=EOF;
				}
				newtemp->next=NULL;
			}
		}
		//if last chunk
		
		//else
	}
	
	//newtemp->next=NULL;
	
	return newstr;
}


void StringSeparate(struct string *str)
{
	
}

int main()
{
	struct string *str,*str1;
	printf("Input string:\n");
	str = StringFill();
	
	printf("Your string:\n");
	StringPrint(str);
	//printf("\n");
	printf("Size of your string:\n");
	printf("%i\n",StringSize(str));
	/*
	StringFree(str);
	str = NULL;
	printf("Your string after delete:\n");
	StringPrint(str);
	*/
	str1 = StringMakeNewFrom(str,1,8);
	printf("Ive made another string\n");
	StringPrint(str1);
	printf("\n");
	
	printf("Which size is\n%i\n",StringSize(str1));
	
	
	return 0;
}