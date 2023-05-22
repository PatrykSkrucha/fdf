/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:18:55 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/22 17:13:15 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

static t_bresenham	*allocate_container(int x, int y)
{
	t_bresenham	*container;

	container = malloc(sizeof(t_bresenham));
	if (!container)
		exit(EXIT_FAILURE);
	container->x = x;
	container->y = y;
	container->ai = 0;
	container->bi = 0;
	container->length = 0;
	container->x_length = 0;
	container->xi = 0;
	container->y_length = 0;
	container->yi = 0;
	return (container);
}

static void set_direction(t_isometric start, t_isometric stop, t_bresenham *container)
{
		if (start.x < stop.x)
	{
		container->xi = 1;
		container->x_length = stop.x - start.x;
	}
	else
	{
		container->xi = -1;
		container->x_length = start.x - stop.x;
	}
	if (start.y < stop.y)
	{
		container->yi = 1;
		container->y_length = stop.y - start.y;
	}
	else
	{
		container->yi = -1;
		container->y_length = start.y - stop.y;
	}
}

#include "include/fdf.h"

void	BresenhamLine(t_isometric start, t_isometric stop, mlx_image_t *img)
{
	t_bresenham	*container;
	
	container = allocate_container(start.x, start.y);
	set_direction(start, stop, container);
	mlx_put_pixel(img, container->x, container->y, start.color);
	if (container->x_length > container->y_length)
	{
		container->ai = (container->y_length - container->x_length) * 2;
		container->bi = container->y_length * 2;
		container->length = container->bi - container->x_length;
		// pętla po kolejnych x
		while (container->x != stop.x)
		{
			//color = color_picker(container->x_length, color, start.color - stop.color);
			// test współczynnika
			if (container->length >= 0)
			{
				container->x += container->xi;
				container->y += container->yi;
				container->length += container->ai;
			}
			else
			{
				container->length += container->bi;
				container->x += container->xi;
			}
			//ft_printf("nic container->x: %i container->y: %i\n", container->x,container->y);
			mlx_put_pixel(img, container->x, container->y, start.color);
			//ft_printf("here\n");
		}
	}
	else
	{
		container->ai = ( container->x_length - container->y_length ) * 2;
		container->bi = container->x_length * 2;
		container->length = container->bi - container->y_length;
		// pętla po kolejnych container->y
		while (container->y != stop.y)
		{
			//color = color_picker(x_length, color, start.color - stop.color);
			// test współczynnika
			if (container->length >= 0)
			{
				container->x += container->xi;
				container->y += container->yi;
				container->length += container->ai;
			}
			else
			{
				container->length += container->bi;
				container->y += container->yi;
			}
			//ft_printf("nic container->x: %i container->y: %i\n", container->x,container->y);
			mlx_put_pixel(img, container->x, container->y, start.color);
			//ft_printf("here\n");
		}
	}
}
