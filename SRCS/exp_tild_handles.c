/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_tild_handles.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 22:40:19 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/29 18:18:28 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"

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
            get_home_path(temp, env);
            free(temp);
        }
    }
}

void    handle_env(char *input_copy, t_cmd *input_check, t_env *env)
{
    char *temp;
    int i;

    i = -1;
    while(input_copy[++i])
    {
        if(ft_strrchr(input_copy, '$'))
        {
            if(input_copy[0] == '"')
                ft_memmove(&input_copy[i], &input_copy[i + 2], ft_strlen(input_copy) - i);
            else
                ft_memmove(&input_copy[i], &input_copy[i + 1], ft_strlen(input_copy) - i);
            if(input_copy[ft_strlen(input_copy) - 1] == '"')
                temp = ft_strndup(input_copy, ft_strlen(input_copy) - 1); /// still needs work
            else
                temp = ft_strdup(input_copy);
            temp = ft_strcat(temp, "=");
            find_env_var(temp, input_check, env);
            free(temp);
            break ;
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
        {
            temp = ft_strdup(env->env_copy[i] + 5);
            env->tilde_hold = ft_strdup(temp);
        }
    }
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
            env->exp_hold = ft_strdup(env->env_copy[i] + len);
    }
}