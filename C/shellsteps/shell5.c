/*
	Ivan Shulyugin (vsha96)
	MSU CMC 2019
=========================
	It is my shell.
	Realised:
		= execution of commands (processes)
		= streams > >> <
		= conveyor |
=========================
	There is a lot of work for "brilliant" shell but my shell just a try (and I think it's successful attempt) to learn more about different structures of data, processes, streams, pipes, etc.
*/
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
	/* usial = 0, > = 1, >> = 2, < = 3, | = 4 */
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
	return newstr;
}

int StringCharAt(const struct String *str, int i)
{
	int size = StringSize(str);
	if (i > size)
	{
		printf("warning::attemp to get StringCharAt with i > size!\n");
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
		if ((StringCharAt(str,j)) != ' ')
			return 1;
	}
	return 0;
}

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

void CommandLinePrint(const struct CommandLine *line)
{
	while (line!=NULL)
	{
		printf("[%s]",line->word);
		/*printf("\t\t\t size:%lu",sizeof(line->word));*/
		line=line->next;
	}
}

void CommandLinePackPrint(struct CommandLine **line)
{
	int i = 0;
	while(line[i])
	{
		CommandLinePrint(line[i]);
		printf("(status:%i)(stream:%i)\n",
			line[i]->status,
			line[i]->stream);
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

int CommandLinePackSize(struct CommandLine **line)
{
	int i = 0;
	while(line[i])
	{
		i++;
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

struct CommandLine *CommandLineAddWord(
	struct CommandLine *line,
	struct String *str,
	int s1,
	int s2
)
{
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
			line = linetemp;
		} else {
			lineprev->next = malloc(sizeof(*line));
			linetemp = lineprev->next;
		}
		linetemp->word = StringMakeRealStringFrom(str,s1,s2);
		linetemp->status = 0;
		linetemp->stream = 0;
		linetemp->next = NULL;
	}	
	return line;
}

struct CommandLine *
CommandLineChangeStatus(struct CommandLine *line, int newstat)
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

struct CommandLine *
CommandLineChangeStream(struct CommandLine *line, int newstream)
{
	int size = CommandLineSize(line);
	if (size == 0 || line == NULL)
	{
		printf("error::attempt to change stream when size is 0\n");
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


int StringCutAmpersand(
	struct CommandLine **line,
	struct String *str,
	int *i
)
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
	/*printf("%i %i\n",s1,s2);*/
	line = CommandLineAddWord(line,str,s1,s2);
	return 0;
}

int StreamAppeared(struct String *str, int *i, int size)
{
	int c = StringCharAt(str,*i);
	return c == '|' || c == '<' || 
			(c == '>' && 
				(*i) < size && 
				StringCharAt(str,*i+1) == '>') ||
			c == '>';
}

/*5th step*/
int CountStreams(struct String *str)
{ /*we must create blocks of **CommandLine*/
	int i, n = 0, size = StringSize(str);
	for(i=1;i<=size;i++)
	{
		if (StreamAppeared(str, &i, size))
			n += 1;
	}
	return n;
}

struct CommandLine **CommandLinePackFromCount
(struct CommandLine **line, int count)
{
	int i;
	/*there are another +1 cause example: cat | cat*/
	/*there are 1 change stream, but two commands*/
	line = malloc((count+1+1)*sizeof(*line));
	for (i=0;i<count+1+1;i++)
	{
		line[i] = NULL;
	}
	return line;
}
/*5th step*/

int StringCutStreams
(struct CommandLine **line, struct String *str, int *i, int *j)
{ /*I consider that I won't have incorrect string*/
	int size = StringSize(str);
	int c;
	int st;
	if (line[0] == NULL)
	{
		printf("error::there are no commands among |\n");
		return -1;
	}
	if ((st=line[0]->stream) != 0 && st != 4)
	{ /*!there are not all errors that may appear*/
		printf("error::trying to change stream several times\n");
		return -1;
	}
	if ((c = StringCharAt(str,*i)) == '>' &&
		(*i < size) &&
		StringCharAt(str,*i+1) == '>')
	{
		line[*j] = CommandLineChangeStream(line[*j],2);
		*i += 1;
	} else if (c == '<') {
		line[*j] = CommandLineChangeStream(line[*j],3);
	} else if (c == '|') {
		line[*j] = CommandLineChangeStream(line[*j],4);
	} else {
		line[*j] = CommandLineChangeStream(line[*j],1);
	}
	if (!StringSymbolsAfter(str,*i+1) || (*j > 0 && line[*j] == NULL))
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
			while(i<=size &&
				(c = StringCharAt(str,i)) != ' ' &&
				c != '&' &&
				c != '>' &&
				c != '<' &&
				c != '|')
			{
				i += 1;
			}
			s2 = i - 1;
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
	free(cline);
}

/*======COMMAND LINE======*/
int CommandCD(const struct CommandLine *line)
{
	return RealStringEqual(line->word,"cd");
}

int CommandConv(const struct CommandLine *line)
{
	if (line == NULL)
	{
		printf("this is bad, conv\n"); return 0;
	} else {
		return line->stream == 4;
	}
}

int CommandBG(const struct CommandLine *line)
{
	if (line == NULL)
	{
		printf("this is bad1\n"); return 0;
	} else {
		return line->status == 1;
	}
}

int CommandIllegal(const struct CommandLine *line)
{
	if (line == NULL)
	{
		printf("this is bad\n"); return 0;
	} else {
		return line->status == -1;
	}
}

int ConvCount(struct CommandLine **line)
{
	int i = 0;
	int n = 0;
	while(line[i])
	{
		if (line[i]->stream == 4)
			n += 1;
		i += 1;
	}
	return n+1;
}

void StreamOpen(int st, char **cline1)
{
	int fd;
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

void CExe(struct CommandLine *line)
{
	char **cline;
	cline = CommandLineConverter(line);
	execvp(cline[0],cline);
	perror(cline[0]);
	fflush(stderr);
	exit(1);
}

void CLineExecute(struct CommandLine **line, int *j)
{
	int st; /*stream, file descriptor*/
	char **cline = CommandLineConverter(line[*j]);
	if ((st = line[*j]->stream) != 0 && st != 4)
	{
		char **cline1 = CommandLineConverter(line[*j+1]);
		*j += 1;
		StreamOpen(st, cline1);
		execvp(cline[0],cline);
		perror(cline[0]);
		fflush(stderr);
		exit(1);
	}
	execvp(cline[0],cline);
	perror(cline[0]);
	fflush(stderr);
	exit(1);
}

void SetupFDs(int ***fd, int i, int size)
{
	int j;
	/*close unnecessary fd-s*/
	for(j=0;j<i-1;j++)
	{
		close((*fd)[j][0]);
		close((*fd)[j][1]);
	}
	for(j=i+1;j<size-1;j++)
	{
		close((*fd)[j][0]);
		close((*fd)[j][1]);
	}
	/*setup near fd-s*/
	if (i > 0)
	{
		dup2((*fd)[i-1][0],0);
		close((*fd)[i-1][1]);
	}
	if (i < size - 1)
	{
		close((*fd)[i][0]);
		dup2((*fd)[i][1],1);
	}
}

void CloseFDs(int ***fd, int size)
{
	int i;
	for (i=0;i<size-1;i++)
	{
		close((*fd)[i][0]);
		close((*fd)[i][1]);
	}
}

void ConvExecution(struct CommandLine **line)
{
	int i, j, size = ConvCount(line), kpid;
	int **fd /*our filedescriptors*/, *mpid; /*our saved pids*/
	fd = malloc(size*(sizeof(*fd)));
	for (i=0;i<size;i++)
		fd[i] = malloc((2+1)*sizeof(fd));
	mpid = malloc((size+1)*(sizeof(*mpid)));
	for (i=0;i<size-1;i++)
		pipe(fd[i]);
	
	for (i=0;i<size;i++)
	{
		mpid[i] = fork();
		if (mpid[i] == 0)
		{
			SetupFDs(&fd, i, size);
			CLineExecute(line, &i);
		}
	}
	CloseFDs(&fd, size);
	if (!CommandBG(line[0]))
	{
		while((kpid = wait(NULL)))
		{
			int check = 0;
			for (j=0;j<size;j++) /*we launched n=size processes*/
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
	for (i=size-1;i>=0;i--)
		free(fd[i]);
	free(fd);
	free(mpid);
}

void CommandLineProcessor(struct CommandLine **line)
{ 
	int r, pid, kpid;
	char **cline = CommandLineConverter(line[0]);
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
		ConvExecution(line);	
	} else {
		pid = fork();	
		if (pid == 0)
		{
			int j = 0;
			CLineExecute(line, &j);
		}
		if (!CommandBG(line[0]))
		{
			while ( (kpid = wait(NULL)) != pid ){}	
		}
	}
	ClineFree(cline);
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
		if (CommandLineEmpty(line[0]) || CommandIllegal(line[0]))
		{
			StringFree(str);
			CommandLinePackFree(line);	
			continue;
		}
		
		CommandLineProcessor(line);

		StringFree(str);
		CommandLinePackFree(line);
		str = NULL;
	}
}
