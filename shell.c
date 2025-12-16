#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int count_words(char *str)
{
	int count = 0;
	int in_word = 0;

	while (*str)
	{
		if (*str != ' ' && *str != '\n' && !in_word)
		{
			count++;
			in_word = 1;
		}
		else if (*str == ' ' || *str == '\n')
			in_word = 0;
		str++;
	}
	return (count);
}

char **slicing_str(char *str)
{
	int i = 0;
	char **tokens;
	char *token;
	int words;

	words = count_words(str);
	tokens = malloc(sizeof(char *) * (words + 1));

	if (tokens == NULL)
		return (NULL);

	token = strtok(str, " \n");
	while (token)
	{
		tokens[i++] = token;
		token = strtok(NULL, " \n");
	}
	tokens[i] = NULL;
	return (tokens);
}

int main(void)
{
	char *line = NULL;
	char **argv = NULL;
	size_t size = 0;
	pid_t child_pid;

	line = NULL;
	printf("$ ");
	if (getline(&line, &size, stdin) == -1)
	{
		free(line);
		return (0);
	}

	argv = slicing_str(line);
	if (!argv || !argv[0])
	{
		free(line);
		free(argv);
		return (0);
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		free(line);
		free(argv);
		return (1);
	}
	if (child_pid == 0)
	{
		execve(argv[0], argv, NULL);
		perror("execve");
		exit (1);
	}
	else
	{
		wait(NULL);
	}
	free(argv);
	free(line);
	return (0);
}
