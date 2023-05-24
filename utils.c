/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:40:19 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/24 15:58:06 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

void	get_ratio(t_map *map)
{
	int	ratiox;
	int	ratioy;

	ratiox = (WIDTH) / map->width;
	ratioy = (HEIGHT) / map->height;
	if (ratiox < ratioy)
	{
		if (ratiox > 10)
			ratiox /= 2;
		map->ratio = ratiox;
	}
	else
	{
		if (ratioy > 10)
			ratioy /= 2;
		map->ratio = ratioy;
	}
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
	(*map)->algo_temp = malloc(sizeof(t_bresenham));
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

void	read_and_calc(int fd, t_map	*map)
{
	char	*line;
	char	**splitted;
	int		i;

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line && map->height == 0)
			free_and_exit(map, 1);
		if (!line)
			break ;
		splitted = ft_split(line, ' ');
		if (!splitted)
			free_line_and_exit(map, line);
		while (splitted[i] && splitted[i][0] != '\n')
			i++;
		if (map->width != -1 && map->width != i)
			invalid_map_exit(map, splitted, line);
		map->width = i;
		free_splitted(splitted);
		ft_free_str(line);
		map->height++;
		i = 0;
	}
}

void	get_size(char *path, t_map *map)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		free_and_exit(map, 1);
	read_and_calc(fd, map);
	close(fd);
	get_ratio(map);
	allocate_matrix(map);
}
