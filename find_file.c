#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

char *split_path(char *cmd)
{
	char *path = getenv("PATH");
	char *path_cpy;
	char *dir;
	char *res;
	struct stat st;

	if (!path)
		return (NULL);

	path_cpy = strdup(path);
	if (!path_cpy)
		return (NULL);

	dir = strtok(path_cpy, ":");
	while (dir)
	{
		res = malloc(strlen(dir) + strlen(cmd) + 2);
		if (!res)
		{
			free(path_cpy);
			return (NULL);
		}
		sprintf(res, "%s/%s", dir, cmd);

		if (stat(res, &st) == 0)
		{
			free(path_cpy);
			return (res);
		}
		free(res);
		dir = strtok(NULL, ":");
	}
	free(path_cpy);
	return (NULL);
}

int main(int ac, char **av)
{
	struct stat st;
	int i;
	char *res;

	if (ac < 2)
	{
		printf("Usage: %s command ...\n", av[0]);
		return (1);
	}
	for (i = 1; av[i]; i++)
	{
		if (strchr(av[i], '/'))
		{
			if (stat(av[i], &st) == 0)
				printf("%s\n", av[i]);
			else
				printf("%s: not found\n", av[i]);
		}
		else
		{
			res = split_path(av[i]);
			if (res)
			{
				printf("%s\n", res);
				free(res);
			}
			else
			{
				printf("%s: not found\n", av[i]);
			}
		}
	}
	return (0);
}
