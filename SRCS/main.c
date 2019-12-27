/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:16:50 by brfeltz           #+#    #+#             */
/*   Updated: 2019/12/26 20:28:27 by brfeltz          ###   ########.fr       */
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
    input_check->nbr_of_cmds = 0;
}
// int     double_len(char **str)
// {
//     int len;

//     len = 0;
//     while(str[len])
//         len++;
//     len--;
//     return(len);
// }
// void    check_cmds(char *temp)
// {
    
// }

// void    ft_parse_cmd(t_env *env)
// {
//     t_cmd *input_check;
//     char **temp;
//     int len;
//     int i;

//     i = 0;
//     input_check = ft_memalloc(sizeof(t_cmd));
//     temp = ft_memalloc(sizeof(char **) + 1);
    // while(env->input[i]) // while going through the string, if we find a space or semi store that part of the array from 0 into 2d
    // {
    //     if (!(env->input[i] == ' ') || !(env->input[i] == ';'))
    //         i++;
    //     else
    //     {
    //         temp[k] = ft_strndup(env->input, i);
    //         i++;
    //         k++;
    //     }
    // }
    // init_input_check(input_check);
    // check_cmds(temp);
    // free(temp);
// }

int     check_exit(t_env *env)
{
    if (ft_strcmp(env->input, "exit") == 0)
    {
        free(env->input);
        free(env);
        return(1);
    }
    else
        return(0);
}
void    display_get_input(t_env *env)
{
    while(ft_printf("Ft_Minishell") > 0 && get_next_line(0, &(env->input)) == 1)
    {
        display_prompt();
        if (check_exit(env) == 1)
            break ;
        //ft_parse_cmd(env);
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