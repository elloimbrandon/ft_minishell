/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 01:51:14 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/31 19:05:09 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"

int    display_prompt(void)
{
    char ft_display[BUFF];
    
    getcwd(ft_display, BUFF);
    ft_printf("%s%s$>", KGRN, ft_display);
    return (0);
}

void    sigint_handler_2(int sig_num)
{
    sig_num = 0;
    ft_printf("\n");
}

void    sigint_handler(int sig_num)
{
    sig_num = 0;
    ft_printf("\n");
    display_prompt();
}

void    sigquit_handler(int sig_num)
{
    sig_num = 0;
    ft_printf("\n%sGoodbye!\n", KMAG);
    exit(1);
}

void    ft_hello(void)
{
    ft_printf("%s**My Mini shell!**\n", KCYN);
}