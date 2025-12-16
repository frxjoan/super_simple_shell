#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * struct list_s - singly linked list
 * @str: string - (malloc'ed string)
 * @len: length of the string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct list_s
{
	char *str;
	struct list_s *next;
} list_t;

extern char **environ;

list_t *lister(char *path)
{
	char *line = getenv(path);
	char *line_cpy; 
	char *dir;
	list_t *nn;
	list_t *head = NULL;
	list_t *tail = NULL;

	if (!line)
		return (NULL);

	line_cpy = strdup(line);
	if (!line_cpy)
		return (NULL);

	dir = strtok(line_cpy, ":");
	while(dir)
	{
		nn = malloc(sizeof(list_t));
		if (!nn)
			break;

		nn->str = strdup(dir);
		if (!nn->str)
		{
			free(nn);
			break;
		}
		nn->next = NULL;
		if (!head)
			head = nn;
		else
			tail->next = nn;
		tail = nn;
		dir = strtok(NULL, ":");
	}
	free(line_cpy);
	return (head);
}

void free_list(list_t *head)
{
    list_t *tmp;

    while (head)
    {
        tmp = head->next;
        free(head->str);
        free(head);
        head = tmp;
    }
}

int main(void)
{
    list_t *list;
    list_t *tmp;

    list = lister("PATH");
    if (!list)
    {
        printf("PATH not found or empty\n");
        return (1);
    }

    tmp = list;
    while (tmp)
    {
        printf("%s\n", tmp->str);
        tmp = tmp->next;
    }

    free_list(list);
    return (0);
}
