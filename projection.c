/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:02:04 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/21 14:09:07 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

void	isometric(t_map **map)
{
	int		i;
	int		j;
	double	theta;

	theta = 30 * 3.14 / 180 ;
	i = 0;
	while (i < (*map)->height)
	{
		j = 0;
		while (j < (*map)->width)
		{
			(*map)->projection[i][j].color = (*map)->matrix[i][j].color;
			(*map)->projection[i][j].x = (((*map)->matrix[i][j].x * cos(theta) - (*map)->matrix[i][j].y * cos(theta)));
			(*map)->projection[i][j].y = (*map)->matrix[i][j].x * sin(theta) + (*map)->matrix[i][j].y * sin(theta) - (*map)->matrix[i][j].z;
			j++;
		}
		i++;
	}
}
