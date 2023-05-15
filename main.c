/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:18:49 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/16 01:13:28 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"
#include <stdio.h>

void my_keyhook(mlx_key_data_t keydata, void *map)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		exit(EXIT_SUCCESS); //free map etc
}


void print_matrix(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			ft_printf("%i ", map->matrix[i][j].z);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void	draw(t_map *map)
{
	int i, j;
	i = 0;
	while (i < map->height)
	{
		j = 0;

		ft_printf(" this%i\n",i);
			while (j < map->width)
			{
				if (i == map->height - 1 && j < map->width - 1)
					BresenhamLine(map->projection[i][j], map->projection[i][j+1], map->image);
				else if (j == map->width - 1 && i < map->height - 1)
					BresenhamLine(map->projection[i][j], map->projection[i+1][j], map->image);
				else if (i != map->height -1 && j != map->width -1)
				{
					BresenhamLine(map->projection[i][j], map->projection[i][j+1], map->image);
					BresenhamLine(map->projection[i][j], map->projection[i+1][j], map->image);
				}
				j++;
			}
		i++;
	}
}

void	isometric(t_map **map)
{
	int	i;
	int	j;
	double theta;

	theta = 30 * 3.14 / 180 ;
	i = 0;
	while (i < (*map)->height)
	{
		j = 0;
		while (j < (*map)->width)
		{
			(*map)->projection[i][j].color = (*map)->matrix[i][j].color;
			(*map)->projection[i][j].x = (((*map)->matrix[i][j].x * cos(theta) - (*map)->matrix[i][j].y * cos(theta))) + 700;
			(*map)->projection[i][j].y = (*map)->matrix[i][j].x * sin(theta) + (*map)->matrix[i][j].y * sin(theta) - (*map)->matrix[i][j].z;
			j++;
		}
		i++;
	}
	printf("%i %i ", i ,j);
}
int32_t	main(int argc, char **argv)
{
	t_map	*map;
	allocate_map(&map);
	get_size(argv[1], &map);
	read_map(argv[1], &map);
	isometric(&map);
	draw(map);
	mlx_key_hook(map->window, &my_keyhook, &map);
	mlx_loop(map->window);
	mlx_terminate(map->window);
	return (EXIT_SUCCESS);
}
