/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:11:40 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/22 17:29:34 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# ifdef __APPLE__				
#  define WIDTH 2400			// horizonal pixels on Mac
#  define HEIGHT 1350			// vertical pixels on Mac
# elif defined(__linux__)	
#  define WIDTH 1500				// horizonal pixels on Linux
#  define HEIGHT 850			// vertical pixels on Linux
# endif

typedef struct bresenham
{
	int	length;
	int	x_length;
	int	y_length;
	int	ai;
	int	bi;
	int	xi;
	int	yi;
	int	x;
	int	y;
}	t_bresenham;

typedef struct iso
{
	int		x;
	int		y;
	long	color;
}	t_iso;

typedef struct coordinate
{
	int		x;
	int		y;
	int		z;
	long	color;
}	t_coordinate;

typedef struct map
{
	int				width;
	int				height;
	int				ratio;
	int				shift_y;
	int				shift_x;
	t_coordinate	**matrix;
	t_iso			**projection;
	mlx_t			*window;
	mlx_image_t		*image;
}	t_map;

void	read_map(char *path, t_map **map);
void	allocate_map(t_map **map);
void	allocate_matrix(t_map **map);
void	get_size(char *path, t_map **map);
void	get_ratio(t_map **map);
void	bresenham(t_iso x1, t_iso x2, mlx_image_t *img);
void	isometric(t_map **map);
void	draw(t_map *map);
void	shift_down(t_map *map);
void	shift_up(t_map *map);
void	shift_right(t_map *map);
void	shift_left(t_map *map);
void	find_shift_x(t_map **map);
void	find_shift_y(t_map **map);
void	shift__to_the_edge(t_map **map);
void	center_map(t_map **map);
void	zoom_hook(double xdelta, double ydelta, void *map);
void	exit_hook(mlx_key_data_t keydata, void *map);

#endif