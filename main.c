/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:18:49 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/24 19:23:21 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

int32_t	main(int argc, char **argv)
{
	t_map	*map;

	if (allocate_map(&map))
		free_and_exit(map, 0);
	get_size(argv[1], map);
	read_map(argv[1], map);
	isometric(map);
	center_map(map);
	draw(map);
	mlx_key_hook(map->window, &key_hook, map);
	mlx_close_hook(map->window, &close_app, map);
	mlx_loop(map->window);
	mlx_terminate(map->window);
	return (EXIT_SUCCESS);
}
