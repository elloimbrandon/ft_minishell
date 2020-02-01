/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 22:31:41 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/31 20:33:19 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"

int		ft_count_words_2d(char **s)
{
	int i;
	int wrds_in_string;

	i = -1;
	if (!s)
		return (-1);
	wrds_in_string = 0;
	while (s[++i])
		wrds_in_string = w_count(s[i], ' ');
	return (wrds_in_string);
}

int		w_count(char *words, int d)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while (words[i])
	{
		if (words[i] == d)
			i++;
		else
		{
			while (words[i] && words[i] != d)
				i++;
			count++;
		}
	}
	return (count);
}

int		ft_size_2d(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	*get_path(t_env *env)
{
	int		i;
	char	*temp;

	i = -1;
	while (env->env_copy[++i])
	{
		if (strncmp("PATH=", env->env_copy[i], 5) == 0)
		{
			temp = ft_strdup(env->env_copy[i] + 5);
			return (temp);
		}
	}
	return (NULL);
}

char	*build_path(char *input_copy, char *path)
{
	path = ft_strcat(path, "/");
	return (ft_strjoin(path, input_copy));
}
