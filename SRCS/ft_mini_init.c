/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 22:28:46 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/31 20:00:07 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"

void	init_structs(t_env *env, t_cmd *input_check)
{
	extern char **environ;

	env->env_copy = copy_2d_array(environ);
	env->input = NULL;
	env->exp_hold = NULL;
	env->tilde_hold = NULL;
	input_check->executed = 0;
	input_check->qoutes = 0;
	input_check->tilde = 0;
	input_check->expansions = 0;
	input_check->printed_errors = 0;
}
