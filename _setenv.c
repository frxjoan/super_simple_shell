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

int _setenv(const char *name, const char *value, int overwrite)
{
	int i = 0;
	char **new_env;
	char *new_var;
	size_t size;

	if (!name || !value || strchr(name, '='))
		return (-1);

	size = strlen(name) + strlen(value) + 2;

	i = 0;
	while (environ[i])
	{
		if (strncmp(environ[i], name, strlen(name)) == 0
	&& environ[i][strlen(name)] == '=')
		{
			if (!overwrite)
			{
				return (0);
			}
			new_var = malloc(size);
			if (!new_var)
				return (-1);

			snprintf(new_var, size, "%s=%s", name, value);

			free(environ[i]);
			environ[i] = new_var;
			return (0);
		}
		i++;
	}
	new_env = realloc(environ, sizeof(char *) * (i + 2));
	if (!new_env)
		return (-1);
	environ = new_env;

	new_var = malloc(size);
	if (!new_var)
		return (-1);

	snprintf(new_var, size, "%s=%s", name, value);
	
	environ[i] = new_var;
	environ[i + 1] = NULL;
	return (0);
}

int main(void)
{
    char *old_path;
    unsigned int i = 0;

	init_env();

    old_path = strdup(getenv("PATH"));
    if (!old_path)
        return (1);

    printf("---- PATH AVANT ----\n");
    printf("%s\n\n", getenv("PATH"));

    _setenv("PATH", "/nothing/to/TEST", 1);

    printf("---- ENV APRES MODIF ----\n");
    while (environ[i])
    {
        printf("%s\n", environ[i]);
        i++;
    }

    _setenv("PATH", old_path, 1);
    free(old_path);

    printf("\n---- PATH RESTAURE ----\n");
    printf("%s\n", getenv("PATH"));

    return (0);
}
