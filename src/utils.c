#include "lem_in.h"

void	free_string_array(char **array)
{
	size_t i;

	if (array)
	{
		i = 0;
		while (array[i] != NULL)
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

void	free_lemin(t_lemin *lemin, t_room *path)
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

int		print_error(const char *error)
{
	ft_putendl_fd(error, STDERR_FILENO);
	return (ERROR);
}

char	**ft_realloc(char **array, size_t size)
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

void	free_rooms(t_room *r)
{
	t_room *tmp;

	while (r)
	{
		tmp = r;
		r = r->next;
		free(tmp);
	}
}
