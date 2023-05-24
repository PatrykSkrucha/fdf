/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:19:01 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/24 16:28:33 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

void	read_coord(t_map *map, int z, t_coordinate *temp, long color)
{
	t_coordinate	*point;

	point = malloc(sizeof(t_coordinate));
	point->x = temp->x * map->ratio;
	point->y = temp->y * map->ratio;
	point->z = z;
	point->color = color;
	map->matrix[temp->y][temp->x] = *point;
}



static int	fill_map(t_map *map, char **str, t_coordinate *temp)
{
	if (!str)
		free_and_exit(map, 1);
	temp->x = 0;
	while (str[temp->x] && str[temp->x][0] != '\n')
	{
		process_input(str, map, temp);
		temp->x++;
	}
	return (0);
}

void	read_map(char *path, t_map *map)
{
	int				fd;
	char			*line;
	char			**str;

	map->coord_temp->y = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		free_and_exit(map, 1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		str = ft_split(line, ' ');
		free(line);
		fill_map(map, str, map->coord_temp);
		free_splitted(str);
		map->coord_temp->y++;
	}
	close(fd);
}
