#include "include/so_long.h"

int	**read_map(char *path)
{
	int		fd;
	char	*line;
	int		**map;

	fd = open(path, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
	}
	return (map);
}