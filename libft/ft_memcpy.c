/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:10:59 by brfeltz           #+#    #+#             */
/*   Updated: 2019/03/11 18:13:00 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	unsigned char *c1;
	unsigned char *c2;

	if (n == 0 || s1 == s2)
		return (s1);
	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	while (n--)
		*c1++ = *c2++;
	c1 = c2;
	return (s1);
}
