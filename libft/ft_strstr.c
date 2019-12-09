/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 18:52:55 by brfeltz           #+#    #+#             */
/*   Updated: 2019/03/11 19:18:09 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	int i;
	int x;
	int size;

	size = 0;
	i = 0;
	while (to_find[size])
		size++;
	if (size == 0)
		return (((char*)str));
	while (str[i])
	{
		x = 0;
		while (to_find[x] == str[i + x])
		{
			if (to_find[x + 1] == '\0')
			{
				return (((char*)str) + i);
			}
			x++;
		}
		i++;
	}
	return (0);
}
