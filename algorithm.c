/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:18:55 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/24 18:57:15 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

static t_bresenham	*allocate_container(int x, int y)
{
	t_bresenham	*box;

	box = malloc(sizeof(t_bresenham));
	if (!box)
		return (NULL);
	box->x = x;
	box->y = y;
	box->ai = 0;
	box->bi = 0;
	box->length = 0;
	box->x_length = 0;
	box->xi = 0;
	box->y_length = 0;
	box->yi = 0;
	return (box);
}

static void	set_direction(t_iso start, t_iso stop, t_bresenham *box)
{
	if (start.x < stop.x)
	{
		box->xi = 1;
		box->x_length = stop.x - start.x;
	}
	else
	{
		box->xi = -1;
		box->x_length = start.x - stop.x;
	}
	if (start.y < stop.y)
	{
		box->yi = 1;
		box->y_length = stop.y - start.y;
	}
	else
	{
		box->yi = -1;
		box->y_length = start.y - stop.y;
	}
}

static void	pick_x(t_bresenham *box, t_iso start, t_iso stop, mlx_image_t *img)
{
	box->ai = (box->y_length - box->x_length) * 2;
	box->bi = box->y_length * 2;
	box->length = box->bi - box->x_length;
	while (box->x != stop.x)
	{
		if (box->length >= 0)
		{
			box->x += box->xi;
			box->y += box->yi;
			box->length += box->ai;
		}
		else
		{
			box->length += box->bi;
			box->x += box->xi;
		}
		mlx_put_pixel(img, box->x, box->y, start.color);
	}	
}

static void	pick_y(t_bresenham *box, t_iso start, t_iso stop, mlx_image_t *img)
{
	box->ai = (box->x_length - box->y_length) * 2;
	box->bi = box->x_length * 2;
	box->length = box->bi - box->y_length;
	while (box->y != stop.y)
	{
		if (box->length >= 0)
		{
			box->x += box->xi;
			box->y += box->yi;
			box->length += box->ai;
		}
		else
		{
			box->length += box->bi;
			box->y += box->yi;
		}
		mlx_put_pixel(img, box->x, box->y, start.color);
	}
}

void	bresenham(t_iso start, t_iso stop, mlx_image_t *img)
{
	t_bresenham	*box;

	box = allocate_container(start.x, start.y);
	set_direction(start, stop, box);
	mlx_put_pixel(img, box->x, box->y, start.color);
	if (box->x_length > box->y_length)
		pick_x(box, start, stop, img);
	else
		pick_y(box, start, stop, img);
}
