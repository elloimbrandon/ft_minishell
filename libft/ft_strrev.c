/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 23:08:47 by brfeltz           #+#    #+#             */
/*   Updated: 2019/08/08 16:06:07 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	int			i;
	int			x;
	char		temp;

	i = 0;
	x = 0;
	while (str[i] != '\0')
		i++;
	i--;
	while (x < i)
	{
		temp = str[i];
		str[i] = str[x];
		str[x] = temp;
		x++;
		i--;
	}
	return (str);
}
