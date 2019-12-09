/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 21:28:05 by brfeltz           #+#    #+#             */
/*   Updated: 2019/02/26 21:53:29 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int n)
{
	size_t len;

	len = ft_strlen(s);
	while (len > 0 && s[len] != n)
		len--;
	if (s[len] == n)
		return (&((char*)s)[len]);
	return (NULL);
}
