#include "simple_shell.h"

/**
 * _getenviron - gets PATH member from environ
 * @name: pointer to PATH
 *
 * Return: pointer to PATH or NULL if not found
 */
char *_getenviron(const char *name)
{
	int i, result;

	for (i = 0; environ[i]; i++)
	{
		result = _PATHcompare(name, environ[i]);
		if (result == 0)
		{
			return (environ[i]);
		}
	}
	return (NULL);
}
/**
 * _env - prints the environ
 *
 * Return: 0 on success
 */
int _env(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		_puts(environ[i]);
	return (0);
}
/**
 * _puts - prints a string
 * @s: string to print
 */
void _puts(char *s)
{
	int c;

	for (c = 0; s[c] != '\0'; c++)
		_putchar(s[c]);
	_putchar('\n');
}
/**
 * _putchar - prints a character
 * @c: character to print
 *
 * Return: return value of write syscall
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
/**
 * _memset - fills memory with a constant byte
 * @s: character array to fill
 * @b: constant byte to fill with
 * @n: how many bytes to fill
 * Return: the pointer to the char array
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}
