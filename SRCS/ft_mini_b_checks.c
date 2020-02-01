/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_b_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 23:42:01 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/31 18:30:15 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"

void     check_cd_cmd(char **input_copy, t_cmd *input_check, t_env *env)
{
    if(ft_strcmp(input_copy[0], "cd") == 0)
        ft_cd(input_copy,input_check, env);
}

void     check_env_cmd(char **input_copy, t_env *env)
{
    if(!input_copy[1] && ft_strcmp(input_copy[0], "env") == 0)
        ft_print_2d(env->env_copy);
    else if (input_copy[1] && ft_strcmp(input_copy[0], "env") == 0)
        ft_printf("%senv: %s: No such file or directory\n", KRED, input_copy[1]);
}

void     check_pwd_cmd(char **input_copy, t_cmd *input_check)
{
    if(!input_copy[1] && ft_strcmp(input_copy[0], "pwd") == 0)
        print_path();
    else if(!input_check->printed_errors && ft_strcmp(input_copy[0], "pwd") == 0)
        ft_printf("%spwd: too many arguments\n", KRED);
}

void     check_echo_cmd(char **input_copy, t_cmd *input_check)
{
    if(!input_copy[1] && ft_strcmp(input_copy[0], "echo") == 0)
        ft_printf("\n");
    else if(input_check->qoutes && ft_strcmp(input_copy[0], "echo") == 0)
    {
        if(input_check->qoutes % 2 == 0)
            ft_print_echo(input_copy, input_check);
        else
            ft_printf("%secho: Unmatched \" \" \n", KRED);
        input_check->qoutes = 0;
    }
    else if(input_copy[1] && ft_strcmp(input_copy[0], "echo") == 0)
        ft_print_echo(input_copy, input_check);
}

void     check_exit_cmd(char **input_copy)
{
    if(ft_strcmp(input_copy[0], "exit") == 0)
    {
        ft_printf("%sGoodbye!\n", KMAG);
        exit(1);
    }
}