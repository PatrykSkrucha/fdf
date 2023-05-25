/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:28:50 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/24 15:58:29 by pskrucha         ###   ########.fr       */
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

	i = map->height - 1;
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
	if (map)
	{
		if (map->coord_temp)
			free(map->coord_temp);
		if (map->algo_temp)
			free(map->algo_temp);
		free_iso(map);
		free_matrix(map);
		if (map->window)
			mlx_terminate(map->window);
		free(map);
	}
	if (!i)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}

void	free_line_and_exit(t_map *map, char *line)
{
	free(line);
	free_and_exit(map, 1);
}

void	invalid_map_exit(t_map *map, char **splitted, char *line)
{
	free_splitted(splitted);
	ft_free_str(line);
	ft_putstr_fd("Invalid map.\n", STDERR_FILENO);
	free_and_exit(map, 1);
}
