/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:40:19 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/16 00:33:28 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

void	allocate_map(t_map **map)
{
	*map = malloc(sizeof(t_map));
	if (!map)
		exit(EXIT_FAILURE);
	(*map)->width = 0;
	(*map)->height = 0;
	(*map)->matrix = NULL;
	(*map)->projection = NULL;
	(*map)->window = mlx_init(WIDTH, HEIGHT, "fdf", true);
	(*map)->image = mlx_new_image((*map)->window, WIDTH, HEIGHT);
	if (!(*map)->image
		|| (mlx_image_to_window((*map)->window, (*map)->image, 0, 0) < 0))
		exit(EXIT_FAILURE);
}

void	allocate_matrix(t_map **map)
{
	int	i;

	i = 0;
	(*map)->matrix = ft_calloc((*map)->height, sizeof(t_coordinate *));
	(*map)->projection = ft_calloc((*map)->height, sizeof(t_coordinate *));
	if (!(*map)->projection || !(*map)->matrix)
		exit(EXIT_FAILURE);
	while (i < (*map)->height)
	{
		(*map)->matrix[i] = ft_calloc((*map)->width, sizeof(t_coordinate));
		if (!(*map)->matrix[i] && ft_printf("memory allocation problem"))
			exit(EXIT_FAILURE);
		i++;
	}
	i = 0;
	while (i < (*map)->height)
	{
		(*map)->projection[i] = ft_calloc((*map)->width, sizeof(t_coordinate));
		if (!(*map)->projection[i] && ft_printf("memory allocation problem"))
			exit(EXIT_FAILURE);
		i++;
	}
}

void	get_size(char *path, t_map **map)
{
	int		height;
	char	**splitted;
	int		i;
	int		width;
	int		fd;
	char	*line;

	height = 0;
	width = -1;
	i = 0;
	fd = open(path, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		splitted = ft_split(line, ' ');
		if (!splitted)
			exit(EXIT_FAILURE);
		while (splitted[i] && splitted[i][0] != '\n')
			i++;
		if (width != -1)
		{
			if (width != i)
			{
				ft_printf("Incorrect map\n");
				exit (EXIT_FAILURE);
			}
		}
		else
			width = i;
		free_splitted(splitted);
		free(line);
		height++;
		i = 0;
	}
	close(fd);
	(*map)->height = height;
	(*map)->width = width;
	ft_printf("height: %i width: %i\n",(*map)->height,(*map)->width);
	allocate_matrix(map);
}
