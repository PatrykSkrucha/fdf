#include "include/fdf.h"

void print_list(t_grid *grid)
{
	while (grid)
	{
		ft_printf("%i",grid->z);
		if (grid->last)
			ft_printf("\n");
		else
			ft_printf(" ");
		grid = grid->next;
	}
}

t_grid	*new_list(int x, int y, int z, int last)
{
	t_grid	*new;

	new = (t_grid *)malloc(sizeof(t_grid));
	if (!new)
		return (NULL);
	new->x = x;
	new->y = y;
	new->z = z;
	new->last = last;
	new->next = NULL;
	return (new);
}

t_grid	*lstlast(t_grid *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	add_back(t_grid **lst, t_grid *new)
{
	t_grid	*temp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = lstlast(*lst);
	temp->next = new;
}

void	append_nodes(t_grid **grid, char *line, int x)
{
	char 	**container;
	int		y;
	
	container = ft_split(line, ' ');
	y = 0;
	if (!container)
		return ;
	while (container[y+1])
	{
		if (!container[y + 2])
			add_back(grid, new_list(x, y, ft_atoi(container[y]), 1));
		else
			add_back(grid, new_list(x, y, ft_atoi(container[y]), 0));
		y++;
	}
	y--;
	while (y >= 0)
	{
		free(container[y]);
		y--;
	}
	free(container);
}

t_grid	*read_map(char *path)
{
	int		fd;
	char	*line;
	t_grid	*grid;
	int		x;

	x = 0;
	grid = NULL;
	fd = open(path, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		append_nodes(&grid, line, x);
		free(line);
		x++;
	}
	return (grid);
}