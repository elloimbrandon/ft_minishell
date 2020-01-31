/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 01:51:14 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/31 00:04:23 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"

/*
** initializing the layout of  the command prompt and grabbing
** the current path of the directory we're working in to display
*/

int    display_prompt(void)
{
    char ft_display[BUFF];// + 1];
    
    getcwd(ft_display, BUFF);
    ft_printf("%s%s$>", KGRN, ft_display);
    return(0);
}

/*
** sig number returned for cntl-c to interupt the program process
*/

void    sigint_handler(int sig_num)
{
    (void)sig_num;

    sig_num = 0;
    ft_printf("\n");
    display_prompt();
}

/*
** sig number to completely exit the program and kill process
*/

void    sigquit_handler(int sig_num)
{
    sig_num = 0; // changed
    ft_printf("\n%sGoodbye!\n", KMAG);
    exit(1);
}

/*
** hello message you receive when you start the program
*/

void    ft_hello(void)
{
    ft_printf("%s**My Mini shell!**\n", KCYN);
}