/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:11:40 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/24 14:56:20 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <math.h>
# ifdef __APPLE__				
#  define WIDTH 2400
#  define HEIGHT 1350
# elif defined(__linux__)	
#  define WIDTH 1500
#  define HEIGHT 850
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
	t_iso			**iso;
	mlx_t			*window;
	mlx_image_t		*image;
}	t_map;

void	read_map(char *path, t_map *map);
int		allocate_map(t_map **map);
void	allocate_matrix(t_map *map);
void	get_size(char *path, t_map *map);
void	get_ratio(t_map *map);
void	bresenham(t_iso x1, t_iso x2, mlx_image_t *img);
void	isometric(t_map **map);
void	draw(t_map *map);
void	shift_down(t_map *map);
void	shift_up(t_map *map);
void	shift_right(t_map *map);
void	shift_left(t_map *map);
void	find_shift_x(t_map *map);
void	find_shift_y(t_map *map);
void	shift_to_the_edge(t_map **map);
void	center_map(t_map **map);
void	key_hook(mlx_key_data_t keydata, void *map);
void	close_and_free(t_map *map);
void	free_and_exit(t_map *map, int i);
void	free_line_and_exit(t_map *map, char *line);
void	invalid_map_exit(t_map *map, char **splitted, char *line);

#endif