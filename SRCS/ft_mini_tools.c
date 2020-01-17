/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandonf <brfeltz@student.42.us.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 22:31:41 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/16 00:22:56 by brandonf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"

/*
** removes the spaces from input and stores them into
** new 2d array so we can work with array's without spaces
*/

static int		w_dcount(char *words, int delim)
{
	int count;
	int i;
	i = 0;
	count = 0;
	while (words[i])
	{
		if (words[i] == delim)
			i++;
		else
		{
			while (words[i] && words[i] != delim)
				i++;
			count++;
		}
	}
	return (count);
}

static int     ft_count_words_2d(char **strings)
{
    int idx;
    int words_in_string;
    int total_words;

    idx = -1;
    total_words = 0;
    while(strings[++idx])
    {
        words_in_string = w_dcount(strings[idx], ' ');
        total_words += words_in_string;
    }
    return (words_in_string);
}

char    **split_by_space(char **input_copy)
{
    char **ret;
    char **flat;
    int i;
    int j;
    int k;

    i = 0;
    k = -1;
    int total_words = ft_count_words_2d(input_copy);
    flat = ft_memalloc(sizeof(char**) * (total_words + 1));
    flat[total_words] = NULL;
    while(input_copy[i])
    {
        ret = ft_strsplit(input_copy[i++], ' ');
        j = -1;
        while(ret[++j])
            flat[++k] = ret[j];
        free(ret);
    }
    ft_free_2d(input_copy);
    return(flat);
}

// char    **split_by_space(char **input_copy)
// {
//     char **ret;
//     int i;

//     i = 0;
    
//     while(input_copy[i])
//         ret = ft_strsplit(input_copy[i++], ' ');
//     ft_free_2d(input_copy);
//     return(ret);
// }

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