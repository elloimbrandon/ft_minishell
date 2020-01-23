/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_2d_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandonf <brfeltz@student.42.us.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 18:18:44 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/23 00:55:39 by brandonf         ###   ########.fr       */
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
	temp = ft_memalloc(sizeof(char*) * (len + 1)); // might not need the 1?
	temp[len] = NULL;
	while (str[++i])
		temp[i] = ft_strdup(str[i]);
	return (temp);
}
