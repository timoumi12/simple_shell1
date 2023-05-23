#include "SIMPLE_SHELL_H"


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
    int i, w, count, *n;
    char *buffer = NULL;

    count = getline(&buffer, &n, stdin);
    if (count == -1)
    {
        free(buffer);
        if (isatty(STDIN_FILENO) != 0)
            write(STDOUT_FILENO, "\n", 1);
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
