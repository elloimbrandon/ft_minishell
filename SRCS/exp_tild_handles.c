/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_tild_handles.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 22:40:19 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/04 00:30:48 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"
#include <stdio.h> ////////// REMOVEEEEEEEEEEEEE

void    handle_exp_tilde(char *input_copy, t_cmd *input_check, t_env *env)
{
    if(input_check->expansions >= 1)
    {
        printf("hit handle_exp func\n");
        handle_exp(input_copy, input_check, env);
        input_check->expansions--;
        printf("%s <-- output str for exp\n", env->output);
    }
    else if(input_check->tilde >= 1)
    {
        printf("hit handle_tilde func\n");
        handle_tilde(input_copy, input_check, env);
        input_check->tilde--;
        printf("%s <-- output str for tilde\n", env->output);
    }
}

void    handle_tilde(char *input_copy, t_cmd *input_check, t_env *env)
{
    char *temp;
    int i;

    i = -1;
    while(input_copy[++i] && input_check->tilde >= 1)
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
        temp = ft_strdup(env->env_copy[i] + 5); // or try ft_strndup
        env->output = ft_strdup(temp);
    }
}

void    handle_exp(char *input_copy, t_cmd *input_check, t_env *env)
{
    char *temp;
    int i;

    i = -1;
    while(input_copy[++i] && input_check->expansions >= 1)
    {
        if(ft_strrchr(input_copy, '$'))
        {
            if(!ft_strrchr(input_copy, '='))
                env->solo_exp += 1;
            ft_memmove(&input_copy[i], &input_copy[i + 1], ft_strlen(input_copy) - i);
            temp = ft_strdup(input_copy);
            if(env->solo_exp)
                temp = ft_strcat(temp, "=");
            find_env_var(temp, env);
            free(temp);
        }
    }
}

void    find_env_var(char *temp, t_env *env)
{
    int i;
    int len;

    i = -1;
    len = ft_strlen(temp);
    while(env->env_copy[++i])
    {
        if(ft_strccmp(temp, env->env_copy[i], '=') == 0) // might not need 
        {
            if(ft_strcmp(temp, env->env_copy[i]) == 0) // if the env values are the same change nothing
                break ;
            if(!env->solo_exp && temp[len -= 1] == '=') // if the command isnt just $USER and it had '=' at the end dont change value
                break ;
            if(env->solo_exp)
            {
                temp = ft_strdup(env->env_copy[i]);
                env->solo_exp = 0;
            }
            env->output = ft_strdup(temp);
            ft_strdel(&env->env_copy[i]);
            env->env_copy[i] = ft_strdup(env->output);
        }
    }
}