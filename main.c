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
}

//int	**allocate_matrix(char *path)
//{
//	int	**matrix;
//	int	width;
//	int	height;

//	width = 0;
//	height = 0;
//	matrix = NULL;
//	get_size(path, &height, &width);
//	return(matrix);
//}

void	check_input(char *path, t_map **map)
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
		{	
			//ft_printf("string: %s i: %i\n",splitted[i],i);
			//sleep(1);
			i++;
		}
		//ft_printf("tu??");
		i--;
		if (width != -1)
		{
			if (width != i)
				exit (EXIT_FAILURE);
		}
		else
			width = i;
		i++;
		while (i >= 0)
		{
			free(splitted[i]);
			i--;
		}
		height++;
		free(splitted);
		free(line);
		i = 0;
	}
	(*map)->height = height;
	(*map)->width = width;
}

int32_t	main(int argc, char **argv)
{
	t_map	*map;
	//t_coordinate	**array;
	//t_coordinate	*coord;

	//coord = malloc(sizeof(t_coordinate));
	//array = malloc(sizeof(1));
	//if (!array)
	//	exit(EXIT_FAILURE);
	//coord->x = 5000;
	//coord->y = 60;
	//array[0] = malloc(sizeof(1));
	//array[0][0] = *coord;
	//printf("%i",(&array[0][0])->y);
	//mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	//if (!mlx)
	//	exit(EXIT_FAILURE);
	allocate_map(&map);
	check_input(argv[1], &map);
	ft_printf("height: %i\nwidth: %i", map->height, map->width);
	//get_dimentions(argv[1], &map);
	//read_map(argv[1], &map);
	//mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
	//if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
	//	exit(EXIT_FAILURE);
	//mlx_put_pixel(img, 10, 10, 0xf63d9dcc);
	//mlx_put_pixel(img, 11, 11, 0xf63d9dcc);
	//mlx_put_pixel(img, 12, 12, 0xf63d9dcc);
	//mlx_put_pixel(img, 301, 301, 1140810969);
	//mlx_put_pixel(img, 302, 302, 1140810969);
	//mlx_put_pixel(img, 303, 303, 1140810969);
	//mlx_key_hook(mlx, &my_keyhook, &map);
	//mlx_loop(mlx);
	//mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
