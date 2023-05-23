/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:40:19 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/23 16:59:56 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

void	get_ratio(t_map **map)
{
	int	ratiox;
	int	ratioy;

	ratiox = (WIDTH) / (*map)->width;
	ratioy = (HEIGHT) / (*map)->height;
	if (ratiox < ratioy)
	{
		if (ratiox > 10)
			ratiox /= 3;
		(*map)->ratio = ratiox;
	}
	else
	{
		if (ratioy > 10)
			ratioy /= 2;
		(*map)->ratio = ratioy;
	}
}

int	allocate_map(t_map **map)
{
	*map = malloc(sizeof(t_map));
	if (!map)
		return (1);
	(*map)->width = -1;
	(*map)->height = 0;
	(*map)->ratio = 0;
	(*map)->shift_x = 0;
	(*map)->shift_y = 0;
	(*map)->matrix = NULL;
	(*map)->iso = NULL;
	(*map)->window = mlx_init(WIDTH, HEIGHT, "fdf", true);
	(*map)->image = mlx_new_image((*map)->window, WIDTH, HEIGHT);
	if (!(*map)->image
		|| (mlx_image_to_window((*map)->window, (*map)->image, 0, 0) < 0))
		return (1);
	return (0);
}

void	allocate_matrix(t_map **map)
{
	int	i;

	i = 0;
	(*map)->matrix = ft_calloc((*map)->height, sizeof(t_coordinate *));
	(*map)->iso = ft_calloc((*map)->height, sizeof(t_coordinate *));
	if (!(*map)->iso || !(*map)->matrix)
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
		(*map)->iso[i] = ft_calloc((*map)->width, sizeof(t_coordinate));
		if (!(*map)->iso[i] && ft_printf("memory allocation problem"))
			exit(EXIT_FAILURE);
		i++;
	}
}

void	read_and_calc(int fd, t_map	**map)
{
	char	*line;
	char	**splitted;
	int		i;

	i = 0;
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
		if ((*map)->width != -1 && (*map)->width != i)
			exit (EXIT_FAILURE);
		(*map)->width = i;
		free_splitted(splitted);
		free(line);
		(*map)->height++;
		i = 0;
	}
}

void	get_size(char *path, t_map **map)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (read(fd, 0, 0) < 0 || fd < 0)
	{
		ft_putstr_fd("Incorrect path to the file\n", 2);
		exit (EXIT_FAILURE);
	}
	read_and_calc(fd, map);
	close(fd);
	get_ratio(map);
	allocate_matrix(map);
}
