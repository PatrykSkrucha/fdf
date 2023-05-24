/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:20:00 by pskrucha          #+#    #+#             */
/*   Updated: 2023/05/24 18:43:12 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_htol(char *s)
{
	long	res;

	if (!s)
		return (0);
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
