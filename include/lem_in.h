#ifndef LEM_IN_H
#define LEM_IN_H

# include "libft.h"
# include <limits.h>
# include <stdint.h>

# define STDIN_BUFF_SIZE 2048;

enum e_type
{
	START, NORMAL, END
};

typedef struct	s_room
{
	char 			*name;
	int				ants;
	int 			iterations;
	int 			head;
	int 			weight;
	enum e_type		type;
	struct s_room	**connection;
	struct s_room	*next;
}				t_room;

typedef struct	s_lemin
{
	int				nb_ants;
	char			**stdin;
	size_t 			laps;
	t_room			*room;
	t_room			*start;
	t_room			*end;
}				t_lemin;

int read_inputs(t_lemin *);
int create_room(t_lemin *, const char *line, enum e_type room);
int free_string_array(char **array);
t_room	*get_room(char *name, t_lemin *);
int connect_rooms(t_room *room_a, t_room *room_b);
void	free_lemin(t_lemin *lemin, t_room *path);
int	inputs_are_valid(t_lemin *lemin);
int print_error(const char *error);
int assigns_room_weights(t_room *room, int weight);
t_room	*get_shortest_path(t_lemin *lemin);
char **ft_realloc(char **array, size_t size);
void print_stdin(char **stdin);

#endif
