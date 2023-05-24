/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:23:13 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/24 16:28:04 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

static void	process_no_color(char **str, t_map *map, t_coordinate *temp)
{
	char	*trimmed;
	char	**divided;

	trimmed = ft_strtrim(str[temp->x], "\n");
	read_coord(map, ft_atoi(trimmed), temp, 0);
	ft_free_str(trimmed);
}

void	process_input(char **str, t_map *map, t_coordinate *temp)
{
	char	*trimmed;
	char	**divided;

	if (ft_strchr(str[temp->x], '\n') && !ft_strchr(str[temp->x], ','))
		process_no_color(str, map, temp);
	else if (ft_strchr(str[temp->x], '\n') && ft_strchr(str[temp->x], ','))
	{
		divided = ft_split(str[temp->x], ',');
		trimmed = ft_strtrim(divided[1], "\n");
		read_coord(map, ft_atoi(divided[0]), temp, ft_htol(trimmed));
		free_splitted(divided);
		ft_free_str(trimmed);
	}
	else if (!ft_strchr(str[temp->x], ','))
		read_coord(map, ft_atoi(str[temp->x]), temp, 0);
	else
	{
		divided = ft_split(str[temp->x], ',');
		read_coord(map, ft_atoi(divided[0]), temp, ft_htol(divided[1]));
		free_splitted(divided);
	}
}