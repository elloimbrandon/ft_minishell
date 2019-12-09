/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 19:29:02 by brfeltz           #+#    #+#             */
/*   Updated: 2019/03/04 12:41:22 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *needle, size_t len)
{
	unsigned long	i;
	int				x;

	x = 0;
	i = 0;
	if (!*needle)
		return ((char*)hay);
	while (hay[i])
	{
		x = 0;
		while (hay[i] == needle[x] && hay[i] && i < len)
		{
			i++;
			x++;
		}
		if (!needle[x])
			return ((char*)&hay[i - x]);
		i = (i - x) + 1;
	}
	return (NULL);
}
