#include <stdio.h>
#include <stdlib.h>
struct CommandWord {
	struct string *word;
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
		while((c=(temp->x[i]))!=EOF && (i<chunk_size)) 
		{
			putchar(c);
			i++;
		}
		temp=temp->next;
		i=0;
	}
}

void CommandLinePrint(const struct CommandWord *line)
{
	const struct CommandWord *linetemp;
	linetemp = line;
	while (linetemp!=NULL)
	{
		StringPrint(linetemp->word);
		printf("\n");
		linetemp=linetemp->next;
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
//===new idea===
		for (j=s1;j<=s2;j++)
		{
			l = j-s1; //index in chunk of newstr
	//printf("\tj = %i\n",j);
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
		
//===old idea===
/*
	//copy every chunk we needed //!BASE (s2-1) -> (s1+s2-1) etc
	for (i=0;i<=((s2-1)/chunk_size);i++)
	{
		//if first chunk
		if (i==0)
		{
			if ((s2-1)/chunk_size!=0) //if 2nd separator not in our chunk
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
				if (j-s1+1 != chunk_size)
				{
					newtemp->x[j-s1+1]=EOF;
				}
				newtemp->next=NULL;
			}
		}
		
		//if last chunk
		// we need to pay attention for our new base!
		//Ive fucked up
		if (i==((s2-1)/chunk_size))
		{
			if ((s2-1)/chunk_size!=0) //if 2nd separator not in our chunk
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
				if (j-s1+1 != chunk_size)
				{
					newtemp->x[j-s1+1]=EOF;
				}
				newtemp->next=NULL;
			}
		}
		//else
		else
		{
			newtemp->next=malloc(sizeof(*newstr));
			for (j=0;j<chunk_size;j++)
			{
				newtemp->x[j]=temp->x[j];
			}
		}
	}
*/
	return newstr;
}


struct CommandWord *StringSeparate(struct string *str)
{
	struct CommandWord *line,*linetemp;
	struct string *temp;
	temp = str;
	line = malloc(sizeof(*line));
	linetemp = line;
	linetemp->next=NULL;
	int i,j,m;
	int p,q;
	int flagspace=0,flag=0;
	//we're moving through our string, if ' ' or '"' => separate
	for (i=1;i<=StringSize(str);i++) //!!! <= : we need last symbol
	{
		j = i - 1; //shift
		if ((j != 0) && (j%chunk_size==0))
		{
			temp=temp->next;
		}
		m = j%chunk_size; //our index in chunk
		//printf("\t%i\n",m);
		if ((temp->x[m] == '"') && (flag==0))
		{
			p = i+1;
			flag = 1;
		} else if ((temp->x[m] == '"') && (flag==1)) {
			q = i-1;
			linetemp->word = StringMakeNewFrom(str,p,q);
			linetemp->next = malloc(sizeof(*line));
			linetemp = linetemp->next;
			linetemp->next = NULL;
			flag = 0;
		} else {
		// if spaces
			if ((temp->x[m]!=' ') && ((flagspace==0) && (flag==0)))
			{
				p = i;
				flagspace = 1;
			} else if (((temp->x[m]==' ') || (temp->x[m])=='\n') && ((flagspace==1) && (flag==0)))
			{
				q = i;
				linetemp->word = StringMakeNewFrom(str,p,q);
				linetemp->next = malloc(sizeof(*line));
				linetemp = linetemp->next;
				linetemp->next = NULL;
				flagspace = 0;
			}
		}
	}
	return line;
	
}

int main()
{
	struct CommandWord *line;
	struct string *str;
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
	/*
	struct string *str1;
	str1 = StringMakeNewFrom(str,1,StringSize(str));
	printf("Ive made another string\n");
	StringPrint(str1);
	printf("\n");
	printf("Which size is\n%i\n",StringSize(str1));
	*/
	line = StringSeparate(str);
	printf("Your command words from line\n");
	CommandLinePrint(line);
	printf("\n");
	
	return 0;
}