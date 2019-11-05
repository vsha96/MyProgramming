#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

struct CommandLine {
	char *word;
	int status;
	/*	illegal=-1, usual=0, bg=1 */
	int stream;
	/*
	usial = 0, > = 1, >> = 2, < = 3, | = 4
solution:
	cline1
	cline2 (what after separator)
	*/
	struct CommandLine *next;
};
enum {
	chunk_size = 8
};

struct String {
	int x[chunk_size]; /* elements of chunk */
	struct String *next;
};

struct String *StringFill()
{
	struct String *str,*temp; /*we use it when we create another buffer*/
	int i=0;
	int c; /*our char with EOF*/
	str = malloc(sizeof(*str));
	temp = str;
	while((c = getchar()) != '\n') /* EOF) */
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
	/*if (c == EOF)*/
	if (i != chunk_size)
	{
		temp->x[i]=EOF;
	}
	temp->next=NULL;
	/* is this free memory? */
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

/*we need some procedures to separate string into words*/
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
	/* is this free memory? */
	newtemp = NULL;

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

char *StringMakeRealStringFrom(struct String *str, int s1, int s2)
{ /*we add it to dont overwrite all of this*/
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
	/* is this free memory? */
	StringFree(temp);
	temp = NULL;
	
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

void CommandLinePrint(const struct CommandLine *line)
{
	while (line!=NULL)
	{
		printf("[%s]",line->word);
		/*printf("\t\t\t size:%lu",sizeof(line->word));*/
		line=line->next;
	}
	printf("\n");
}

void CommandLinePackPrint(struct CommandLine **line)
{
	int i = 0;
	while(line[i])
	{
		CommandLinePrint(line[i]);
		i++;
	}
}

int CommandLineSize(const struct CommandLine *line)
{
	int i=0;
	while (line != NULL)
	{
		line = line->next; i++;
	}
	return i;
}

void CommandLineFree(struct CommandLine *line)
{
	if (line != NULL)
	{
		CommandLineFree(line->next);
		free(line->word);
		free(line);
	}
}

void CommandLinePackFree(struct CommandLine **line)
{
	while (*line != NULL)
	{
		CommandLineFree(line[0]);
		line++;
	}
}

int CommandLineEmpty(const struct CommandLine *line)
{
	if (line == NULL)
	{
		return 1;
	} else {
		if (line->word[0] == 0)
		{
			return 1;
		} else {
			return 0;
		}
	}
}

struct CommandLine *CommandLineAddWord(struct CommandLine *line, struct String *str, int s1, int s2)
{ /*we can use recursion, it will be more compact code here with it*/
/* or **line , it is also will be more compact */
/* maybe one day I'll rewrite it */
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
		if (first && (str != NULL))
		{
			linetemp = malloc(sizeof(*line));
			linetemp->word = StringMakeRealStringFrom(str,s1,s2);
			linetemp->status = 0; /*added 27.10*/
			linetemp->stream = 0; /*added 27.10*/
			linetemp->next = NULL;
			line = linetemp;
		} else if (str != NULL){
			lineprev->next = malloc(sizeof(*line));
			linetemp = lineprev->next;
			linetemp->word = StringMakeRealStringFrom(str,s1,s2);
			linetemp->next = NULL;
		}
	}	
	/* is this free memory? */
	linetemp = NULL;
	lineprev = NULL;
	
	return line;
}

struct CommandLine *CommandLineChangeStatus(struct CommandLine *line, int newstat)
{
	int size = CommandLineSize(line);
	if (size == 0)
	{
		struct String *str0;
		str0 = malloc(sizeof(str0)); str0->x[0] = 0; str0->x[1] = EOF;
		line = CommandLineAddWord(line,str0,1,1);
		line->status = newstat;
		free(str0); str0 = NULL;
	} else {
		line->status = newstat;
	}
	return line;
}

struct CommandLine *CommandLineChangeStream(struct CommandLine *line, int newstream)
{
	int size = CommandLineSize(line);
	if (size == 0)
	{
		printf("error::attempt to change stream when size of line is 0\n");
		return NULL;
	} else {
		line->stream = newstream;
	}
	return line;
}

/*======SUPPORT FOR CommandLineFromString======*/
int StringCutCommas(struct CommandLine *line, struct String *str, int *i)
{
	/*StringCutCommas*/
	int size = StringSize(str);
	int s1, s2;
	*i = *i + 1;
	s1 = *i; /*save our 1st separator*/
	while(*i<=size && (StringCharAt(str,*i)!='"'))
	{
		*i += 1;
	}
	s2 = *i - 1; /*save our 2d separator*/
	if (*i > size)
	{
		line = CommandLineChangeStatus(line,-1);
		printf("error:: unbalanced commas\n");
		return -1;
	}
	if (s1 > s2)
	{
		line = CommandLineChangeStatus(line,-1);
		printf("error:: empty commas\n");
		return -1;
	}
	line = CommandLineAddWord(line,str,s1,s2);
	*i = *i + 1;
	return 0;
}


int StringCutAmpersand(struct CommandLine **line, struct String *str, int *i)
{
	/*CHANGE STATUS and make string without & at the end*/	
	if (CommandLineSize(line[0]) == 0)
	{	
		line[0] = CommandLineChangeStatus(line[0],-1);
		return -1;
	}
	if (StringSymbolsAfter(str,*i))
	{
		line[0] = CommandLineChangeStatus(line[0],-1);
		printf("error:: misplaced &\n");
		return -1;
	}
	line[0] = CommandLineChangeStatus(line[0],1);
	*i += 1;
	return 0;
}

int StringCutWords(struct CommandLine *line, struct String *str, int *i)
{ /*why isn't it working?*/
	int s1, s2, size = StringSize(str);
	int c;
	s1 = *i;
	*i += 1;
	while(*i<=size && (c = StringCharAt(str,*i)) != ' ' && c != '&')
	{
		*i += 1;
	}
	s2 = *i - 1;
/*
	if (StringCharAt(str,s2) == '\n') { s2 = s2 - 1; }
*/
	/*printf("%i %i\n",s1,s2);*/
	line = CommandLineAddWord(line,str,s1,s2);
	return 0;
}

/*5th step*/
int CountStreams(struct String *str)
{ /*we must create blocks of **CommandLine*/
	int i, n = 0, size = StringSize(str);
	int c;
	for(i=1;i<=size;i++)
	{
		/*here we may write some errors alerts!*/
		c = StringCharAt(str,i);
		if (c == '|' || c == '<' || (c == '>' && i < size && StringCharAt(str,i+1) == '>') || c == '>') n += 1;
	}
	return n;
}

struct CommandLine **CommandLinePackFromCount
(struct CommandLine **line, int count)
{
	int i;
	line = malloc((count+1+1)*sizeof(*line));
	for (i=0;i<count+1+1;i++)
	{
		line[i] = NULL;
	}
	return line;
}
/*5th step*/

int StringCutStreams
(struct CommandLine **line, struct String *str, int *i, int *j /*number of line in pack of lines*/)
{ /*I consider that I won't have incorrect string*/
	int size = StringSize(str);
	int c, st;
	if ((st = line[0]->stream) != 0 && st != 4)
	{
		printf("error::trying to change stream several times\n");
		return -1;
	}
	if ((c = StringCharAt(str,*i)) == '>' && (*i < size) && StringCharAt(str,*i+1) == '>')
	{
		line[0] = CommandLineChangeStream(line[0],2);
		*i += 1;
	} else if (c == '<') {
		line[0] = CommandLineChangeStream(line[0],3);
	} else if (c == '|') {
		/*I really dont like that we initialize stream several times*/
		/*maybe one day I will write some errors alerts*/
		line[0] = CommandLineChangeStream(line[0],4);
	} else {
		line[0] = CommandLineChangeStream(line[0],1);
	}
	if (!StringSymbolsAfter(str,*i+1))
	{
		line[0] = CommandLineChangeStatus(line[0],-1);
		printf("error:: missing argument after change stream\n");
		return -1;
	}
	*i += 1; *j += 1;
	return 0;
}
/*====== END OF SUPPORT ======*/

struct CommandLine **CommandLineFromString(struct String *str)
{
	struct CommandLine **line;
	line = NULL;
	line = CommandLinePackFromCount(line,CountStreams(str));
	int s1, s2, c;
	int i, j, size;
	/*we're moving through our string, if ' ' or '"' => separate*/
	j = 0; /*our index in pack of command lines*/
	i=1; /*we're pointing at first symbol*/
	size = StringSize(str);
	while(i<=size)
	{
		c = StringCharAt(str,i);
		if (c == '"') {
			if (StringCutCommas(line[j],str,&i)) break;
		} else if (c == '&') {
			if (StringCutAmpersand(line,str,&i)) break;
		} else if (c == '>' || c == '<' || c == '|') {
			if (StringCutStreams(line,str,&i,&j)) break;
		} else if (c != ' ') {
			/*StringCutWords(line,str,&i);*/
			s1 = i;
			i += 1;
			while(i<=size && (c = StringCharAt(str,i)) != ' ' && c != '&' && c != '>' && c != '<' && c != '|')
			{
				i += 1;
			}
			s2 = i - 1;
		/*
			if (StringCharAt(str,s2) == '\n') { s2 = s2 - 1; }
		*/
			line[j] = CommandLineAddWord(line[j],str,s1,s2);
		} else {
			i += 1;
		}
		/*printf("I SEE CHAR = (%c)\n",StringCharAt(str,i));*/
	}
	if (size == 0) line[0] = CommandLineChangeStatus(line[0],0);

	return line;
}

/*======CONVERTE LINE equal CHAR ** NAME======*/
char **CommandLineConverter(const struct CommandLine *line)
{ /*our |line| became |cline|*/
	int i, size = CommandLineSize(line);
	char **p;
	p = malloc((size+1)*sizeof(*p));
	for (i=0;i<size;i++)
	{
		p[i] = line->word;
		line = line->next;
	}
	p[i] = NULL;
	return p;
}

void ClinePrint(char * const *cline)
{
	int i=0;
	while (cline[i] != NULL)
	{
		printf("%s\n",cline[i]); i++;
	}
}

void ClineFree(char ** cline)
{
	/*
	int i=0;
	while(cline != NULL)
	{
		free(cline[i]); i++;
	}
	*/
	free(cline);
}

/*======COMMAND LINE======*/
int CommandCD(const struct CommandLine *line)
{
	if (RealStringEqual(line->word,"cd"))
	{
		return 1;
	} else {
		return 0;
	}
}

int CommandConv(const struct CommandLine *line)
{
	if (line == NULL)
	{
		printf("oh fuck conv\n"); return 0;
	} else {
		if (line->stream == 4)
		{
			return 1;
		} else {
			return 0;
		}
	}
}

int CommandBG(const struct CommandLine *line)
{
	if (line == NULL)
	{
		printf("oh fuck1\n"); return 0;
	} else {
		if (line->status == 1)
		{
			/*printf("it's bg\n");*/
			return 1;
		} else {
			return 0;
		}
	}
}

int CommandIllegal(const struct CommandLine *line)
{
	if (line == NULL)
	{
		printf("oh fuck2\n"); return 0;
	} else {
		if (line->status == -1)
		{
			//printf("error:: illegal command\n");
			return 1;
		} else {
			return 0;
		}
	}
}
/*
void CommandLineStream(const struct CommandLine *line)
{}
*/

void StreamOpen(int st, int fd, char **cline1)
{
	if (st == 1) /* > */
		fd = open(cline1[0],O_WRONLY|O_CREAT|O_TRUNC,0666);	
	if (st == 2) /* >> */
		fd = open(cline1[0],O_WRONLY|O_CREAT|O_APPEND,0666);
	if (st == 3) /* < */
		fd = open(cline1[0],O_RDONLY,0666);	
	if (fd == -1)
	{
		perror(cline1[0]);
		exit(1);
	}
	if (st == 3)
	{
		dup2(fd,0);
	} else {	
		dup2(fd,1);
	}
}

void ConvOpen(int fd[2])
{
	/*TODO*/
}

void CLineExecute(struct CommandLine **line, char **cline, char **cline1)
{
	int st,fd = 0; /*stream, file descriptor*/

	if ((st = line[0]->stream) != 0)
	{
		StreamOpen(st, fd, cline1); /*put (&fd) for close(fd) lower*/
	}

	execvp(cline[0],cline);
	perror(cline[0]);
	fflush(stderr);
	exit(1);
	/*
	if (st != 0)
	{
		close(fd);
	}
	*/
}

void CommandLineProcessor(struct CommandLine **line)
{ 
	int r,pid;
	int kpid; /*killed pid*/
	char **cline = CommandLineConverter(line[0]);
	char **cline1 = CommandLineConverter(line[1]);
	/*printf("your strings [%s] [%s]\n",cline[0],cline1[0]);*/
	/*cleaning*/
	while ( (kpid = wait4(-1,NULL,WNOHANG,NULL)) > 0 ){}
	if (CommandCD(line[0]))
	{
		r = chdir(cline[1]);
		if (r == -1)
		{
			perror(cline[1]);
		}
	} else if (CommandConv(line[0])) {
		/*TODO*/
		int fd[2];
		fd[0] = 0; fd[1] = 1; pid = 0;
		int i = 0;
		/*we can't collect all pids, need revise this cycle*/
		int mpid[32], j;
		for (j=0;j<32;j++) { mpid[j] = 0; }

		while(line[i])
		{
			cline = CommandLineConverter(line[i]);

			//dup2(fd[0],0); /*at begining fd[0]=0*/
			if (i != 0)
			{
				dup2(fd[0],0);
				close(fd[1]);
			}
			
			if (line[i+1]) 
				pipe(fd);
			
			
			pid = fork();
			mpid[i] = pid;
			if (pid == 0)
			{
				close(fd[0]);
				dup2(fd[1],1);
				execvp(cline[0],cline);
				perror(cline[0]);
				fflush(stderr);
				exit(1);
			}
			i++;
		}
		
		
		/*
		for (j=0;j<4;j++)
		{
			printf("[%i]\n",mpid[j]);
		} printf("===\n");
		*/
		
		if (!CommandBG(line[0]))
		{
			while((kpid = wait(NULL)))
			{
				int check = 0;
				for (j=0;j<i+1;j++) /*we launched (i) processes*/
				{
					check += mpid[j];
					if (kpid == mpid[j])
					{
						mpid[j] = 0; break;
					}
				}	
				if (check == 0) break;
				check = 0;
			}
		}
		
		/*
		for (j=0;j<4;j++)
		{
			printf("[%i]\n",mpid[j]);
		} printf("===\n");
		*/

		/*
		execvp(cline[0],cline);
		perror(cline[0]);
		fflush(stderr);
		exit(1);
		*/

	} else {
		pid = fork();	
		if (pid == 0)
		{
			CLineExecute(line, cline, cline1);
		}
		if (!CommandBG(line[0]))
		{
			while ( (kpid = wait(NULL)) != pid ){}	
		}
	}
	ClineFree(cline);
	if (!cline1) ClineFree(cline1);
}


int main()
{
	
	struct CommandLine **line;
	struct String *str;
	
	for(;;)
	{
		printf("-->");
		str = StringFill();
		
		line = CommandLineFromString(str);
		
		/*
		printf("your pack of lines:\n");
		CommandLinePackPrint(line);
		printf("your status: %i\n",line[0]->status);
		printf("your stream: %i\n",line[0]->stream);
		*/
		/*
		printf("%i\n", CountStreams(str));
		*/
		/*
		line = CommandLinePackFromCount(line,5);
		CommandLinePackPrint(line);
		*/
		/*CommandLineStream(line)*/
		
		/*
		CommandLinePackPrint(line);
		*/


		if (CommandLineEmpty(line[0]) || CommandIllegal(line[0]))
		{
			StringFree(str);
			CommandLinePackFree(line);	
			continue;
		}
		
		/*
		char **cline;
		cline = CommandLineConverter(line);
		printf("your line\n");
		CommandLinePrint(line);
		printf("your cline\n");
		ClinePrint(cline);
		*/
		
		
		CommandLineProcessor(line);

		StringFree(str);
		CommandLinePackFree(line);

		str = NULL; /* line[0] = NULL; */
	}
	

}
