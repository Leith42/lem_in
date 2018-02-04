#include "lem_in.h"

void debug(t_lemin *lemin)
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

int print_ants(t_lemin *lemin, t_room *path)
{
	t_room *start;

	start = path;
	start->head = 1;
	while (lemin->end->ants < lemin->nb_ants)
	{
		while (path->type != END && path->next->head == 1)
		{
			path = path->next;
			path->iterations++;
			if (path->iterations <= lemin->nb_ants)
				ft_printf("L{RED}%d{EOC}-{GREEN}%s{EOC} ", path->iterations, path->name);
			if (path->type == END)
				lemin->end->ants++;
		}
		if (path->type != END)
		{
			path->next->head = 1;
		}
		path = start;
		lemin->laps++;
		ft_putchar('\n');
	}
	ft_printf("\n{BLUE}Total laps:{EOC} {RED}%ld{EOC}\n", --lemin->laps);
}

int main(int argc, char **argv)
{
	t_lemin *lemin;
	t_room *shortest_path;

	shortest_path = NULL;
	if ((lemin = ft_memalloc(sizeof(t_lemin))) == NULL)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
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
//	debug(lemin);
//	putchar('\n');
//	while (shortest_path)
//	{
//		puts(shortest_path->name);
//		shortest_path = shortest_path->next;
//	}

	free_lemin(lemin, shortest_path);
	return (true);
}
