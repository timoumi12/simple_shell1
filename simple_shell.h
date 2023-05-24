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

/*String.c*/




