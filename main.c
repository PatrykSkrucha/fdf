/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:18:49 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/22 17:29:41 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"
#include <stdio.h>


void	draw(t_map *map)
{
	int i, j;
	i = 0;
	ft_memset(map->image->pixels, 255, map->image->width * map->image->height * sizeof(int));
	while (i < map->height)
	{
		j = 0;
			while (j < map->width)
			{
				if (i == map->height - 1 && j < map->width - 1)
					bresenham(map->projection[i][j], map->projection[i][j+1], map->image);
				else if (j == map->width - 1 && i < map->height - 1)
					bresenham(map->projection[i][j], map->projection[i+1][j], map->image);
				else if (i != map->height -1 && j != map->width -1)
				{
					ft_printf("here?\n");
					ft_printf(" this x%i y: %i\n",map->projection[i][j].x, map->projection[i][j].y);
					bresenham(map->projection[i][j], map->projection[i][j+1], map->image);
					ft_printf("or not\n");
					bresenham(map->projection[i][j], map->projection[i+1][j], map->image);
				}
				j++;
			}
		i++;
	}
}


int32_t	main(int argc, char **argv)
{
	t_map	*map;

	allocate_map(&map);
	get_size(argv[1], &map);
	read_map(argv[1], &map);
	isometric(&map);
	find_shift_x(&map);
	find_shift_y(&map);

	shift__to_the_edge(&map);
	center_map(&map);
	draw(map);
	mlx_key_hook(map->window, &exit_hook, map);
	mlx_loop(map->window);
	mlx_terminate(map->window);
	return (EXIT_SUCCESS);
}

