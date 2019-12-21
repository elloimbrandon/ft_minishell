/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:16:50 by brfeltz           #+#    #+#             */
/*   Updated: 2019/12/20 22:52:53 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"
#include <stdio.h> /////////////////// REMOVE

// void    **find_path(t_env *env)
// {
//     int i;

//     i= 0;
//     while(env->env_copy[i])
//     {
//         if(ft_strcmp(env->cmd_copy, "PATH") == 0)
//             return (ft_strsplit(env->env_copy, ':'));
//         i++;
//     }
//     return(ft_strsplit("", ';'));
// }

// void    ft_store_cmd(t_env *env)
// {
//     if (argc >= 1)
//     {
        
//     }

// }

/*
** setting up struct variables, setting some to 0 or NULL and allocating space
** for others for later use
*/

void    init_struct(t_env *env)
{
    env->input = NULL;
    env->env_copy = NULL;
    env->cmd_copy = ft_memalloc(sizeof(char **));
}

/* 
** copying evironment varibles from (**environ) to a 2d array we 
** created for parsing and later output if needed
*/

void    copy_env_var(t_env *env)
{
    extern char **environ;
    int i;
    int len;

    len = 0;
    i = -1;
    while(environ[len])
        len++;
    len--;
    env->env_copy = ft_memalloc(sizeof(char*) * (len + 1));
    while(environ[++i])
       env->env_copy[i] = ft_strdup(environ[i]);
    env->env_copy[i] = NULL;
}

/*
** initializing the layout of the command prompt and grabbing
** the current path of the directory we're working in to display
*/

int    display_prompt(void)
{
    char *display;
    int size = 1000;
 
    display = ft_memalloc(sizeof(char *) * size);
    getcwd(display, size);
    ft_printf("%s $>", display);
    free(display);
    return(0);
}

void    sigint_handler(int sig_num)
{
    (void)sig_num;
    ft_printf("\n");
    display_prompt();
}

void    display_get_input(t_env *env)
{
    while(1)
    {
        display_prompt();
        get_next_line(0, &(env->input));
        //ft_store_cmd(env);
    }
}

int        main(void)
{
    t_env   *env;

    env = ft_memalloc(sizeof(t_env));
    init_struct(env);
    copy_env_var(env);
    signal(SIGINT, sigint_handler);
    display_get_input(env);
}