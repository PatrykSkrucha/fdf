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

void	read_map(char *path, t_map **map)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		
		free(line);
	}
}