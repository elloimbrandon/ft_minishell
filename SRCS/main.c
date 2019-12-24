/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:16:50 by brfeltz           #+#    #+#             */
/*   Updated: 2019/12/24 00:28:13 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"
#include <stdio.h> /////////////////// REMOVE


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
void    init_input_check(t_cmd *input_check)
{
    input_check->echo = 0;
    input_check->exit = 0;
    input_check->cd = 0;
    input_check->set_e = 0;
    input_check->unset_e = 0;
    input_check->qoutes = 0;
}

void    check_cmds(char *temp)
{
    
}

void    ft_parse_cmd(t_env *env)
{
    t_cmd *input_check;
    char **temp;
    int len;
    int i;

    i = 0;
    len = 0;
    input_check = ft_memalloc(sizeof(t_cmd));
    while(env->input[len])
        len++;
    len--;
    while(env->input)

    // init_input_check(input_check);
    // check_cmds(temp);
    // free(temp);
}
void    display_get_input(t_env *env)
{
    while(1)
    {
        display_prompt();
        get_next_line(0, &(env->input));
        ft_parse_cmd(env);
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