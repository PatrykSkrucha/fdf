#include "include/fdf.h"
#include <stdio.h>

void my_keyhook(mlx_key_data_t keydata, void *map)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		exit(EXIT_SUCCESS); //free map etc
}
void	allocate_map(t_map **map)
{
	*map = malloc(sizeof(t_map));
	if (!map)
		exit(EXIT_FAILURE);
	(*map)->width = 0;
	(*map)->height = 0;
	(*map)->matrix = NULL;
	(*map)->projection = NULL;
	(*map)->window= mlx_init(WIDTH, HEIGHT, "fdf", true);
	(*map)->image = mlx_new_image((*map)->window, WIDTH, HEIGHT);
	if (!(*map)->image || (mlx_image_to_window((*map)->window, (*map)->image, 0, 0) < 0))
		exit(EXIT_FAILURE);
}

void	allocate_matrix(t_map **map)
{
	int	i;

	i = 0;
	//ft_printf("h: %i w: %i", (*map)->height, (*map)->width);
	//(*map)->matrix = malloc(sizeof(t_coordinate*) * (*map)->height);
	(*map)->matrix = ft_calloc((*map)->height, sizeof(t_coordinate*));
	(*map)->projection = ft_calloc((*map)->height, sizeof(t_coordinate*));
	if (!(*map)->projection || !(*map)->matrix)
		exit(EXIT_FAILURE);
	//(*map)->projection = malloc(sizeof(t_isometric*) * (*map)->height);
	while (i < (*map)->height)
	{
		(*map)->matrix[i] = ft_calloc((*map)->width, sizeof(t_coordinate));
		if (!(*map)->matrix[i])
		{
			ft_printf("memory allocation problem");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	while (i < (*map)->height)
	{
		(*map)->projection[i] = ft_calloc((*map)->width, sizeof(t_coordinate));
		if (!(*map)->projection[i])
		{
			ft_printf("memory allocation problem");
			exit(EXIT_FAILURE);
		}
		//(*map)->projection[i] = malloc(sizeof(t_isometric));
		i++;
	}

}

void	get_size(char *path, t_map **map)
{
	int	height;
	char	**splitted;
	int	i;
	int	width;
	int		fd;
	char	*line;

	height = 0;
	width = -1;
	i = 0;
	fd = open(path, O_RDONLY);
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
		if (width != -1)
		{
			if (width != i)
			{
				ft_printf("Incorrect map\n");
				exit (EXIT_FAILURE);
			}
		}
		else
			width = i;
		free_splitted(splitted);
		free(line);
		height++;
		i = 0;
	}
	close(fd);
	(*map)->height = height;
	(*map)->width = width;
	allocate_matrix(map);
}

void print_matrix(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			ft_printf("%i ", map->matrix[i][j].z);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void	draw(t_map *map)
{
	int i, j;
	i = 0;
	while (i < map->height)
	{
		j = 0;

		ft_printf("%i\n",i);
			while (j < map->width)
			{
				if (i == map->height - 1 && j < map->width - 1)
				{

					BresenhamLine(map->projection[i][j].x, map->projection[i][j].y, map->projection[i][j+1].x, map->projection[i][j+1].y, map->image);
				}
				else if (j == map->width - 1 && i < map->height - 1)
					BresenhamLine(map->projection[i][j].x, map->projection[i][j].y, map->projection[i+1][j].x, map->projection[i+1][j].y, map->image);
				else if (i != map->height -1 && j != map->width -1)
				{
					BresenhamLine(map->projection[i][j].x, map->projection[i][j].y, map->projection[i][j+1].x, map->projection[i][j+1].y, map->image);
				//ft_printf("kirwwww %i %i\n\n",i,j);
					BresenhamLine(map->projection[i][j].x, map->projection[i][j].y, map->projection[i+1][j].x, map->projection[i+1][j].y, map->image);
				}
				j++;
			}
		i++;
	}
}

void	isometric(t_map **map)
{
	int	i;
	int	j;
	double theta;

	theta = 30 * 3.14 / 180 ;
	i = 0;
	while (i < (*map)->height)
	{
		j = 0;
		while (j < (*map)->width)
		{
			(*map)->projection[i][j].color = (*map)->matrix[i][j].color;
			(*map)->projection[i][j].x = (((*map)->matrix[i][j].x * cos(theta) - (*map)->matrix[i][j].y * cos(theta))) + 400;
			(*map)->projection[i][j].y = (*map)->matrix[i][j].x * sin(theta) + (*map)->matrix[i][j].y * sin(theta) - (*map)->matrix[i][j].z;
			//(*map)->projection[i][j].x = ((*map)->matrix[i][j].x * cos(theta) - (*map)->matrix[i][j].y * cos(theta)) + 400;
			//(*map)->projection[i][j].y = ((*map)->matrix[i][j].x * sin(theta) + (*map)->matrix[i][j].y * sin(theta)) - (*map)->matrix[i][j].z;
			j++;
		}
		i++;
	}
	printf("%i %i ", i ,j);
}
int32_t	main(int argc, char **argv)
{
	t_map	*map;
	//t_coordinate	*point;
	//t_coordinate	*point3;
	//t_coordinate	*point1;
	//t_coordinate	*point11;
	//point = malloc(sizeof(t_coordinate));
	//point3 = malloc(sizeof(t_coordinate));
	//point1 = malloc(sizeof(t_coordinate));
	//point11 = malloc(sizeof(t_coordinate));
	
	//mlx_image_t* img = 
	//if (!mlx)
	//	exit(EXIT_FAILURE);
	allocate_map(&map);
	get_size(argv[1], &map);
	//ft_printf("h: %i w: %i", map->height, map->width);
	//map->matrix[2][100] = *point;
	read_map(argv[1], &map);


	//print_matrix(map);
	//point->x =1;
	//point3->x =1;
	//point1->x =150;
	//point->y =1;
	//point->z =1;



	//ft_printf("haha");
	//map->matrix = malloc(sizeof(t_coordinate*));
	//map->matrix[0] = malloc(1);
	//map->matrix[1] = malloc(1);

	//map->matrix[1][1000] = *point1;
	//map->matrix[1][1001] = *point3;
	//ft_printf("%i", map->matrix[1][1000].x);
	//ft_printf("%i", map->matrix[1][0].x);

	//BresenhamLine(200, 200, 800, 800, map->image);
	isometric(&map);
	////print_matrix(map);
	////printf("tu????\n\n");
	
	draw(map);
	mlx_key_hook(map->window, &my_keyhook, &map);
	mlx_loop(map->window);
	mlx_terminate(map->window);
	return (EXIT_SUCCESS);
}
