#include "lem_in.h"

int free_string_array(char **array)
{
	size_t i;

	if (array == NULL)
	{
		return (false);
	}
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void free_lemin(t_lemin *lemin, t_room *path)
{
	t_room *tmp;

	if (lemin)
	{
		while (lemin->room)
		{
			ft_strdel(&(lemin->room)->name);
			if (lemin->room->connection)
			{
				free(lemin->room->connection);
			}
			tmp = lemin->room;
			lemin->room = lemin->room->next;
			free(tmp);
		}
		free_string_array(lemin->stdin);
		free(lemin);
	}
	while (path)
	{
		tmp = path;
		path = path->next;
		free(tmp);
	}
}

int print_error(const char *error)
{
	ft_putendl_fd(error, STDERR_FILENO);
	return (ERROR);
}

void print_stdin(char **stdin)
{
	size_t i;

	i = 0;
	while (stdin[i])
	{
		ft_putendl(stdin[i]);
		i++;
	}
}

char **ft_realloc(char **array, size_t size)
{
	char **new;
	size_t i;

	if ((array == NULL) || (new = ft_memalloc(sizeof(char *) * size)) == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (array[i] != NULL)
	{
		new[i] = array[i];
		i++;
	}
	free(array);
	return (new);
}