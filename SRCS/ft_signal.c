/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 01:51:14 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/15 00:50:50 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"

/*
** initializing the layout of  the command prompt and grabbing
** the current path of the directory we're working in to display
*/

int    display_prompt(void)
{
    char display[BUFF + 1];
    
    getcwd(display, BUFF);
    ft_printf("%s%s$>", KGRN, display);
    return(0);
}

char		*get_input(void)
{
	char	*buf;
    char    *temp;
	int		result;

    buf = ft_memalloc(sizeof(char*));
    temp = ft_memalloc(sizeof(char*));
	while ((result = read(0, buf, 1)) && (buf[0] != '\n'))
	{
        temp = ft_strjoin(temp, buf);
        if (!temp)
			temp = ft_strdup(buf);
        ft_strclr(buf);
	}
    if(buf[0] == '\n')
        temp[0] = *ft_strjoin(temp, buf);
    free(buf);
    return(temp);
}

/*
** sig number returned for cntl-c to interupt the program process
*/

void    sigint_handler(int sig_num)
{
    (void)sig_num; 
    ft_printf("\n");
    display_prompt();
}

/*
** sig number to completely exit the program and kill process
*/

void    sigquit_handler(int sig_num)
{
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