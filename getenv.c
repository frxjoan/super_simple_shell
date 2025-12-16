#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern char **environ;
char *_getenv(const char *name)
{
	unsigned int i = 0;
	char *ptr = environ[0];
	int len = strlen(name);

	while (environ[i])
	{
		if (strncmp(environ[i], name, len) == 0)
		{
			if (environ[i][len] == '=')
			{
				ptr = environ[i] + len + 1;
				return (ptr);
			}
		}
		i++;
	}
	return (NULL);
}

void print_dir(char *path)
{
	char *line = _getenv(path);
	char *line_cpy; 
	char *dir;

	if (!line)
		return;

	line_cpy = strdup(line);
	if (!line_cpy)
		return;

	dir = strtok(line_cpy, ":");
	while(dir)
	{
		printf("%s\n", dir);
		dir = strtok(NULL, ":");
	}
	free(line_cpy);
}

int main(void)
{
	char *tester1 = _getenv("PATH");
	printf("%s\n", tester1);
	print_dir("PATH");
	return (0);
}
