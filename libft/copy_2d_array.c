/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_2d_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 18:18:44 by brfeltz           #+#    #+#             */
/*   Updated: 2019/12/27 18:20:53 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**copy_2d_array(char **str)
{
	int		i;
	int		len;
	char	**temp;

	i = -1;
	len = 0;
	while (str[len])
		len++;
	len--;
	temp = ft_memalloc(sizeof(char*) * (len + 1));
	while (str[++i])
		temp[i] = ft_strdup(str[i]);
	temp[i] = NULL;
	return (temp);
}
