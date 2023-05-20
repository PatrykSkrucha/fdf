/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:18:49 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/20 02:38:51 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"
#include <stdio.h>

void move_hook(mlx_key_data_t keydata, void *map)
{
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		shift_up(map);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		shift_left(map);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		shift_down((t_map *)map);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		shift_right(map);
		
}
void exit_hook(mlx_key_data_t keydata, void *map)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		exit(EXIT_SUCCESS); //free map etc
	else
		move_hook(keydata, map);
}



void print_matrix(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			ft_printf("%i ", map->matrix[i][j].z);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void	draw(t_map *map)
{
	int i, j;
	i = 0;
	ft_memset(map->image->pixels, 255, map->image->width * map->image->height * sizeof(int));
	while (i < map->height)
	{
		j = 0;

		
			while (j < map->width)
			{
				if (i == map->height - 1 && j < map->width - 1)
					BresenhamLine(map->projection[i][j], map->projection[i][j+1], map->image);
				else if (j == map->width - 1 && i < map->height - 1)
					BresenhamLine(map->projection[i][j], map->projection[i+1][j], map->image);
				else if (i != map->height -1 && j != map->width -1)
				{
					//ft_printf("here?\n");
					//ft_printf(" this x%i y: %i\n",map->projection[i][j].x, map->projection[i][j].y);
					BresenhamLine(map->projection[i][j], map->projection[i][j+1], map->image);
					//ft_printf("or not\n");
					BresenhamLine(map->projection[i][j], map->projection[i+1][j], map->image);
				}
				j++;
			}
		i++;
	}
}

void	isometric(t_map **map)
{
	int	i;
	int	j;
	double theta;

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
	printf("%i %i ", i ,j);
}

int shift_mapx(t_map **map)
{
	int min;
	int i;
	int j;

	i = 0;
	min = 0;
	while (i < (*map)->height)
	{
		j = 0;
		while (j < (*map)->width)
		{
			if ((*map)->projection[i][j].x < min)
				min = (*map)->projection[i][j].x;
			j++;
		}
		i++;
	}
	return (min);
}
int shift_mapy(t_map **map)
{
	int min;
	int i;
	int j;

	i = 0;
	min = 0;
	while (i < (*map)->height)
	{
		j = 0;
		while (j < (*map)->width)
		{
			if ((*map)->projection[i][j].y < min)
				min = (*map)->projection[i][j].y;
			j++;
		}
		i++;
	}
	return (min);
}

void shift_map(t_map **map, int shifty, int shiftx)
{
	int i;
	int j;

	i = 0;
	while (i < (*map)->height)
	{
		j = 0;
		while (j < (*map)->width)
		{
			(*map)->projection[i][j].x -= shiftx;
			(*map)->projection[i][j].y -= shifty;
			j++;
		}
		i++;
	}
}

void	center_map(t_map **map)
{
	int	centerx = (WIDTH - (*map)->projection[0][(*map)->width - 1].x) / 2;
	int centery = (HEIGHT - (*map)->projection[(*map)->height - 1][(*map)->width - 1].y) / 2;
	int i;
	int j;

	i = 0;
	while (i < (*map)->height)
	{
		j = 0;
		while (j < (*map)->width)
		{
			(*map)->projection[i][j].x += centerx;
			(*map)->projection[i][j].y += centery;
			j++;
		}
		i++;
	}
	//ft_printf("x: %i y: %i\n", centerx, centery);
	
}

int32_t	main(int argc, char **argv)
{
	t_map	*map;
	int shiftx;
	int shifty;

	//printf("tu: %li", color_picker(4, 900, 1000 - 800));
	allocate_map(&map);
	get_size(argv[1], &map);
	read_map(argv[1], &map);
	isometric(&map);
	shiftx = shift_mapx(&map);
	shifty = shift_mapy(&map);
	//ft_printf("shift x:%i shift y:%i ", shiftx, shifty);
	shift_map(&map, shifty, shiftx);
	center_map(&map);
	draw(map);
	mlx_key_hook(map->window, &exit_hook, map);
	//mlx_key_hook(map->window, &move_hook, &map);
	mlx_loop(map->window);
	mlx_terminate(map->window);
	return (EXIT_SUCCESS);
}

//#define BPP sizeof(int32_t)

//int32_t	main(void)
//{
//    // Init mlx with a canvas size of 256x256 and the ability to resize the window.
//    mlx_t* mlx = mlx_init(256, 256, "MLX42", true);
    
//    if (!mlx) exit(EXIT_FAILURE);

//    // Create a 128x128 image.
//    mlx_image_t* img = mlx_new_image(mlx, 255, 255);

//    // Set the channels of each pixel in our image to the maximum byte value of 255. 
//    memset(img->pixels, 255, img->width * img->height * BPP);

//    // Draw the image at coordinate (0, 0).
//    mlx_image_to_window(mlx, img, 0, 0);

//    // Run the main loop and terminate on quit.  
//    mlx_loop(mlx);
//    mlx_terminate(mlx);

//    return (EXIT_SUCCESS);
//}

