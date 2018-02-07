#include "lem_in.h"

/*
**		Assign a weight to all possible rooms.
**		Here the weight corresponds to the number of rooms that must be traveled to reach the final room.
*/

int assigns_room_weights(t_room *room, int weight)
{
	t_room	**connections;
	size_t	i;

	i = 0;
	if (room != NULL)
	{
		if ((connections = room->connection) == NULL)
			return (ERROR);
		while (connections[i] != NULL)
		{
			if (connections[i]->weight == -1 || room->connection[i]->weight > weight + 1)
			{
				connections[i]->weight = weight + 1;
				assigns_room_weights(connections[i], weight + 1);
			}
			i++;
		}
	}
	return (true);
}

/*
**		Gets the neighboring room with the smallest weight.
**		The smaller the weight, the fewer rooms to cross.
*/

t_room *get_best_connection(t_room *room)
{
	t_room *closest;
	int i = 0;
	int weight;

	weight = room->weight;
	closest = NULL;
	while (room->connection[i] != NULL)
	{
		if (room->connection[i]->weight < weight)
		{
			closest = room->connection[i];
			weight = closest->weight;
		}
		i++;
	}
	return (closest);
}

/*
**		Returns a list of rooms corresponding to the shortest path.
*/

t_room *get_shortest_path(t_lemin *lemin)
{
	t_room *shortest_path;
	t_room *first_room;
	t_room *room;

	room = lemin->start;
	if ((shortest_path = ft_memalloc(sizeof(t_room))) == NULL)
		return (NULL);
	shortest_path->name = room->name;
	first_room = shortest_path;
	while (room->type != END)
	{
		if ((room = get_best_connection(room)) == NULL)
		{
			print_error("ERROR: [Start] and [End] are not connected.");
			free_rooms(first_room);
			return NULL;
		}
		if ((shortest_path->next = ft_memalloc(sizeof(t_room))) == NULL)
			return (NULL);
		shortest_path = shortest_path->next;
		shortest_path->name = room->name;
		shortest_path->type = room->type;
	}
	shortest_path = first_room;
	return (shortest_path);
}

/*
**		Displays the journey of ants traveling the shortest way from [START] to [END].
*/

void	print_ants(t_lemin *lemin, t_room *path)
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
