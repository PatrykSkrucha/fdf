/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_positioning.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:00:39 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/22 20:35:36 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

void	find_shift_x(t_map **map)
{
	int	shift_x;
	int	i;
	int	j;

	i = 0;
	shift_x = 0;
	while (i < (*map)->height)
	{
		j = 0;
		while (j < (*map)->width)
		{
			if ((*map)->iso[i][j].x < shift_x)
				shift_x = (*map)->iso[i][j].x;
			j++;
		}
		i++;
	}
	(*map)->shift_x = shift_x;
}

void	find_shift_y(t_map **map)
{
	int	shift_y;
	int	i;
	int	j;

	i = 0;
	shift_y = 0;
	while (i < (*map)->height)
	{
		j = 0;
		while (j < (*map)->width)
		{
			if ((*map)->iso[i][j].y < shift_y)
				shift_y = (*map)->iso[i][j].y;
			j++;
		}
		i++;
	}
	(*map)->shift_y = shift_y;
}

void	shift__to_the_edge(t_map **map)
{
	int	i;
	int	j;

	i = 0;
	while (i < (*map)->height)
	{
		j = 0;
		while (j < (*map)->width)
		{
			(*map)->iso[i][j].x -= (*map)->shift_x;
			(*map)->iso[i][j].y -= (*map)->shift_y;
			j++;
		}
		i++;
	}
}

void	center_map(t_map **map)
{
	int	center_x;
	int	center_y;
	int	i;
	int	j;

	center_y = (HEIGHT
			- (*map)->iso[(*map)->height - 1][(*map)->width - 1].y) / 2;
	center_x = (WIDTH - (*map)->iso[0][(*map)->width - 1].x) / 2;
	i = 0;
	while (i < (*map)->height)
	{
		j = 0;
		while (j < (*map)->width)
		{
			(*map)->iso[i][j].x += center_x;
			(*map)->iso[i][j].y += center_y;
			j++;
		}
		i++;
	}
}
