/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:04:32 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/24 19:14:41 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

void	draw(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	ft_memset(map->image->pixels, 255, map->image->width
		* map->image->height * sizeof(int));
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (i == map->height - 1 && j < map->width - 1)
				bresenham(map->iso[i][j], map->iso[i][j + 1], map);
			else if (j == map->width - 1 && i < map->height - 1)
				bresenham(map->iso[i][j], map-> iso[i + 1][j], map);
			else if (i != map->height -1 && j != map->width -1)
			{
				bresenham(map->iso[i][j], map->iso[i][j + 1], map);
				bresenham(map->iso[i][j], map->iso[i + 1][j], map);
			}
			j++;
		}
		i++;
	}
}
