/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_splitted.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:29:20 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/24 14:24:55 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	free_splitted(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
	{
		free(str[i]);
		str[i] = NULL;
		i--;
	}
	free(str);
	str = NULL;
	return (0);
}
