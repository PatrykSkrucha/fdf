#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>

typedef struct s_grid
{
    int             x;
    int             y;
    int             z;
	int				last;
    struct s_grid   *next;
}   t_grid;

t_grid *read_map(char *path);
void print_list(t_grid *grid);
void	add_back(t_grid **lst, t_grid *new);
int	lst_size(t_grid *grid);

#endif