#include "lem_in.h"

static int parse_room(t_lemin *lemin, const char *line, enum e_type room_type)
{
	char **array;
	int ret;

	if (!line || !(array = ft_strsplit(line, ' ')) ||
		!array[0] || !array[1] || !array[2] ||
		array[0][0] == '#' || array[0][0] == 'L')
	{
		free_string_array(array);
		return (ERROR);
	}
	ret = create_room(lemin, array[0], room_type);
	free_string_array(array);
	return (ret);
}

static int parse_lines(t_lemin *lemin, char *line)
{
	t_room *room_a;
	t_room *room_b;
	char **array;

	if (line == NULL || (array = ft_strsplit(line, '-')) == NULL ||
		array[0] == NULL || array[1] == NULL)
	{
		return (ERROR);
	}
	room_a = get_room(array[0], lemin);
	room_b = get_room(array[1], lemin);
	free_string_array(array);
	return (connect_rooms(room_a, room_b));
}

static int parse_ants(const char *ants)
{
	size_t i;
	intmax_t nb_ants;

	nb_ants = ERROR;
	if (ants)
	{
		i = 0;
		while (ft_isdigit(ants[i]))
		{
			i++;
		}
		if (ants[i] == '\0')
		{
			nb_ants = ft_atol(ants, BASE_DECIMAL);
		}
	}
	return (nb_ants > INT_MAX ? ERROR : (int) nb_ants);
}

/*
**		Parse all lines read on standard input.
*/

static int parse_inputs(t_lemin *lemin, char **stdin)
{
	int ret;
	size_t i;

	i = 0;
	ret = 0;
	if ((lemin->nb_ants = parse_ants(stdin[0])) == ERROR)
	{
		return (print_error("ERROR: Ants parsing failed."));
	}
	while (stdin[++i] != NULL)
	{
		if (ft_strequ(stdin[i], "##start"))
		{
			ret = parse_room(lemin, stdin[++i], START);
		}
		else if (ft_strequ(stdin[i], "##end"))
		{
			ret = parse_room(lemin, stdin[++i], END);
		}
		else if (stdin[i][0] != '#' && !ft_strchr(stdin[i], '-'))
		{
			ret = parse_room(lemin, stdin[i], NORMAL);
		}
		else if (stdin[i][0] != '#' && ft_strchr(stdin[i], '-'))
		{
			ret = parse_lines(lemin, stdin[i]);
		}
		if (ret == ERROR)
		{
			return (print_error("ERROR: Parsing failed, please make sure that the graph is valid."));
		}
	}
	return (inputs_are_valid(lemin));
}

/*
**		Read the graph on the standard input.
*/

int read_inputs(t_lemin *lemin)
{
	int ret;
	size_t i;
	char *line;
	size_t buffer;

	i = 0;
	buffer = STDIN_BUFF_SIZE;
	if (buffer <= 0)
	{
		return (ERROR);
	}
	lemin->stdin = ft_memalloc(sizeof(char *) * buffer);
	while (get_next_line(STDIN_FILENO, &line))
	{
		if (i == buffer - 1)
		{
			if ((lemin->stdin = ft_realloc(lemin->stdin, buffer * 2)) == false)
			{
				return (ERROR);
			}
			buffer *= 2;
		}
		lemin->stdin[i] = line;
		i++;
	}
	ret = parse_inputs(lemin, lemin->stdin);
	return (ret);
}
