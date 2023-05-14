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
	
	point = malloc(sizeof(t_coordinate));
	point->x = x * 42 + 200;
	point->y = y * 42 + 200;
	point->z = z;
	point->color = color;
	//ft_printf("liczba: %i\n", z);
	//ft_printf("?? y:%i x: %i\n", y, x);
	//ft_printf("here?????");
	(*map)->matrix[x][y] = *point;
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
		if(ft_strchr(splitted[x], '\n'))
		{
			trimmed = ft_strtrim(splitted[x], "\n");
			//ft_printf("jest!\n");
			read_coord(map, ft_atoi(trimmed), y, x, 0);
		}
		else if (!ft_strchr(splitted[x], ','))
		{
			//ft_printf("line: >>%s<<\n", splitted[x]);
			read_coord(map, ft_atoi(splitted[x]), y, x, 0);
		}
		else 
		{
			printf("x: %i y: %i\n\n",x,y);
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