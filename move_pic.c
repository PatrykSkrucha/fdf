/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_pic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:50:30 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/20 02:46:16 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "include/fdf.h"

void shift_down(t_map *map)
{
	int i;
	int j;
	
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			map->projection[i][j].y += 100;
			//map->projection[i][j].x += 10;
			j++;
		}
		i++;
	}
	//ft_printf("b4 iso x: %i, y: %i\n", map->matrix[0][0].x, map->matrix[0][0].y);
	//isometric(&map);
	//ft_printf("iso: x: %i, y: %i\n", map->projection[0][0].x, map->projection[0][0].y);
	draw(map);
}
void shift_up(t_map *map)
{
	int i;
	int j;
	
	i = 0;
	if (map->projection[0][0].y - 100 > 0)
	{	
		while (i < map->height)
		{
			j = 0;
			while (j < map->width)
			{
				map->projection[i][j].y -= 100;
				//map->projection[i][j].x -= 100;
				j++;
			}
			i++;
		}
	//ft_printf("b4 iso x: %i, y: %i\n", map->matrix[0][0].x, map->matrix[0][0].y);
	//isometric(&map);
	//ft_printf("iso: x: %i, y: %i\n", map->projection[0][0].x, map->projection[0][0].y);
	draw(map);
	}
}
void shift_right(t_map *map)
{
	int i;
	int j;
	
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			//map->matrix[i][j].y -= 100;
			map->projection[i][j].x += 100;
			j++;
		}
		i++;
	}
	//ft_printf("b4 iso x: %i, y: %i\n", map->matrix[0][0].x, map->matrix[0][0].y);
	//isometric(&map);
	//ft_printf("iso: x: %i, y: %i\n", map->projection[0][0].x, map->projection[0][0].y);
	draw(map);
}
void shift_left(t_map *map)
{
	int i;
	int j;
	
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			//map->matrix[i][j].y += 100;
			map->projection[i][j].x -= 100;
			j++;
		}
		i++;
	}
	//ft_printf("b4 iso x: %i, y: %i\n", map->matrix[0][0].x, map->matrix[0][0].y);
	//isometric(&map);
	//ft_printf("iso: x: %i, y: %i\n", map->projection[0][0].x, map->projection[0][0].y);
	draw(map);
}
