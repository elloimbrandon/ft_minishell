/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_tild_handles.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 22:40:19 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/08 16:31:50 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"
#include <stdio.h> ////////// REMOVEEEEEEEEEEEEE

void    handle_tilde(char *input_copy, t_cmd *input_check, t_env *env)
{
    char *temp;
    int i;

    i = -1;
    while(input_copy[++i])
    {
        if(ft_strrchr(input_copy, '~'))
        {
            ft_memmove(&input_copy[i], &input_copy[i + 1], ft_strlen(input_copy) - i);
            temp = ft_strdup(input_copy);
            get_home_path(temp, env); // check to try for the use of other commands with home path needed
            free(temp);
        }
    }
}

void    get_home_path(char *temp, t_env *env)
{
    int i;

    i = -1;
    while(env->env_copy[++i])
    {
        if (strncmp("HOME=", env->env_copy[i], 5) == 0)
        temp = ft_strdup(env->env_copy[i] + 5);
        env->tilde_hold = ft_strdup(temp);
    }
}

static void    add_env_var(char *temp, t_cmd *input_check, t_env *env)
{
    int i;
    int len;
    int len2;

    i = -1;
    len = ft_strlen(temp);
    len2 = ft_size2d(env->env_copy);
    env->env_copy[len2] = ft_strdup(temp);
    env->env_copy[len2 + 1] = NULL;
    input_check->add_env = 0;
}

void    handle_env(char *input_copy, t_cmd *input_check, t_env *env)
{
    char *temp;
    int i;

    i = -1;
    while(input_copy[++i])
    {
        if(ft_strrchr(input_copy, '$')) //&& input_copy[i + 1]) //added extra check
        {
            ft_memmove(&input_copy[i], &input_copy[i + 1], ft_strlen(input_copy) - i);
            temp = ft_strdup(input_copy);
            if(!input_check->set_e && !input_check->add_env) // might change
                temp = ft_strcat(temp, "=");
            find_env_var(temp, input_check, env);
            if(input_check->add_env == 1)
                add_env_var(temp, input_check, env);
            free(temp);
        }
    }
}

int		ft_size2d(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void    find_env_var(char *temp, t_cmd *input_check, t_env *env)
{
    int i;
    int len;

    i = -1;
    len = ft_strlen(temp);
    while(env->env_copy[++i])
    {
        if(ft_strccmp(temp, env->env_copy[i], '=') == 0)
        {
            if(input_check->set_e == 1)
            {
                env->exp_hold = ft_strdup(temp);
                ft_strdel(&env->env_copy[i]);
                env->env_copy[i] = ft_strdup(env->exp_hold);
                input_check->set_e = 0;
            }
            else if(input_check->unset_e == 1)
            {
                ft_strdel(&env->env_copy[i]);
                input_check->unset_e = 0;
            }
            else
                env->exp_hold = ft_strdup(env->env_copy[i] + len);
        }
    }
}