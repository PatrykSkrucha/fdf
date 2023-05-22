/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:18:49 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/22 20:33:41 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"
#include <stdio.h>

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
