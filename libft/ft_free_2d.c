/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 23:49:02 by brfeltz           #+#    #+#             */
/*   Updated: 2019/12/19 23:50:23 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_2d(char **str)
{
	int i;

	i = 0;
	if (!*str || !str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	str = NULL;
}