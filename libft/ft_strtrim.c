/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 20:11:16 by brfeltz           #+#    #+#             */
/*   Updated: 2019/03/03 20:20:50 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	i;
	char	*dst;
	int		beg;

	beg = 0;
	if (!s)
		return (NULL);
	i = 0;
	while (ft_isspace(s[i]))
		i++;
	beg = i;
	if (s[beg] == '\0')
	{
		dst = ft_strnew(0);
		dst[0] = '\0';
		return (dst);
	}
	while (s[i])
		i++;
	i--;
	while (ft_isspace(s[i]))
		i--;
	if (!(dst = (ft_strsub(s, beg, i - beg + 1))))
		return (NULL);
	return (dst);
}
