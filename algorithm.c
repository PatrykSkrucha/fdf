/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:18:55 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/20 03:53:57 by pskrucha         ###   ########.fr       */
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


void BresenhamLine(t_isometric start, t_isometric stop, mlx_image_t* img)
 {
	long color = stop.color;
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
	//ft_printf("nic x: %i y: %i\n", x,y);
	mlx_put_pixel(img, x, y, color);
	//ft_printf("here\n");
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
			//ft_printf("nic x: %i y: %i\n", x,y);
			mlx_put_pixel(img, x, y, color);
			//ft_printf("here\n");
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
			//ft_printf("nic x: %i y: %i\n", x,y);
			mlx_put_pixel(img, x, y, color);
			//ft_printf("here\n");
		}
	}
}