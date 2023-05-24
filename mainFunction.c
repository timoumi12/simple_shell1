#include "simple_shell.h"


/**
 * prompt - print $
 * Return: 0
*/

void prompt(void)
{
	int w;
	char *prompt = "($) ";

	if (isatty(STDIN_FILENO) == 1)
	{
		w = write(STDOUT_FILENO, prompt, 4);
	}
	if (w == -1)
		exit(0);
}

/**
 * _read - read input
 * Return: returns the buffer element
*/

char *_read(void)
{
	int i, count;
	char *buffer = NULL;
	size_t n = 0;

	count = getline(&buffer, &n, stdin);
	if (count == -1)
	{
		free(buffer);
		/*if (isatty(STDIN_FILENO) != 0)*/
		/*write(STDOUT_FILENO, "\n", 1);*/
		exit(0);
	}
	if (buffer[count - 1] == '\n')
	{
		buffer[count - 1] = '\0';
	}
	for (i = 0; buffer[i]; i++)
	{
		if (buffer[i] == '#' && buffer[i - 1] == ' ')
		{
			buffer[i] = '\0';
			break;
		}
	}
	return (buffer);
}

/**
* builtinFunction - check if the string is a builtin or not
* @av: pointer to array of user of strings
* @buffer: pointer to user string
* @exitstatus: exit status of execve
* Return: 1 if the string is equal env or 0 other wise
*/
int builtinFunction(char **av, char *buffer, int exitstatus)
{
	int i;

	if (_strcmp(av[0], "env") == 0)
	{
		_env();
		for (i = 0; av[i]; i++)
			free(av[i]);
		free(av);
		free(buffer);
		return (1);
	}
	else if (_strcmp(av[0], "exit") == 0)
	{
		for (i = 0; av[i]; i++)
			free(av[i]);
		free(av);
		free(buffer);
		exit(exitstatus);
	}
	else
		return (0);
}

/**
 * _fork - create child process to execute the user input
 * @av: pointer to array of strings
 * @buffer: pointer to user string
 * @fullpathbuffer: pointer to user input
 *
 * Return: 0 on success
 */
int _fork(char **av, char *buffer, char *fullpathbuffer)
{
	int i, status, result, exitstatus = 0;
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		exit(1);
	}
	if (pid == 0)
	{
		result =  execve(fullpathbuffer, av, environ);
		if (result == -1)
		{
			perror(av[0]);
			for (i = 0; av[i]; i++)
				free(av[i]);
			free(av);
			free(buffer);
			exit(127);
		}
	}
	wait(&status);
	if (WIFEXITED(status))
	{
		exitstatus = WEXITSTATUS(status);
	}
	for (i = 0; av[i]; i++)
		free(av[i]);
	free(av);
	free(buffer);
	return (exitstatus);
}
/**
 * _fullpathbuffer - finds the string to call execve on
 * @av: pointer to array of user strings
 * @PATH: pointer to PATH string
 * @copy: pointer to copy of PATH string
 *
 * Return: a pointer to string to call execve on
 */

char *_fullpathbuffer(char **av, char *PATH, char *copy)
{
	char *tok = NULL, *fullpathbuffer = NULL, *concatstr = NULL;
	static char tmp[256];
	int PATHcount = 0, fullpathflag = 0, z = 0, toklen = 0;
	struct stat h;

	copy = NULL;
	copy = _strdup(PATH);
	PATHcount = _splitPATH(copy);
	tok = strtok(copy, ": =");
	while (tok != NULL)
	{
		concatstr = _concat(tmp, av, tok);
		if (stat(concatstr, &h) == 0)
		{
			fullpathbuffer = concatstr;
			fullpathflag = 1;
			break;
		}
		if (z < PATHcount - 2)
		{
			toklen = _strlen(tok);
			if (tok[toklen + 1] == ':')
			{
				if (stat(av[0], &h) == 0)
				{
					fullpathbuffer = av[0];
					fullpathflag = 1;
					break;
				}
			}
		}
		z++;
		tok = strtok(NULL, ":");
	}
	if (fullpathflag == 0)
		fullpathbuffer = av[0];
	free(copy);
	return (fullpathbuffer);
}
