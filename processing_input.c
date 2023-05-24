/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:23:13 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/24 18:24:11 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

static void	process_no_color(char **str, t_map *map, t_coordinate *temp)
{
	char	*trimmed;
	int		z;	

	trimmed = ft_strtrim(str[temp->x], "\n");
	if (!trimmed)
		free_and_exit(map, 1);
	z = ft_atoi(trimmed);
	ft_free_str(trimmed);
	read_coord(map, z, temp, 0);
}

static void	process_color_nl(char **str, t_map *map, t_coordinate *temp)
{
	char	*trimmed;
	char	**divided;

	divided = ft_split(str[temp->x], ',');
	if (!divided)
		free_and_exit(map, 1);
	trimmed = ft_strtrim(divided[1], "\n");
	if (!trimmed)
	{
		free_splitted(divided);
		free_and_exit(map, 1);
	}
	read_coord(map, ft_atoi(divided[0]), temp, ft_htol(trimmed));
	free_splitted(divided);
	ft_free_str(trimmed);
}

static void	process_color(char **str, t_map *map, t_coordinate *temp)
{
	char	**divided;

	divided = ft_split(str[temp->x], ',');
	if (!divided)
		free_and_exit(map, 1);
	read_coord(map, ft_atoi(divided[0]), temp, ft_htol(divided[1]));
	free_splitted(divided);
}

void	process_input(char **str, t_map *map, t_coordinate *temp)
{
	char	*trimmed;
	char	**divided;

	if (ft_strchr(str[temp->x], '\n') && !ft_strchr(str[temp->x], ','))
		process_no_color(str, map, temp);
	else if (ft_strchr(str[temp->x], '\n') && ft_strchr(str[temp->x], ','))
		process_color_nl(str, map, temp);
	else if (!ft_strchr(str[temp->x], ','))
		read_coord(map, ft_atoi(str[temp->x]), temp, 0);
	else
		process_color(str, map, temp);
}
