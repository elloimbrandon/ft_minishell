/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:16:50 by brfeltz           #+#    #+#             */
/*   Updated: 2019/12/20 01:42:06 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"

void    display_prompt()
{
    
}

void    copy_env(t_env *env)
{
    extern char **environ;
    int i;

    i = 0;
    while((*environ)[i])
    {
        
        i++;
    }
    
}
/* Signal Handler for SIGINT */
void sigint_handler(int sig_num)
{ 
    exit(0);
}

int		main(int argc, char **argv)
{
    t_env   *env;
    t_env   *list;

    ft_bzero(&env,(sizeof(t_env)));
    ft_bzero(&list,(sizeof(t_env)));
    copy_env(&env);
    signal(SIGINT, sigint_handler); // consider inside while loop.
    while(1)
    {

    }
    return (0);
}