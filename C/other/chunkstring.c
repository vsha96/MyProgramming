#include <stdio.h>
#include <stdlib.h>
#include "chunkstring.h"
/*
StringFill
	struct String *StringFill()
StringPrint
	void StringPrint(const struct String *str)
StringFree
	void StringFree(struct String *str)
StringSize
	int StringSize(const struct String *str)
StringMakeNewFrom
	struct String *StringMakeNewFrom(struct String *str,int s1,int s2)
StringCharAt
	int StringCharAt(const struct String *str, int i)
StringSymbolsAfter
	int StringSymbolsAfter(const struct String *str, int i)

==============REAL STRING==============
StringMakeRealStringFrom
	char *StringMakeRealStringFrom(struct String *str, int s1, int s2)
RealStringEqual
	int RealStringEqual(char *s1, char *s2)
*/

struct String *StringFill()
{
    struct String *str,*temp; /*we use it when we create another buffer*/
    int i=0;
    int c; /*our char with EOF*/
    str = malloc(sizeof(*str));
    temp = str;
    while((c = getchar()) != '\n')
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
    if (i != chunk_size)
    {
        temp->x[i]=EOF;
    }
    temp->next=NULL;
    temp = NULL;
    return str;
}

void StringPrint(const struct String *str)
{
    const struct String *temp;
    int i=0;
    int c; /*our char with EOF*/
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

void StringFree(struct String *str)
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

struct String *StringMakeNewFrom(struct String *str,int s1,int s2)
{   
    struct String *temp, *newstr, *newtemp;
    int i,j,l;
    temp = str; 
    s1 -= 1; s2 -= 1; /*shift*/
    s2 = s2 - s1; /*pass few lines we'll make another base*/
    /*move to our 1st separator*/
    for (i=0;i<(s1/chunk_size);i++)
    {   
        temp = temp->next;
    }
    s1 = s1 % chunk_size; /*we made another base*/
    s2 = s1 + s2; /*s2 points in new base*/
    newstr = malloc(sizeof(*newstr));
    newtemp = newstr;
    for (j=s1;j<=s2;j++)
    {   
        l = j-s1; /*index in chunk of newstr*/
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
    l = j-s1; /*index in chunk of newstr*/
    /*ending*/
    if ( ((l)%chunk_size) != 0 )
    {   
        newtemp->x[(l%chunk_size)]=EOF;
    }
    newtemp->next=NULL;
    return newstr;
}

int StringCharAt(const struct String *str, int i)
{
    int size = StringSize(str);
    if (i > size)
    {
        printf("warning::we're trying to get StringCharAt with i > size!\n");
        return -1;
    } else {
        i = i - 1; /*shift*/
        int j;
        for (j=0;j<(i/chunk_size);j++)
        {
            str=str->next;
        }
        return str->x[i%chunk_size];
    }
}

int StringSymbolsAfter(const struct String *str, int i)
{
    int j, size = StringSize(str);
    for (j=i+1;j<=size;j++)
    {
        if ((StringCharAt(str,j)) != ' ') { return 1; }
    }
    return 0;
}

/*==============REAL STRING==============*/
char *StringMakeRealStringFrom(struct String *str, int s1, int s2)
{
    struct String *temp;
    char *p;
    temp = StringMakeNewFrom(str,s1,s2);
    int i, size = StringSize(temp);
    p = malloc((size+1));
    for (i=1;i<=size;i++)
    {
        p[i-1] = (char)StringCharAt(temp,i);

    }
    p[i-1] = 0;
    /* free memory */
    StringFree(temp);
    return p;
}

int RealStringEqual(char *s1, char *s2)
{
    int i=0;
    while (s1[i] || s2[i])
    {
        if (s1[i] != s2[i])
        {
            return 0;
        }
        i+=1;
    }
    return 1;
}
