#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_grid
{
    int value;
    struct s_grid   *right;
    struct s_grid   *left;
    struct s_grid   *top;
    struct s_grid   *bottom;
}   t_grid;

#endif