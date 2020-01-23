/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandonf <brfeltz@student.42.us.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 22:31:41 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/23 01:16:07 by brandonf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"

/*
** removes the spaces from input and stores them into
** new 2d array so we can work with array's without spaces
*/

static int		w_dcount(char *words, int d)
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

static int     ft_count_words_2d(char **s)
{
    int i;
    int wrds_in_string;
    int total_wrds;

    i = -1;
    total_wrds = 0;
    while(s[++i])
    {
        wrds_in_string = w_dcount(s[i], ' ');
        total_wrds += wrds_in_string;
    }
    return (wrds_in_string);
}

char    **split_by_space(char **input_copy)
{
    char **temp;
    char **ret;
    int total_wrds;
    int i;
    int j;
    int k;

    i = 0;
    k = -1;
    total_wrds = ft_count_words_2d(input_copy);
    ret = ft_memalloc(sizeof(char**) * (total_wrds + 1));
    ret[total_wrds] = NULL;
    while(input_copy[i])
    {
        temp = ft_strsplit(input_copy[i++], ' ');
        j = -1;
        while(temp[++j])
            ret[++k] = temp[j];
        free(temp);
    }
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