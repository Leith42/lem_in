#include "lem_in.h"

static int new_connection(t_room *room_1, t_room *room_2)
{
	size_t i;
	t_room **new_connection;

	i = 0;
	while (room_1->connection[i] != NULL)
		i++;
	if ((new_connection = ft_memalloc(((sizeof(t_room) * (i + 1)) + sizeof(NULL)))) == NULL)
		return (ERROR);
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

int connect_rooms(t_room *room_a, t_room *room_b)
{
	if (room_a == NULL || room_b == NULL)
	{
		return (print_error("ERROR: Connections are invalid."));
	}
	if (room_a->connection == NULL)
	{
		if ((room_a->connection = ft_memalloc(sizeof(t_room) + sizeof(NULL))) == NULL)
			return (ERROR);
		room_a->connection[0] = room_b;
	}
	else
		new_connection(room_a, room_b);
	if (room_b->connection == NULL)
	{
		if ((room_b->connection = ft_memalloc(sizeof(t_room) + sizeof(NULL))) == NULL)
			return (ERROR);
		room_b->connection[0] = room_a;
	}
	else
		new_connection(room_b, room_a);
	return (true);
}

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

int create_room(t_lemin *lemin, const char *line, enum e_type room_type)
{
	t_room *tmp;
	t_room *room;

	if ((room = ft_memalloc(sizeof(t_room))) == NULL || (room->name = ft_strdup(line)) == NULL)
		return (ERROR);
	room->type = room_type;
	if (room->type == END)
	{
		if (lemin->end != NULL)
			return (ERROR);
		lemin->end = room;
	}
	else
		room->weight = -1;
	if (room->type == START)
	{
		room->ants = lemin->nb_ants;
		if (lemin->start != NULL)
			return (ERROR);
		lemin->start = room;
	}
	if ((tmp = lemin->room) == NULL)
		lemin->room = room;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = room;
	}
	return (true);
}