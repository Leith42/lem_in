#include "lem_in.h"

void	debug(t_lemin *lemin)
{
	size_t i = 0;
	t_room *tmp;

	tmp = lemin->room;
	ft_printf("{GREEN}nb_ants:{EOC}\n%d\n", lemin->nb_ants);
	ft_printf("{GREEN}Rooms:{EOC}\n");
	while (tmp)
	{
		i = 0;
		ft_printf("{RED}name:{EOC} %s {BLUE}weight:{EOC} %d {BLUE}connections: {EOC}", tmp->name, tmp->weight);
		while (tmp->connection && tmp->connection[i])
		{
			ft_printf("[%s] | ", tmp->connection[i]->name, tmp->connection[i]->weight);
			i++;
		}
		ft_putchar('\n');
		tmp = tmp->next;
	}
}

void	print_stdin(char **stdin)
{
	size_t i;

	i = 0;
	while (stdin[i])
	{
		ft_putendl(stdin[i]);
		i++;
	}
}

int		main(void)
{
	t_lemin *lemin;
	t_room *shortest_path;

	shortest_path = NULL;
	if ((lemin = ft_memalloc(sizeof(t_lemin))) == NULL)
	{
		perror(NULL);
		return (EXIT_FAILURE);
	}
	if (read_inputs(lemin) != ERROR)
	{
		assigns_room_weights(lemin->end, 0);
		if ((shortest_path = get_shortest_path(lemin)) != NULL)
		{
			print_stdin(lemin->stdin);
			print_ants(lemin, shortest_path);
		}
	}
	free_lemin(lemin, shortest_path);
	return (EXIT_SUCCESS);
}
