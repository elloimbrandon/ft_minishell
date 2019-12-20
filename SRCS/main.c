/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandonf <brfeltz@student.42.us.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:16:50 by brfeltz           #+#    #+#             */
/*   Updated: 2019/12/19 23:00:10 by brandonf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"

void    display_prompt()
{
    
}

/* Signal Handler for SIGINT */
void sigint_handler(int sig_num)
{ 
    exit(0);
}

int		main(int argc, char **argv)
{
    t_info *info;

    info = (t_info*)ft_memalloc(sizeof(t_info));
    signal(SIGINT, sigint_handler); // consider inside while loop.
    while(1)
    {

    }
    return (0);
}