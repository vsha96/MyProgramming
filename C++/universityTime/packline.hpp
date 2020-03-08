#ifndef PACKLINE_H_SENTRY
#define PACKLINE_H_SENTRY

int is_it_sep(int c, const char *sep);
int word_count(const char *line, const char *sep);
void packline_print(char **packline);
int packline_size(char **packline);
void packline_free(const char **packline);
char **make_packline(const char *line, const char *sep);

#endif
