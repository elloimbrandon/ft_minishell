/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strccmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 22:00:00 by brfeltz           #+#    #+#             */
/*   Updated: 2019/12/27 22:00:35 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strccmp(const char *s1, const char *s2, char c)
{
	int	x;

	x = 0;
	if (!c)
		return (0);
	while (s1[x] && s2[x] && s1[x] == s2[x] && s2[x] != '=')
		x++;
	return (((unsigned char *)s1)[x] - ((unsigned char *)s2)[x]);
}
