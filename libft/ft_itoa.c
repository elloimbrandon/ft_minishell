/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:36:29 by brfeltz           #+#    #+#             */
/*   Updated: 2019/03/05 17:27:33 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_instrlen(int n)
{
	size_t	i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

char			*ft_itoa(int n)
{
	char			*str;
	size_t			len;
	unsigned int	sign;

	len = ft_instrlen(n);
	sign = n;
	if (n < 0)
	{
		sign = -n;
		len++;
	}
	str = (char*)malloc(sizeof(char) * len);
	if (!str)
		return (NULL);
	str[len] = '\0';
	str[--len] = sign % 10 + '0';
	while (sign /= 10)
		str[--len] = sign % 10 + '0';
	if (n < 0)
		str[0] = '-';
	return (str);
}
