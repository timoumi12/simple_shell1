#include "simple_shell.h"

/**
 * main - runs the shell program
 *
 * Return: 0 on success
 */
int main(void)
{
	char *fullpathbuffer = NULL, *copy = NULL, *buffer = NULL;
	char *PATH = NULL;
	char **av = NULL;
	int exitstatus = 0;

	signal(SIGINT, SIG_IGN);
	PATH = _getenviron("PATH");
	if (PATH == NULL)
		return (-1);
	while (1)
	{
		av = NULL;
		prompt();
		buffer = _read();
		if (*buffer != '\0')
		{
			av = splitbuffer(buffer);
			if (av == NULL)
			{
				free(buffer);
				continue;
			}
			fullpathbuffer = _fullpathbuffer(av, PATH, copy);
			if (builtinFunction(av, buffer, exitstatus) != 0)
				continue;
			exitstatus = _fork(av, buffer, fullpathbuffer);
		}
		else
			free(buffer);
	}
	return (0);
}
