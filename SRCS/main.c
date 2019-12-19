/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandonf <brfeltz@student.42.us.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:16:50 by brfeltz           #+#    #+#             */
/*   Updated: 2019/12/18 23:16:20 by brandonf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"


/* Signal Handler for SIGINT */
void sigint_handler(int sig_num)
{
    /* Reset handler to catch SIGINT next time.
       Refer http://en.cppreference.com/w/c/program/signal */
    printf("\n User provided signal handler for Ctrl+C \n");

    /*
    ** cleanup of the program like: free memory and exit
    */ 
    exit(0);
}

int		main(int argc, char **argv)
{
    t_info *info;

    info = (t_info*)ft_memalloc(sizeof(t_info));
    signal(SIGINT, sigint_handler);
    while(1)
    {

    }
    return (0);
}