#include "simple_shell.h"

/**
 * _splitbuffer - creates array of tokens based on user string
 * @buffer: pointer to user string
 *
 * Return: pointer to array of user strings
 */
char **_splitbuffer(char *buffer)
{
	char *token = NULL;
	int i = 0, nb = 0;
	char *sep = " \n";
	char **av = NULL;

	nb = _splitstring(buffer);
	if (!nb)
		return (NULL);
	av = malloc((nb + 1) * sizeof(char *));
	if (av == NULL)
		exit(1);
	token = strtok(buffer, sep);
	while (token != NULL)
	{
		av[i] = _strdup(token);
		token = strtok(NULL, sep);
		i++;
	}
	av[i] = NULL;
	return (av);
}
/**
 * _splitPATH - counts the number of PATH members
 * @str: pointer to string to count
 *
 * Return: number of PATH members
 */
int _splitPATH(char *str)
{
	int i, test = 1, nb = 0;

	for (i = 0; str[i]; i++)
	{
		if (str[i] != ':' && test == 1)
		{
			nb += 1;
			test = 0;
		}
		if (str[i + 1] == ':')
		{
			test = 1;
		}
	}
	return (nb);
}
/**
 * _PATHcompare - compares PATH with environ to find PATH value
 * @str1: pointer PATH string
 * @str2: pointer to environ string with actual value
 *
 * Return: 0 on success
 */
int _PATHcompare(const char *str1, const char *str2)
{
	int i;

	for (i = 0; str2[i] != '='; i++)
	{
		if (str1[i] != str2[i])
			return (-1);
	}
	return (0);
}
/**
 * _concat - concats user string with PATH member string and /
 * @tmp: static array to store concatenated string
 * @av: pointer to array of user strings
 * @tok: pointer to PATH token
 *
 * Return: 0 on success
 */
char *_concat(char *tmp, char **av, char *tok)
{
	int len = 0;

	_memset(tmp, 0, 256);
	len = _strlen(tok) + _strlen(av[0]) + 2;
	_strcat(tmp, tok);
	_strcat(tmp, "/");
	_strcat(tmp, av[0]);
	tmp[len - 1] = '\0';
	return (tmp);
}
