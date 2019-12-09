/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 14:06:20 by brfeltz           #+#    #+#             */
/*   Updated: 2019/03/16 14:11:26 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_max(int *tab, unsigned int length)
{
	unsigned int	i;
	int				max;

	i = 0;
	max = tab[i];
	if (!tab)
		return (0);
	while (i < length)
	{
		if (tab[i] > max)
		{
			max = tab[i];
			i = 0;
		}
		i++;
	}
	return (max);
}
