/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 22:31:41 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/09 00:31:59 by brfeltz          ###   ########.fr       */
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

void     search_input(char *input_copy, t_cmd *input_check)  // do the same for qoutes
{
    if (ft_strrchr(input_copy, '$'))
        input_check->expansions += 1;
    else if (ft_strchr(input_copy, '~'))
        input_check->tilde += 1;
    // else if (ft_strchr(input_copy, '"'))
    //     input_check->qoutes += 1;
    else if (ft_strcmp(input_copy, "cd") == 0)
        input_check->cd += 1;
    else if (ft_strcmp(input_copy, "env") == 0)
        input_check->env += 1;
    else if (ft_strcmp(input_copy, "exit") == 0)
        input_check->exit += 1;
    else if (ft_strcmp(input_copy, "pwd") == 0)
        input_check->pwd += 1;
    else if (ft_strcmp(input_copy, "setenv") == 0)
        input_check->set_e += 1;
    else if (ft_strcmp(input_copy, "unsetenv") == 0)
        input_check->unset_e += 1;
}