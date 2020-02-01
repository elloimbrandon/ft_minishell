/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 18:16:06 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/31 19:05:50 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"

void    check_setenv(char **input_copy, t_env *env)
{
    if (!input_copy[1] && ft_strcmp(input_copy[0], "setenv") == 0)
        ft_printf("%ssetenv: not enough arguments\n", KRED);
    else if (ft_strcmp(input_copy[0], "setenv") == 0 && input_copy[2])
        ft_printf("%ssetenv: too many arguments\n", KRED);
    else if (input_copy[1] && ft_strcmp(input_copy[0], "setenv") == 0)
    {
        if (find_set_var(input_copy, env) == 0)
            add_env_var(input_copy, env);
    }
}

int    find_set_var(char **input_copy, t_env *env)
{
    int i;
    char *temp;

    i = -1;
    temp = NULL;
    while(env->env_copy[++i])
    {
        if (ft_strccmp(input_copy[1], env->env_copy[i], '=') == 0)
        {
                temp = ft_strdup(input_copy[1]);
                free(env->env_copy[i]);
                env->env_copy[i] = ft_strdup(temp);
                free(temp);
                return (1);
        }
    }
    return (0);
}

void    add_env_var(char **input_copy, t_env *env)
{
    int i;
    int k;
    int len;

    i = -1;
    k = 0;
    len = ft_strlen(input_copy[1]);
    while(input_copy[1][++i])
    {
        if (input_copy[1][i] == '=')
        k = 1;
    }
    if (k == 1)
        env->env_copy = add_new_line(env, input_copy);
    else
        ft_printf("%ssetenv: variable has no value: %s\n", KRED, input_copy[1]);
}

char    **add_new_line(t_env *env, char **input_copy)
{
    int     i;
    int    len;
    char   **temp;

    i = -1;
    len = ft_size_2d(env->env_copy);
    temp = ft_memalloc(sizeof(char**) * (len + 2));
    while(env->env_copy[++i])
        temp[i] = ft_strdup(env->env_copy[i]);
    temp[i] = ft_strdup(input_copy[1]);
    temp[i + 1] = NULL;
    ft_free_2d(env->env_copy);
    return (temp);
}
