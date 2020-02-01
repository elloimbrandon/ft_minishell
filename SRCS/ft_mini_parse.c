/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 18:30:59 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/31 20:20:35 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"

void	ft_parse_mini(t_env *env, t_cmd *input_check)
{
	char	**input;
	int		i;
	int		total_wrds;

	i = -1;
	if (!(input = ft_strsplit(env->input, ';')))
	{
		free(env->input);
		return ;
	}
	free(env->input);
	total_wrds = ft_count_words_2d(input);
	if (total_wrds <= 0)
	{
		ft_free_2d(input);
		return ;
	}
	ft_parse_mini_2(env, input_check, input);
	ft_free_2d(input);
}

void	ft_parse_mini_2(t_env *env, t_cmd *input_check, char **input)
{
	char	**input_copy;
	int		i;

	i = -1;
	while (input[++i])
	{
		if (!(input_copy = ft_strsplit(input[i], ' ')))
		{
			ft_free_2d(input_copy);
			return ;
		}
		ft_parse_input(env, input_check, input_copy);
		check_bultin(input_copy, input_check, env);
		ft_already_exc(input_check, input_copy);
		ft_local_exec(input_copy, input_check, env);
		if (input_check->executed == 0)
			check_system_cmd(input_copy, env);
		input_check->executed = 0;
		ft_free_2d(input_copy);
	}
}

void	ft_parse_input(t_env *env, t_cmd *input_check, char **input_copy)
{
	int i;

	i = -1;
	while (input_copy[++i])
	{
		check_env_tilde_qoutes(input_copy[i], input_check);
		if (input_check->expansions == 1)
		{
			input_copy[i] = exp_tilde_check(input_copy[i], input_check, env);
			input_check->expansions = 0;
		}
		if (input_check->tilde == 1)
		{
			if (!input_copy[1])
				is_tilde_qoutes(input_copy[i], env, input_check);
			else
				input_copy[i] = exp_tilde_check(input_copy[i],
					input_check, env);
			input_check->tilde = 0;
		}
	}
}

void	is_tilde_qoutes(char *input_copy, t_env *env, t_cmd *input_check)
{
	handle_tilde(input_copy, env);
	chdir(env->tilde_hold);
	free(env->tilde_hold);
	input_check->executed = 1;
}

void	check_env_tilde_qoutes(char *input_copy, t_cmd *input_check)
{
	check_env(input_copy, input_check);
	check_tilde(input_copy, input_check);
	check_qoutes(input_copy, input_check);
}
