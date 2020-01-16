/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_b_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 23:42:01 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/15 19:42:40 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"

void     check_cd_cmd(char **input_copy, t_cmd *input_check, t_env *env)
{
    if(ft_strcmp(input_copy[0], "cd") == 0)
        ft_cd(input_copy,input_check, env);
}

void     check_env_cmd(char **input_copy, t_cmd *input_check, t_env *env)
{
    if(!input_copy[1] && ft_strcmp(input_copy[0], "env") == 0)
        ft_print_2d(env->env_copy);
    else if (input_copy[1] && ft_strcmp(input_copy[0], "env") == 0)
        ft_printf("%senv: %s: No such file or directory\n", KRED, input_copy[1]);
}

void     check_pwd_cmd(char **input_copy, t_cmd *input_check, t_env *env)
{
    if(!input_copy[1] && ft_strcmp(input_copy[0], "pwd") == 0)
        print_path(env);
    else if(!input_check->printed_errors && ft_strcmp(input_copy[0], "pwd") == 0)
        ft_printf("%spwd: too many arguments\n", KRED);
}

void     check_echo_cmd(char **input_copy, t_cmd *input_check, t_env *env)
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


static int    find_set_var(char **input_copy, t_env *env)
{
    int i;
    char *temp;

    i = -1;
    temp = NULL;
    while(env->env_copy[++i])
    {
        if(ft_strccmp(input_copy[1], env->env_copy[i], '=') == 0)
        {
                temp = ft_strdup(input_copy[1]);
                free(env->env_copy[i]);
                env->env_copy[i] = ft_strdup(temp);
                free(temp);
                return(1);
        }
    }
    return(0);
}

static char    **add_new_line(t_env *env, char **input_copy)
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
    return(temp);
}

static void    add_env_var(char **input_copy, t_env *env)
{
    int i;
    int len;
    int len2;

    i = -1;
    len = ft_strlen(input_copy[1]);
    env->env_copy = add_new_line(env, input_copy);
}


void    check_setenv(char **input_copy, t_cmd *input_check, t_env *env)
{
    if(!input_copy[1] && ft_strcmp(input_copy[0], "setenv") == 0)
        ft_printf("%ssetenv: not enough arguments\n", KRED);
    else if(input_copy[2] && ft_strcmp(input_copy[0], "setenv") == 0)
        ft_printf("%ssetenv: too many arguments\n", KRED);
    else if(input_copy[1] && ft_strcmp(input_copy[0], "setenv") == 0)
    {
        if (find_set_var(input_copy, env) == 0)
            add_env_var(input_copy, env);
    }
}

static int      find_unset_var(char **input_copy, t_env *env)
{
    int i;
    int k;
    char *temp;
    char *temp2;

    i = -1;
    k = 0;
    temp2 = NULL;
    temp = ft_strdup(input_copy[1]);
    ft_strcat(temp, "=");
    while(env->env_copy[++i])
    {
        if(ft_strccmp(temp, env->env_copy[i], '=') == 0)
        {
            ft_strdel(&env->env_copy[i]);
            k = 1;
        }
        if(k == 1 && env->env_copy)
        {
            temp2 = env->env_copy[i + 1];
            env->env_copy[i] = temp2;
        }
    }
    free(temp);
    if(k == 1)
    {
        free(temp2); // might not need to free
        return(1);
    }
    return(0);
}

void    check_unsetenv(char **input_copy, t_cmd *input_check, t_env *env)
{
    if(!input_copy[1] && ft_strcmp(input_copy[0], "unsetenv") == 0)
        ft_printf("%sunsetenv: not enough arguments\n", KRED);
    else if(input_copy[2] && ft_strcmp(input_copy[0], "unsetenv") == 0)
        ft_printf("%sunsetenv: too many arguments\n", KRED);
    else if(input_copy[1] && ft_strcmp(input_copy[0], "unsetenv") == 0)
    {
        if(find_unset_var(input_copy, env) == 0)
            ft_printf("%sunsetenv: var doesnt exist: %s\n", KRED, input_copy[1]);
    }
}

void     check_exit_cmd(char **input_copy, t_cmd *input_check, t_env *env)
{
    if(ft_strcmp(input_copy[0], "exit") == 0)
    {
        ft_printf("%sGoodbye!\n", KMAG);
        exit(1);
    }
}