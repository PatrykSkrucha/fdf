/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:18:49 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/19 18:07:21 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"
#include <stdio.h>

void my_keyhook(mlx_key_data_t keydata, void *map)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		exit(EXIT_SUCCESS); //free map etc
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

		ft_printf(" this%i\n",i);
			while (j < map->width)
			{
				if (i == map->height - 1 && j < map->width - 1)
					BresenhamLine(map->matrix[i][j], map->matrix[i][j+1], map->image);
				else if (j == map->width - 1 && i < map->height - 1)
					BresenhamLine(map->matrix[i][j], map->matrix[i+1][j], map->image);
				else if (i != map->height -1 && j != map->width -1)
				{
					BresenhamLine(map->matrix[i][j], map->matrix[i][j+1], map->image);
					BresenhamLine(map->matrix[i][j], map->matrix[i+1][j], map->image);
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
			(*map)->projection[i][j].x = (((*map)->matrix[i][j].x * cos(theta) - (*map)->matrix[i][j].y * cos(theta))) + 700;
			(*map)->projection[i][j].y = (*map)->matrix[i][j].x * sin(theta) + (*map)->matrix[i][j].y * sin(theta) - (*map)->matrix[i][j].z;
			j++;
		}
		i++;
	}
	printf("%i %i ", i ,j);
}

int32_t	main(int argc, char **argv)
{
	t_map	*map;
	//printf("tu: %li", color_picker(4, 900, 1000 - 800));
	allocate_map(&map);
	get_size(argv[1], &map);
	read_map(argv[1], &map);
	isometric(&map);
	//ft_printf("\n\nshift y:%i\nshift x: %i\n", map->shifty, map->shiftx);
	draw(map);
	mlx_key_hook(map->window, &my_keyhook, &map);
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