/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:28:50 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/23 16:52:43 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

static void	free_iso(t_map *map)
{
	int	i;

	i = map->height - 1;
	if (map->iso)
	{
		while (i >= 0)
		{
			if (map->iso[i])
				free(map->iso[i]);
			i--;
		}
		free(map->iso);
	}
}

static void	free_matrix(t_map *map)
{
	int	i;

	i = 0;
	if (map->matrix)
	{
		while (i >= 0)
		{
			if (map->matrix[i])
				free(map->matrix[i]);
			i--;
		}
		free(map->matrix);
	}
}

void	free_and_exit(t_map *map, int i)
{
	free_iso(map);
	free_matrix(map);
	free(map);
	if (map->window)
		mlx_terminate(map->window);
	if (!i)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}
