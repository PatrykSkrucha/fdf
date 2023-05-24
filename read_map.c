/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:19:01 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/24 15:53:36 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

long	hex_to_l(char *s)
{
	long	res;

	res = 0;
	if (*s == '0')
		s++;
	if (*s == 'x')
		s++;
	while (*s != '\0')
	{
		if (*s >= '0' && *s <= '9')
			res = res * 16 + *s - '0';
		else
		{
			if (*s >= 'a' && *s <= 'f')
				res = res * 16 + *s - 'W';
			else if (*s >= 'A' && *s <= 'F')
				res = res * 16 + *s - '7';
			else
				return (0);
		}
	s++;
	}
	return (res);
}

static void	read_coord(t_map *map, int z, t_coordinate *temp, long color)
{
	t_coordinate	*point;

	point = malloc(sizeof(t_coordinate));
	point->x = temp->x * map->ratio;
	point->y = temp->y * map->ratio;
	point->z = z;
	point->color = color;
	map->matrix[temp->y][temp->x] = *point;
}

static void	process_input(char **str, t_map *map, t_coordinate *temp)
{
	char	*trimmed;
	char	**divided;

	if (ft_strchr(str[temp->x], '\n') && !ft_strchr(str[temp->x], ','))
	{
		trimmed = ft_strtrim(str[temp->x], "\n");
		read_coord(map, ft_atoi(trimmed), temp, 0);
		ft_free_str(trimmed);
	}
	else if (ft_strchr(str[temp->x], '\n') && ft_strchr(str[temp->x], ','))
	{
		divided = ft_split(str[temp->x], ',');
		trimmed = ft_strtrim(divided[1], "\n");
		read_coord(map, ft_atoi(divided[0]), temp, hex_to_l(trimmed));
		free_splitted(divided);
		ft_free_str(trimmed);
	}
	else if (!ft_strchr(str[temp->x], ','))
		read_coord(map, ft_atoi(str[temp->x]), temp, 0);
	else
	{
		divided = ft_split(str[temp->x], ',');
		read_coord(map, ft_atoi(divided[0]), temp, hex_to_l(divided[1]));
		free_splitted(divided);
	}
}

static void	fill_map(t_map *map, char **str, t_coordinate *temp)
{
	if (!str)
	{
		free(temp);
		free_and_exit(map, 1);
	}
	temp->x = 0;
	while (str[temp->x] && str[temp->x][0] != '\n')
	{
		process_input(str, map, temp);
		temp->x++;
	}
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
		fill_map(map, str, map->coord_temp);
		free_splitted(str);
		free(line);
		map->coord_temp->y++;
	}
	close(fd);
}
