#include <stdio.h>

extern char **environ;

int main(void)
{
	unsigned int i = 0;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return (0);
}
