/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_2d_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 18:18:44 by brfeltz           #+#    #+#             */
/*   Updated: 2020/02/01 17:28:09 by brfeltz          ###   ########.fr       */
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
	if (!str)
		return (NULL);
	while (str[len])
		len++;
	temp = ft_memalloc(sizeof(char*) * (len + 1));
	temp[len] = NULL;
	while (str[++i])
		temp[i] = ft_strdup(str[i]);
	return (temp);
}
