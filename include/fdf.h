#ifndef	FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
#include <stdio.h>
#include <math.h>
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
	long	color;
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
	int				ratio;
	int				shifty;
	int				shiftx;
	t_coordinate	**matrix;
	t_isometric		**projection;
	mlx_t			*window;
	mlx_image_t		*image;
} t_map;

void	read_map(char *path, t_map **map);
void	allocate_map(t_map **map);
void	allocate_matrix(t_map **map);
void	get_size(char *path, t_map **map);
void	get_ratio(t_map **map);
void BresenhamLine(t_isometric x1, t_isometric x2, mlx_image_t* img);
void	isometric(t_map **map);
void	draw(t_map *map);
void shift_down(t_map *map);
void shift_up(t_map *map);
void shift_right(t_map *map);
void shift_left(t_map *map);

#endif