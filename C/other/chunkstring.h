#ifndef CHUNKSTRING_H_SENTRY
#define CHUNKSTRING_H_SENTRY
enum {
    chunk_size = 8
};
struct String {
	int x[chunk_size];
    struct String *next;
};

struct String *StringFill();
void StringPrint(const struct String *str);
void StringFree(struct String *str);
int StringSize(const struct String *str);
struct String *StringMakeNewFrom(struct String *str,int s1,int s2);
int StringCharAt(const struct String *str, int i);
int StringSymbolsAfter(const struct String *str, int i);

char *StringMakeRealStringFrom(struct String *str, int s1, int s2);
int RealStringEqual(char *s1, char *s2);
#endif
