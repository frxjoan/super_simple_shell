#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_words(char *str)
{
	int count = 0;
	int in_word = 0;

	while (*str)
	{
		if (*str != ' ' && !in_word)
		{
			count++;
			in_word = 1;
		}
		else if (*str == ' ')
			in_word = 0;
		str++;
	}
	return (count);
}

char **slicing_str(char *str)
{
	int i = 0;
	char *copy = strdup(str);
	char **tokens;
	char *token;
	int words;

	if (!copy)
		return (NULL);

	words = count_words(copy);
	tokens = malloc(sizeof(char *) * words + 1);

	if (tokens == NULL)
	{
		free(copy);
		return (NULL);
	}

	token = strtok(copy, " ");
	while (token)
	{
		tokens[i++] = token;
		token = strtok(NULL, " ");
	}
	tokens[i] = NULL;
	return (tokens);
}

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char **argv;
    int i;

    printf("Tape une commande : ");

    read = getline(&line, &len, stdin);
    if (read == -1)
    {
        perror("getline");
        free(line);
        return 1;
    }

    if (line[read - 1] == '\n')
        line[read - 1] = '\0';

    argv = slicing_str(line);
    if (!argv)
    {
        printf("Erreur slicing_str\n");
        free(line);
        return 1;
    }

    printf("\nArguments découpés :\n");
    for (i = 0; argv[i]; i++)
        printf("argv[%d] = [%s]\n", i, argv[i]);

    free(argv);
    free(line);

    return 0;
}
