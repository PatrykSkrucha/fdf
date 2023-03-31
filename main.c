#include "include/fdf.h"

int	lst_size(t_grid *grid)
{
	int i = 0;
	while (grid)
	{
		i++;
		grid = grid->next;
	}
	return (i);
}

int	main(int argc, char **argv)
{
	t_grid	*grid;
	
	grid = read_map(argv[1]);
	print_list(grid);
	return (0);	
}