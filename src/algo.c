#include "lem_in.h"

int assigns_room_weights(t_room *room, int weight)
{
	t_room **connections;
	size_t i;

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
			print_error("ERROR: [Start] is not connected to [End].");
			return (NULL);
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