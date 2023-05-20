/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:19:01 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/20 00:20:00 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

long hex_to_l(char *s)
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

void	read_coord(t_map **map, int z, int y, int x, long color)
{
	t_coordinate	*point;
	int	ratio;
	
	point = malloc(sizeof(t_coordinate));
	point->x = x * (*map)->ratio;
	point->y = y * (*map)->ratio;
	point->z = z;
	point->color = color;
	//ft_printf("x: %i y: %i z: %i\n",point->x ,point->y, point->z);
	//sleep(2);
	//ft_printf("?? x:%i y: %i\n", x, y);
	//ft_printf("here?????");
	(*map)->matrix[y][x] = *point;
}

void	fill_map(t_map **map, char **splitted, int y)
{
	int x;
	char	*trimmed;
	char	*color;
	char	**divided;
	x = 0;
	
	while (splitted[x] && splitted[x][0] != '\n')
	{
		//printf("i tu");
		if(ft_strchr(splitted[x], '\n') && !ft_strchr(splitted[x], ','))
		{
			//printf("haha\n\n");
			trimmed = ft_strtrim(splitted[x], "\n");
			//ft_printf("jest! str: >>%s<<\n", trimmed);
			read_coord(map, ft_atoi(trimmed), y, x, 0);
			free(trimmed);
		}
		else if (ft_strchr(splitted[x], '\n') && ft_strchr(splitted[x], ','))
		{
			divided = ft_split(splitted[x], ',');
			trimmed = ft_strtrim(divided[1], "\n");
			read_coord(map, ft_atoi(divided[0]), y, x, hex_to_l(trimmed));
			free_splitted(divided);
			free(trimmed);
		}
		else if (!ft_strchr(splitted[x], ','))
		{
			//printf("u??");
			//ft_printf("line: >>%s<<\n", splitted[x]);
			read_coord(map, ft_atoi(splitted[x]), y, x, 0);
			//printf("koniec uu\n");
		}
		else 
		{
			divided = ft_split(splitted[x], ',');
			read_coord(map, ft_atoi(divided[0]), y, x, hex_to_l(divided[1]));
			free_splitted(divided);
		}
		x++;
	}
}

void	read_map(char *path, t_map **map)
{
	int		fd;
	char	*line;
	char	**splitted;
	int		y;

	
	y = 0;
	fd = open(path, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		splitted = ft_split(line, ' ');
		fill_map(map, splitted, y);
		free_splitted(splitted);
		free(line);
		y++;
	}
	close(fd);
}