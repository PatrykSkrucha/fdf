/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 19:00:49 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/24 19:04:15 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

static t_bresenham	*allocate_container(void)
{
	t_bresenham	*box;

	box = malloc(sizeof(t_bresenham));
	if (!box)
		return (NULL);
	box->x = 0;
	box->y = 0;
	box->ai = 0;
	box->bi = 0;
	box->length = 0;
	box->x_length = 0;
	box->xi = 0;
	box->y_length = 0;
	box->yi = 0;
	return (box);
}

int	allocate_map(t_map **map)
{
	*map = malloc(sizeof(t_map));
	if (!map)
		return (1);
	(*map)->width = -1;
	(*map)->height = 0;
	(*map)->ratio = 0;
	(*map)->shift_x = 0;
	(*map)->shift_y = 0;
	(*map)->matrix = NULL;
	(*map)->iso = NULL;
	(*map)->coord_temp = malloc(sizeof(t_coordinate));
	(*map)->algo_temp = allocate_container();
	(*map)->window = mlx_init(WIDTH, HEIGHT, "fdf", true);
	(*map)->image = mlx_new_image((*map)->window, WIDTH, HEIGHT);
	if (!(*map)->image
		|| (mlx_image_to_window((*map)->window, (*map)->image, 0, 0) < 0)
		|| !(*map)->coord_temp || !(*map)->algo_temp)
		return (1);
	return (0);
}

void	allocate_matrix(t_map *map)
{
	int	i;

	i = 0;
	map->matrix = ft_calloc(map->height, sizeof(t_coordinate *));
	map->iso = ft_calloc(map->height, sizeof(t_coordinate *));
	if (!map->iso || !map->matrix)
		free_and_exit(map, 1);
	while (i < map->height)
	{
		map->matrix[i] = ft_calloc(map->width, sizeof(t_coordinate));
		if (!map->matrix[i])
			free_and_exit(map, 1);
		i++;
	}
	i = 0;
	while (i < map->height)
	{
		map->iso[i] = ft_calloc(map->width, sizeof(t_coordinate));
		if (!map->iso[i])
			free_and_exit(map, 1);
		i++;
	}
}
