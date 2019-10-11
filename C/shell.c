#include <stdio.h>
#include <stdlib.h>
struct CommandLine {
	struct String *word; //CHANGES FOR 2d STEP
	struct CommandLine *next;
};
enum {
	chunk_size = 8
};
struct String {
	int x[chunk_size]; //elements of chunk
	struct String *next;
};

struct String *StringFill()
{
	struct String *str,*temp; //we use it when we create another buffer
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

void StringPrint(const struct String *str)
{
	const struct String *temp; //what it does?
	int i=0;
	int c; //our char with EOF
	temp = str;
	while(temp!=NULL)
	{
		while((c=(temp->x[i]))!=EOF && (i<chunk_size)) 
		{
			putchar(c);
			i++;
		}
		temp=temp->next;
		i=0;
	}
}

void StringFree(struct String *str) //we need test for this thing
{
	if (str != NULL)
	{
		StringFree(str->next);
		free(str);
	}
}

int StringSize(const struct String *str)
{
	int n=0, i=0,c;
	const struct String *temp;
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
struct String *StringMakeNewFrom(struct String *str,int s1,int s2)
{
	struct String *temp, *newstr, *newtemp;
	int i,j,l;
	temp = str;
	s1 -= 1; s2 -= 1; //shift
	s2 = s2 - s1; //pass few lines we'll make another base
	//move to our 1st separator
	for (i=0;i<(s1/chunk_size);i++)
	{
		temp = temp->next;
	}
	s1 = s1 % chunk_size; //we made another base
	s2 = s1 + s2; //s2 points in new base
	newstr = malloc(sizeof(*newstr));
	newtemp = newstr;
	for (j=s1;j<=s2;j++)
	{
		l = j-s1; //index in chunk of newstr
		if ( (j != 0) && ((j)%chunk_size) == 0)
		{
			temp=temp->next;
		}
		if ( (l != 0) && ((l)%chunk_size) == 0)
		{
			newtemp->next=malloc(sizeof(*newstr));
			newtemp=newtemp->next;
		}
		newtemp->x[(l%chunk_size)]=temp->x[(j%chunk_size)];
	}
	l = j-s1; //index in chunk of newstr
	//ending
	if ( ((l)%chunk_size) != 0 )
	{
		newtemp->x[(l%chunk_size)]=EOF;
	}
	newtemp->next=NULL;
	return newstr;
}

//CHANGES FOR 2d STEP
char *StringMakeRealStringFrom(struct String *str, int s1, int s2)
{
	return 0;	
}

char StringCharAt(struct String *str, int i)
{
	i = i - 1;
	int j;
	for (j=0;j<(i/chunk_size);j++)
	{
		str=str->next;
	}
	return str->x[i%chunk_size];
}

//!!!CHANGES FOR 2d STEP
void CommandLinePrint(const struct CommandLine *line)
{
	while (line!=NULL)
	{
		StringPrint(line->word);
		//printf("\t\t\t size:%i",StringSize(line->word));
		printf("\n");
		line=line->next;
	}
}

//CHANGES FOR 2d STEP
void CommandLineFree(struct CommandLine *line)
{
	if (line != NULL)
	{
		CommandLineFree(line->next);
		StringFree(line->word);
		free(line);
	}
}

//CHANGES 2d STEP
struct CommandLine *CommandLineAddWord(struct CommandLine *line, struct String *str, int s1, int s2)
{ //we can use recursion, it will be more compact code here with it
	struct CommandLine *linetemp, *lineprev;
	int first = 1;
	linetemp = line;
	if (s1<=s2)
	{
		while(linetemp!=NULL)
		{
			lineprev = linetemp;
			linetemp = linetemp->next;
			first = 0;
		}
		if (first)
		{
			linetemp = malloc(sizeof(*line));
			//StringMakeRealStringFrom
			linetemp->word = StringMakeNewFrom(str,s1,s2);
			linetemp->next = NULL;
			line = linetemp;
		} else {
			lineprev->next = malloc(sizeof(*line));
			linetemp = lineprev->next;
			//---ii---
			linetemp->word = StringMakeNewFrom(str,s1,s2);
			linetemp->next = NULL;
		}
	}
	
	return line;
}

struct CommandLine *CommandLineFromString(struct String *str)
{
	struct CommandLine *line;
	//struct String *empty; //possible desicion for s1>s2
	line = NULL;
	//we need better peace ->
	//-> of this
	int size;
	int i;
	//int first = 0;
	int s1,s2; //our separators
	//we're moving through our string, if ' ' or '"' => separate
	i=1; //we point at first symbol
	size = StringSize(str);
	while(i<=size-1) //-1 cause we have \n!!!
	{
		if (StringCharAt(str,i)=='"')
		{
			i = i + 1;
			//if i > size => error: unbalanced "
			s1 = i; //save our 1st separator
			while(i<=size && (StringCharAt(str,i)!='"'))
			{
	//printf("CharAt %i = (%c)\n",i,StringCharAt(str,i));
				i += 1;
			}
	//???errors in procedure???
			if (i > size)
			{
				printf("error:: unbalanced commas\n");
				break;
			}
			s2 = i - 1; //save our 2d separator
			if (s1 > s2)
			{
				printf("error:: empty commas\n");
				break;
			}
			line = CommandLineAddWord(line,str,s1,s2);
			i = i + 1;
		} else
			if (StringCharAt(str,i)!=' ') 
			{
			s1 = i;
			i += 1;
			while(i<=size && (StringCharAt(str,i)!=' '))
			{
				i += 1;
			}
			s2 = i - 1;
		//!!!if char = "\n" ->
			if (StringCharAt(str,s2) == '\n')
			{
				s2 = s2 - 1;
			}
		//!!! <-
			line = CommandLineAddWord(line,str,s1,s2);
		} else {
			i += 1;
		}
		//printf("I SEE CHAR = (%c)\n",StringCharAt(str,i));
	}
	return line;
}

int main()
{
	struct CommandLine *line;
	struct String *str;
	printf("Input string:\n");
	str = StringFill();
	/*
	printf("Your string:\n");
	StringPrint(str);
	*/
	/*
	printf("Size of your string:\n");
	printf("%i\n",StringSize(str));
	*/
	/*
	StringFree(str);
	str = NULL;
	printf("Your string after delete:\n");
	StringPrint(str);
	*/
	/*
	struct String *str1;
	str1 = StringMakeNewFrom(str,2,6);
	printf("Ive made another string\n");
	StringPrint(str1);
	printf("\n");
	printf("Which size is\n%i\n",StringSize(str1));
	*/
	
	
	//we have problem with test "12345"
	
	line = CommandLineFromString(str);
	printf("Your command words from line:\n");
	CommandLinePrint(line);
	
	
	StringFree(str);
	CommandLineFree(line);
	
	/*
	int i;
	for (i=1;i<=StringSize(str);i++)
	{
		printf("Your char at %i is %c\n",i,StringCharAt(str,i));
	}
	*/
	
	
	
	
	
}
