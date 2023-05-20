/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_modification.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 03:09:31 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/20 03:56:50 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

int shift_mapx(t_map **map)
{
	int min;
	int i;
	int j;

	i = 0;
	min = 0;
	while (i < (*map)->height)
	{
		j = 0;
		while (j < (*map)->width)
		{
			if ((*map)->projection[i][j].x < min)
				min = (*map)->projection[i][j].x;
			j++;
		}
		i++;
	}
	return (min);
}
int shift_mapy(t_map **map)
{
	int min;
	int i;
	int j;

	i = 0;
	min = 0;
	while (i < (*map)->height)
	{
		j = 0;
		while (j < (*map)->width)
		{
			if ((*map)->projection[i][j].y < min)
				min = (*map)->projection[i][j].y;
			j++;
		}
		i++;
	}
	return (min);
}

void shift_map(t_map **map, int shifty, int shiftx)
{
	int i;
	int j;

	i = 0;
	while (i < (*map)->height)
	{
		j = 0;
		while (j < (*map)->width)
		{
			(*map)->projection[i][j].x -= shiftx;
			(*map)->projection[i][j].y -= shifty;
			j++;
		}
		i++;
	}
}

void	center_map(t_map **map)
{
	int	centerx = (WIDTH - (*map)->projection[0][(*map)->width - 1].x) / 2;
	int centery = (HEIGHT - (*map)->projection[(*map)->height - 1][(*map)->width - 1].y) / 2;
	int i;
	int j;

	i = 0;
	while (i < (*map)->height)
	{
		j = 0;
		while (j < (*map)->width)
		{
			(*map)->projection[i][j].x += centerx;
			(*map)->projection[i][j].y += centery;
			j++;
		}
		i++;
	}
	//ft_printf("x: %i y: %i\n", centerx, centery);
	
}

void	zoom_in(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			map->projection[i][i].x *= 1.1;
			map->projection[i][i].y *= 1.1;
			j++;
		}
		i++;
	}
	draw(map);
}

void zoom_out(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			map->projection[i][i].x *= 0.9;
			map->projection[i][i].y *= 0.9;
			j++;
		}
		i++;
	}
	draw(map);
}