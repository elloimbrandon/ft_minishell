/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 22:28:46 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/03 22:29:50 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"

/*
** copying evironment varibles from (**environ) to a 2d array we 
** created for parsing and later output if needed
** setting up struct variables, setting some to 0 or NULL and allocating space
** for others for later use
*/

void    init_structs(t_env *env, t_cmd *input_check)
{
    extern char **environ;

    env->env_copy = copy_2d_array(environ);
    env->cmd_copy = ft_memalloc(sizeof(char **));
    env->input = NULL;
    env->output = NULL;
    env->solo_exp = 0;
    input_check->echo = 0;
    input_check->exit = 0;
    input_check->cd = 0;
    input_check->set_e = 0;
    input_check->unset_e = 0;
    input_check->qoutes = 0;
    input_check->tilde = 0;
    input_check->expansions = 0;
    input_check->nbr_of_cmds = 0;
}