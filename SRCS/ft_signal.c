/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 01:51:14 by brfeltz           #+#    #+#             */
/*   Updated: 2019/12/28 02:24:07 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"

/*
** initializing the layout of  the command prompt and grabbing
** the current path of the directory we're working in to display
*/

int    display_prompt(void)
{
    char *display;
    int size = 1000;
 
    display = ft_memalloc(sizeof(char *) * size);
    getcwd(display, size);
    ft_printf("%s$>>", display);
    free(display); 
    return(0);
}

void    sigint_handler(int sig_num)
{
    (void)sig_num;
    ft_printf("\n");
    display_prompt();
}

void    sigquit_handler(int sig_num)
{
    ft_printf("\n%sGoodbye!\n", KMAG);
    exit(1);
}

void    ft_hello(void)
{
    ft_printf("%s**My Mini shell!**\n", KCYN);
}