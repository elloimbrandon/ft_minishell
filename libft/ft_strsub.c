/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 14:41:02 by brfeltz           #+#    #+#             */
/*   Updated: 2019/02/28 15:42:38 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char	const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;

	i = 0;
	dst = (char *)malloc((len + 1) * sizeof(char));
	if (dst && s)
	{
		while (i < len)
			dst[i++] = s[start++];
		dst[i] = '\0';
		return (dst);
	}
	return (NULL);
}
