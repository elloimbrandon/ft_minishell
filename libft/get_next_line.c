/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 16:07:14 by brfeltz           #+#    #+#             */
/*   Updated: 2019/04/08 16:23:26 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_line(char **temp, int fd, char **line)
{
	char	*str;
	char	*tempmem;

	if ((str = ft_strchr(temp[fd], '\n')))
	{
		tempmem = temp[fd];
		*str = '\0';
		*line = ft_strndup(temp[fd], str - temp[fd]);
		temp[fd] = ft_strdup(str + 1);
		free(tempmem);
		return (1);
	}
	else if (*temp[fd])
	{
		*line = ft_strdup(temp[fd]);
		temp[fd] = ft_strnew(BUFF_SIZE + 1);
		return (1);
	}
	return (0);
}

int		ft_read(int fd, char **buffer)
{
	char	*temp;
	char	*leak;
	int		result;

	temp = ft_strnew(BUFF_SIZE);
	while ((result = read(fd, temp, BUFF_SIZE)) > 0)
	{
		leak = buffer[fd];
		buffer[fd] = ft_strjoin(buffer[fd], temp);
		if (!buffer[fd])
			buffer[fd] = ft_strdup(temp);
		free(leak);
		ft_bzero(temp, BUFF_SIZE);
	}
	free(temp);
	return (result);
}

int		get_next_line(const int fd, char **line)
{
	static char *temp[4864];

	if (!line || fd < 0 || BUFF_SIZE < 0)
		return (-1);
	if (ft_read(fd, &temp[fd]) < 0)
		return (-1);
	if (get_line(&temp[fd], fd, line) == 1)
		return (1);
	return (0);
}
