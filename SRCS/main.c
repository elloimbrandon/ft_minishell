/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:16:50 by brfeltz           #+#    #+#             */
/*   Updated: 2019/12/20 19:09:55 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"
#include <stdio.h> /////////////////// REMOVE

// void    display_prompt()
// {
    
// }

void    init_struct(t_env *env)
{
    env->env_copy = NULL;
}
void    copy_env(t_env *env)
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
/* Signal Handler for SIGINT */
// void sigint_handler(int sig_num)
// { 
//     exit(0);
// }

int		main(int argc, char **argv)
{
    t_env   *env;
    int i = 0;

    env = ft_memalloc(sizeof(t_env));
    init_struct(env);
    copy_env(env);
    //signal(SIGINT, sigint_handler); // consider inside while loop.
    while(1)
    {

    }
    return (0);
}