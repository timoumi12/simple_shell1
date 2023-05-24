#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

extern char **environ;

/* mainFunction.c */

void prompt(void);
char *_read(void);
int builtinFunction(char **av, char *buffer, int exitstatus);
int _fork(char **av, char *buffer, char *fullpathbuffer);
char *_fullpathbuffer(char **av, char *PATH, char *copy);

/* String.c */

char *_strdup(char *str);
int _splitstring(char *str);
int _strcmp(const char *s1, const char *s2);
char *_strcat(char *dest, char *src);
int _strlen(char *s);

/* PATH.c */

char **_splitbuffer(char *buffer);
int _splitPATH(char *str);
int _PATHcompare(const char *str1, const char *str2);
char *_concat(char *tmp, char **av, char *tok);

/* helper.c */

char *_getenviron(const char *name);
int _env(void);
void _puts(char *s);
int _putchar(char c);
char *_memset(char *s, char b, unsigned int n);

#endif
