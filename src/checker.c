#include "lem_in.h"

int check_for_duplicates(t_room *rooms)
{
	char 	*name;
	t_room	*tmp;

	while (rooms != NULL)
	{
		name = rooms->name;
		tmp = rooms->next;
		while (tmp != NULL)
		{
			if (ft_strequ(name, tmp->name) == true)
			{
				return (ERROR);
			}
			tmp = tmp->next;
		}
		rooms = rooms->next;
	}
}

int check_for_paths(t_room *rooms)
{
	while (rooms)
	{
		if (rooms->connection != NULL)
		{
			return (true);
		}
		rooms = rooms->next;
	}
	return (ERROR);
}

int	inputs_are_valid(t_lemin *lemin)
{
	if (lemin->nb_ants <= 0)
	{
		return (print_error("ERROR: No ants."));
	}
	if ((check_for_duplicates(lemin->room)) == ERROR)
	{
		return (print_error("ERROR: There are rooms with the same name."));
	}
	if (lemin->start == NULL)
	{
		return (print_error("ERROR: Start room doesn't exist."));
	}
	if (lemin->end == NULL)
	{
		return (print_error("ERROR: End room doesn't exist."));
	}
	if (check_for_paths(lemin->room) == ERROR)
	{
		return (print_error("ERROR: There is no way."));
	}
	//Todo: TOUT LE PARSING CHECKER
	return (true);
}