/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 23:34:46 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/31 19:04:25 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../HEADERS/ft_minishell.h"


void     ft_print_2d(char **two_d)
{
    int i;

    i = -1;
    while(two_d[++i])
        ft_printf("%s%s\n", KBLU, two_d[i]);
}

void    print_path(void)
{
    char display[BUFF];
    
    getcwd(display, BUFF);
    ft_printf("%s\n", display);
}

void    print_errors(char *input_copy, t_cmd *input_check, int i)
{
    if (i == 1)
        ft_printf("%scd: no such file or directory: %s\n", KRED, input_copy);
    else if (i == 2)
        ft_printf("%scd: not a directory: %s\n", KRED, input_copy);
    else if (i == 3)
        ft_printf("%scd: too many arguments\n", KRED);
    else if (i == 4)
        ft_printf("%scd: string not in pwd: %s\n", KRED, input_copy);
    input_check->printed_errors++;
    
}

void     ft_print_echo(char **input_copy, t_cmd *input_check)
{
    int i;

    i = 0;
    while(input_copy[++i])
    {
        if (input_check->qoutes)
            ft_remove_qoutes(input_copy[i]);
        if (!input_check->qoutes)
            ft_printf("%s", input_copy[i]);
        if (input_copy[i + 1])
            ft_printf(" ");
    }
    ft_printf("\n");
}

int    ft_same_cmd(char *exec, char **input_copy)
{
    int i;
    int len;
    char *temp;

    i = 0;
    temp = NULL;
    len = ft_strlen(exec);
    while(exec[len] != '/')
        len--;
    len++;
    temp = ft_strdup(exec + len);
    if (ft_strcmp(input_copy[0], temp) != 0)
    {
        free(exec);
        free(temp);
        return (1);
    }
    free(temp);
    return (0);
}