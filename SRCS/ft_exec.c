/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 23:53:37 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/29 16:48:30 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"

void    check_system_cmd(char **input_copy, t_cmd *input_check, t_env *env)
{
    char *hold;
    
    hold = get_path(hold, env);
    if(hold)
        check_exec(hold, input_copy, env);
    else
        ft_printf("%sshell: command not found: %s\n", KRED, input_copy[0]);
    free(hold);
}

void    check_exec(char *hold, char **input_copy, t_env *env)
{
    char **path;
    char *exec;
    struct stat buf;
    int i;
    int k;

    k = 0;
    i = -1;
    exec = NULL;
    path = ft_strsplit(hold, ':');
    while(path[++i])
    {
        exec = build_path(input_copy[0], path[i]);
        if(lstat(exec, &buf) != 1)
        {
            if(ft_same_cmd(exec, input_copy) == 1)
                exec = ft_strdup(input_copy[0]);
            if (access(exec, X_OK) == 0)
            {
                ft_fork(exec, input_copy, env);
                k = 1;
                break ;
            }
        }
        free(exec);
    }
    ft_free_2d(path); //added // free path
    if (k == 0 && ft_strcmp(input_copy[0], "\n") != 0)
        ft_printf("%sshell: command not found: %s\n", KRED, input_copy[0]);
}

void    ft_local_exec(char **input_copy, t_cmd *input_check, t_env *env)
{
    char *exec;
    struct stat buf;

    exec = NULL;
    if (!input_copy)
        return ;
    if (ft_strchr(input_copy[0], '/') != NULL && ft_strchr(input_copy[0], '.') != NULL)
    {
        if (lstat(input_copy[0], &buf) != -1)
        {
            if S_ISREG(buf.st_mode)
            {
                if (access(input_copy[0], X_OK) == 0)
                {
                    exec = ft_strdup(input_copy[0]);
                    ft_fork(exec, input_copy, env);
                }
                else
                    ft_printf("%sshell: Permission denied: %s\n", KRED, input_copy[0]);
            }
            chdir(input_copy[0]);
        }
        else
            ft_printf("%sshell: no such file or directory: %s\n", KRED, input_copy[0]);
        input_check->executed = 1;
    }
}

void    ft_fork(char *exec, char **input_copy, t_env *env)
{
    char **env_copy;
    pid_t child_p;

    env_copy = copy_2d_array(env->env_copy);
    child_p = fork();
    if(child_p == 0)
        execve(exec, input_copy, env_copy);
    else if (child_p < 0)
        ft_printf("%sshell: could not create process\n", KRED);
    free(exec); // added
    ft_free_2d(env_copy);
    wait(&child_p);
}

void    ft_already_exc(t_cmd *input_check, char **input_copy)
{
    if (ft_strcmp(input_copy[0], "echo") == 0)
        input_check->executed = 1;
    else if (ft_strcmp(input_copy[0], "cd") == 0)
        input_check->executed = 1;
    else if (ft_strcmp(input_copy[0], "env") == 0)
        input_check->executed = 1;
    else if (ft_strcmp(input_copy[0], "pwd") == 0)
        input_check->executed = 1;
    else if (ft_strcmp(input_copy[0], "exit") == 0)
        input_check->executed = 1;
    else if (ft_strcmp(input_copy[0], "setenv") == 0)
        input_check->executed = 1;
    else if (ft_strcmp(input_copy[0], "unsetenv") == 0)
        input_check->executed = 1;
    else if (ft_strcmp(input_copy[0], "addenv") == 0)
        input_check->executed = 1;
}