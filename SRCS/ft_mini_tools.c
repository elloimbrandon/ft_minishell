/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 22:31:41 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/03 22:35:32 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"

/*
** removes the spaces from input and stores them into
** new 2d array so we can work with array's without spaces
*/

char    **split_by_space(char **input_copy)
{
    char **ret;
    int i;

    i = 0;
    while(input_copy[i])
        ret = ft_strsplit(input_copy[i++], ' ');
    ft_free_2d(input_copy);
    return(ret);
}

/*
** searches through input strings to find a '$' or
** a '~' symbol and adds a count to structs so we can
** modify the output later accordingly
*/

void    search_input(char **input_copy, t_cmd *input_check)
{
    int i;

    i = -1;
    while(input_copy[++i])
    {
        if(ft_strrchr(input_copy[i], '$')) // do the same for qoutes
            input_check->expansions += 1; // minus one away after execution so they dont stack
        else if(ft_strchr(input_copy[i], '~'))
            input_check->tilde += 1;  // minus one away after execution so they dont stack
    }
}