/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 22:28:46 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/15 00:27:01 by brfeltz          ###   ########.fr       */
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
    env->exp_hold = NULL;
    env->tilde_hold = NULL;
    input_check->executed = 0;
    input_check->add_env = 0;
    input_check->set_e = 0;
    input_check->unset_e = 0;
    input_check->qoutes = 0;
    input_check->tilde = 0;
    input_check->expansions = 0;
    input_check->printed_errors = 0;
}

void    ft_zero_out(t_cmd *input_check)
{
    input_check->add_env = 0;
    input_check->set_e = 0;
    input_check->unset_e = 0;
    input_check->expansions = 0;
    input_check->tilde = 0;
    input_check->printed_errors = 0;
}