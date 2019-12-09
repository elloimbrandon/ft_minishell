/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:10:17 by brfeltz           #+#    #+#             */
/*   Updated: 2019/03/04 13:12:53 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char *temp;

	temp = (unsigned char*)str;
	while (n--)
	{
		if (*temp != (unsigned char)c)
			temp++;
		else
			return (temp);
	}
	return (NULL);
}
