#include "lem_in.h"

static int new_connection(t_room *room_1, t_room *room_2)
{
	size_t i;
	t_room **new_connection;

	i = 0;
	while (room_1->connection[i] != NULL)
	{
		i++;
	}
	if ((new_connection = ft_memalloc(((sizeof(t_room) * (i + 1)) + sizeof(NULL)))) == NULL)
	{
		return (ERROR);
	}
	i = 0;
	while (room_1->connection[i] != NULL)
	{
		new_connection[i] = room_1->connection[i];
		i++;
	}
	new_connection[i] = room_2;
	free(room_1->connection);
	room_1->connection = new_connection;
	return (true);
}

/*
**		Connects the rooms bidirectionally, (A -> B) & (B -> A).
*/

int connect_rooms(t_room *room_a, t_room *room_b)
{
	if (room_a == NULL || room_b == NULL)
	{
		return (ERROR);
	}
	if (room_a->connection == NULL)
	{
		if ((room_a->connection = ft_memalloc(sizeof(t_room) + sizeof(NULL))) == NULL)
			return (ERROR);
		room_a->connection[0] = room_b;
	}
	else
	{
		new_connection(room_a, room_b);
	}
	if (room_b->connection == NULL)
	{
		if ((room_b->connection = ft_memalloc(sizeof(t_room) + sizeof(NULL))) == NULL)
			return (ERROR);
		room_b->connection[0] = room_a;
	}
	else
	{
		new_connection(room_b, room_a);
	}
	return (true);
}

/*
**		Search and return a room according to his name.
*/

t_room *get_room(char *name, t_lemin *lemin)
{
	t_room *tmp;

	if (name == NULL || lemin->room == NULL)
	{
		return (NULL);
	}
	tmp = lemin->room;
	while (tmp)
	{
		if (ft_strequ(tmp->name, name))
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int add_room_to_list(t_room *new, t_lemin *lemin)
{
	t_room *tmp;

	if (lemin->room == NULL)
	{
		lemin->room = new;
	}
	else
	{
		tmp = lemin->room;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
	}
	return (true);
}

/*
**		Create a room and add it to the list.
**		Can return an error if [START] or [END] already exist.
*/

int create_room(t_lemin *lemin, const char *line, enum e_type room_type)
{
	t_room *room;

	if ((room = ft_memalloc(sizeof(t_room))) == NULL || (room->name = ft_strdup(line)) == NULL)
		return (ERROR);
	room->type = room_type;
	if (room->type == END)
	{
		if (lemin->end)
			return (ERROR);
		lemin->end = room;
	}
	else
	{
		room->weight = -1;
	}
	if (room->type == START)
	{
		if (lemin->start)
			return (ERROR);
		room->ants = lemin->nb_ants;
		lemin->start = room;
	}
	return (add_room_to_list(room, lemin));
}
