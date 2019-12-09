/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 18:31:11 by brfeltz           #+#    #+#             */
/*   Updated: 2019/02/28 18:35:21 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *s1, const char *s2, size_t size)
{
	size_t	x;
	int		j;
	int		i;

	j = 0;
	i = ft_strlen(s1);
	x = i;
	if (size < x)
		return (ft_strlen((char *)s2) + size);
	else
	{
		while (x < size - 1 && s2[j])
		{
			s1[x] = s2[j];
			x++;
			j++;
		}
	}
	s1[x] = '\0';
	return (i + ft_strlen((char *)s2));
}
