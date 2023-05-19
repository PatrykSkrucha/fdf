/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:18:55 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/19 16:45:34 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

long	color_picker(int distance, long color, long diff)
{
	long new_color;
	if (distance == 0)
		return (color);
	new_color = color - (diff / distance);
	return (new_color);
}


void BresenhamLine(t_coordinate start, t_coordinate stop, mlx_image_t* img)
 {
	long color = start.color;
	long ratio = 0;
	int d, dx, dy, ai, bi, xi, yi;
	int x = start.x, y = start.y;

	// ustalenie kierunku rysowania
	if (start.x < stop.x)
	{
		xi = 1;
		dx = stop.x - start.x;
	}
	else
	{
		xi = -1;
		dx = start.x - stop.x;
	}
	// ustalenie kierunku rysowania
	if (start.y < stop.y)
	{
		yi = 1;
		dy = stop.y - start.y;
	}
	else
	{
		yi = -1;
		dy = start.y - stop.y;
	}
	// pierwszy piksel
	mlx_put_pixel(img, x, y, color);
	// oś wiodąca OX
	if (dx > dy)
	{
		ai = (dy - dx) * 2;
		bi = dy * 2;
		d = bi - dx;
		// pętla po kolejnych x
		while (x != stop.x)
		{
			//color = color_picker(dx, color, start.color - stop.color);
			// test współczynnika
			if (d >= 0)
			{
				x += xi;
				y += yi;
				d += ai;
			}
			else
			{
				d += bi;
				x += xi;
			}
			mlx_put_pixel(img, x, y, color);
		}
	}
	// oś wiodąca OY
	else
	{
		ratio = color / (dy * 10);
		ai = ( dx - dy ) * 2;
		bi = dx * 2;
		d = bi - dy;
		// pętla po kolejnych y
		while (y != stop.y)
		{
			//color = color_picker(dx, color, start.color - stop.color);
			// test współczynnika
			if (d >= 0)
			{
				x += xi;
				y += yi;
				d += ai;
			}
			else
			{
				d += bi;
				y += yi;
			}
			mlx_put_pixel(img, x, y, color);
		}
	}
}