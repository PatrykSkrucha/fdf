/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:18:49 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/21 16:10:14 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"
#include <stdio.h>


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
	mlx_scroll_hook(map->window, &zoom_hook, map);
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

