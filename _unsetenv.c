#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern char **environ;

int init_env(void)
{
	char **env_cpy;
	int count = 0;
	int i = 0;

	while (environ[count])
	{
		count++;
	}
	env_cpy = malloc(sizeof(char *) * (count + 1));
	while (environ[i])
	{
		env_cpy[i] = strdup(environ[i]);
		i++;
	}
	env_cpy[count] = NULL;
	environ = env_cpy;
	return (0);
}

int _unsetenv(const char *name)
{
	int i = 0;
	int removed = 0;
	size_t len;

	if (!name || name[0] == '\0' || strchr(name, '='))
		return(-1);

	len = strlen(name);
	while(environ[i])
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			free(environ[i]);
			removed = 1;
		}
		if (removed)
		{
			environ[i] = environ[i + 1];
		}
		i++;
	}
	return (0);
}


int main(void)
{
	int i = 0;

	init_env();

	printf("---- ENV AVANT ----\n");
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}

	printf("\n---- SUPPRESSION DE PATH ----\n");
	_unsetenv("PATH");

	i = 0;
	printf("\n---- ENV APRES ----\n");
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}

	return (0);
}
