/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 21:05:22 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/29 18:31:03 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char const *s, int n)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == n)
			return ((char*)s);
		s++;
	}
	if (!n)
		return ((char*)s);
	return (NULL);
}
