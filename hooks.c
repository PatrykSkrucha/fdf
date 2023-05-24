/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 03:11:04 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/24 19:25:45 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

void	close_app(void *map)
{
	free_and_exit(map, 0);
}

void	move_hook(mlx_key_data_t keydata, void *map)
{
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		shift_up(map);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		shift_left(map);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		shift_down(map);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		shift_right(map);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		free_and_exit(param, 0);
	else
		move_hook(keydata, param);
}
