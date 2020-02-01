/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp_tilde_checks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 23:50:09 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/31 19:03:41 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"

void   check_env(char *input_copy, t_cmd *input_check)
{
    int i;

    i = -1;
    while(input_copy[++i])
    {
        if (input_copy[i] == '$')
            input_check->expansions++;
    }
}

void   check_tilde(char *input_copy, t_cmd *input_check)
{
    int i;

    i = -1;
    while(input_copy[++i])
    {
        if (input_copy[i] == '~')
            input_check->tilde++;
    }
}

char    *exp_tilde_check(char *input_copy, t_cmd *input_check, t_env *env)
{
    char *ret;

    if (input_check->expansions == 1 && input_copy[1])
    {
        handle_env(input_copy, env);
        if (env->exp_hold)
        {
            free(input_copy);
            ret = ft_strdup(env->exp_hold);
            free(env->exp_hold);
            return (ret);
        }
    }
    if (input_check->tilde == 1)
    {
        handle_tilde(input_copy, env);
        if (env->tilde_hold)
        {
            free(input_copy);
            ret = ft_strdup(env->tilde_hold);
            free(env->tilde_hold);
            return (ret);
        }
    }
    return (input_copy);
}
