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
	(*map)->window = NULL;
	(*map)->image = NULL;
	(*map)->matrix = NULL;
	(*map)->projection = NULL;
}

void	allocate_matrix(t_map **map)
{
	int	i;

	i = 0;
	//ft_printf("h: %i w: %i", (*map)->height, (*map)->width);
	(*map)->matrix = malloc(sizeof(t_coordinate*) * (*map)->height);
	(*map)->projection = malloc(sizeof(t_isometric*) * (*map)->height);
	while (i < (*map)->height)
	{
		(*map)->matrix[i] = malloc(sizeof(t_coordinate) * (*map)->width);
		i++;
	}
	i = 0;
	while (i < (*map)->height)
	{
		(*map)->projection[i] = malloc((*map)->width);
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
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!mlx)
		exit(EXIT_FAILURE);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		exit(EXIT_FAILURE);
	allocate_map(&map);
	get_size(argv[1], &map);
	//ft_printf("h: %i w: %i", map->height, map->width);
	//map->matrix[2][100] = *point;
	read_map(argv[1], &map);

	//printf("color: %lu", map->matrix[5][3].color);


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

	//ft_printf("x:%i y:%i z:%i\n",map->matrix[1][1].x, map->matrix[1][1].y, map->matrix[1][1].z);
	//BresenhamLine(200, 200, 800, 800, img);
	
	int i, j;
	i = 0;
			//ft_printf("haha\n\n");
	while (i < map->height)
	{
		j = 0;

		ft_printf("%i\n",i);
			while (j < map->width)
			{
				if (i == map->height - 1 && j < map->width - 1)
				{
					ft_printf("pierw\n");
					BresenhamLine(map->matrix[i][j].x, map->matrix[i][j].y, map->matrix[i][j+1].x, map->matrix[i][j+1].y, img);
					ft_printf("pierw1\n");
				}
				else if (j == map->width - 1 && ft_printf("drukuje") && i < map->height - 1)
				{
					ft_printf("??2\n");
					BresenhamLine(map->matrix[i][j].x, map->matrix[i][j].y, map->matrix[i+1][j].x, map->matrix[i+1][j].y, img);
					ft_printf("??22\n");
				}
				else if (i != map->height -1 && j != map->width -1)
				{
					ft_printf("here1\n");
					ft_printf("here2\n");
					BresenhamLine(map->matrix[i][j].x, map->matrix[i][j].y, map->matrix[i][j+1].x, map->matrix[i][j+1].y, img);
					ft_printf("nie1\n");
					BresenhamLine(map->matrix[i][j].x, map->matrix[i][j].y, map->matrix[i+1][j].x, map->matrix[i+1][j].y, img);
					ft_printf("nie2\n");
				}
				j++;
			}
		i++;
	}
	mlx_key_hook(mlx, &my_keyhook, &map);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
