#ifndef	FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
#include <stdio.h>
# ifdef __APPLE__				
#  define WIDTH 2400			// horizonal pixels on Mac
#  define HEIGHT 1350			// vertical pixels on Mac
# elif defined(__linux__)	
#  define WIDTH 1500				// horizonal pixels on Linux
#  define HEIGHT 850			// vertical pixels on Linux
# endif

typedef struct isometric
{
	int		x;
	int		y;
} t_isometric;

typedef struct coordinate
{
	int 	x;
	int		y;
	int		z;
	long	color;
} t_coordinate;

typedef struct map
{
	int				width;
	int				height;
	mlx_t			*window;
	t_coordinate	**matrix;
	t_isometric		**projection;
	mlx_image_t		*image;
} t_map;

void	read_map(char *path, t_map **map);

#endif