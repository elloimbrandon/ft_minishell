/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 22:31:41 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/15 20:21:57 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"

/*
** removes the spaces from input and stores them into
** new 2d array so we can work with array's without spaces
*/

char    **split_by_space(char **input_copy)
{
    char **ret;
    int i;

    i = 0;
    while(input_copy[i])
        ret = ft_strsplit(input_copy[i++], ' ');
    ft_free_2d(input_copy);
    return(ret);
}

int		ft_size_2d(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char    *get_path(char *hold, t_env *env)
{
    int i;
    char *temp;

    i = -1;
    while(env->env_copy[++i])
    {
        if (strncmp("PATH=", env->env_copy[i], 5) == 0)
        {
            temp = ft_strdup(env->env_copy[i] + 5);
            return(temp);
        }
    }
    return(NULL);
}

char    *build_path(char *input_copy, char *path)
{
    path = ft_strcat(path, "/");
    return(ft_strjoin(path, input_copy));
}