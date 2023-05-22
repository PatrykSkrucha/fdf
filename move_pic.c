/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_pic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:50:30 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/22 20:37:02 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "include/fdf.h"

void	shift_down(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			map->iso[i][j].y += 100;
			j++;
		}
		i++;
	}
	draw(map);
}

void	shift_up(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	if (map->iso[0][0].y - 100 > 0)
	{	
		while (i < map->height)
		{
			j = 0;
			while (j < map->width)
			{
				map->iso[i][j].y -= 100;
				j++;
			}
			i++;
		}
		draw(map);
	}
}

void	shift_right(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			map->iso[i][j].x += 100;
			j++;
		}
		i++;
	}
	draw(map);
}

void	shift_left(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			map->iso[i][j].x -= 100;
			j++;
		}
		i++;
	}
	draw(map);
}
