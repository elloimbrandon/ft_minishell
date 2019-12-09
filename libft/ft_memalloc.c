/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:46:56 by brfeltz           #+#    #+#             */
/*   Updated: 2019/03/04 16:02:03 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*i;
	size_t	x;

	x = 0;
	if ((i = malloc(size)) == NULL)
		return (NULL);
	while (x < size)
	{
		i[x] = 0;
		x++;
	}
	return (i);
}
