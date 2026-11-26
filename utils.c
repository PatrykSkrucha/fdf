/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:40:19 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/24 19:01:12 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

void	get_ratio(t_map *map)
{
	double	diagonal;
	double	ratiox;
	double	ratioy;

	diagonal = map->width + map->height;
	ratiox = WIDTH / (diagonal * cos(30 * M_PI / 180));
	ratioy = HEIGHT / (diagonal * sin(30 * M_PI / 180));
	if (ratiox < ratioy)
		map->ratio = ratiox * 0.85;
	else
		map->ratio = ratioy * 0.85;
	if (map->ratio < 1)
		map->ratio = 1;
}

void	read_and_calc(int fd, t_map	*map)
{
	char	*line;
	char	**splitted;
	int		i;

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line && map->height == 0)
			free_and_exit(map, 1);
		if (!line)
			break ;
		splitted = ft_split(line, ' ');
		if (!splitted)
			free_line_and_exit(map, line);
		while (splitted[i] && splitted[i][0] != '\n')
			i++;
		if (map->width != -1 && map->width != i)
			invalid_map_exit(map, splitted, line);
		map->width = i;
		free_splitted(splitted);
		ft_free_str(line);
		map->height++;
		i = 0;
	}
}

void	get_size(char *path, t_map *map)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		free_and_exit(map, 1);
	read_and_calc(fd, map);
	close(fd);
	get_ratio(map);
	allocate_matrix(map);
}
