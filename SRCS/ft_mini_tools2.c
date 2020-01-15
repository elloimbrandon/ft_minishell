/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_tools2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 23:38:41 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/15 00:27:38 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"

char     *find_home(t_env *env)
{
    int i;

    i = -1;
    while(env->env_copy[++i])
    {
        if (strncmp("HOME=", env->env_copy[i], 5) == 0)
            return(ft_strdup(env->env_copy[i] + 5));
    }
    return(0);
}

char     *find_old_pwd(t_env *env)
{
    int i;

    i = -1;
    while(env->env_copy[++i])
    {
        if (strncmp("OLDPWD=", env->env_copy[i], 7) == 0)
            return(ft_strdup(env->env_copy[i] + 7));
    }
    return(0);
}


void     handle_qoutes(char **input_copy, t_cmd *input_check)
{
    if(input_check->qoutes % 2 == 0)
        ft_print_echo(input_copy, input_check);
    else
        ft_printf("%secho: Unmatched \" \" \n", KRED);
}

void     check_qoutes(char *input_copy, t_cmd *input_check)
{
    int i;

    i = -1;
    while(input_copy[++i])
    {
        if(input_copy[i] == '"')
            input_check->qoutes++;
    }
}

void     ft_remove_qoutes(char *input_copy, t_cmd *input_check)
{
    int k;

    k = -1;
    while(input_copy[++k])
    {
        if(input_copy[k] != '"')
            ft_printf("%c", input_copy[k]);
    }
}
