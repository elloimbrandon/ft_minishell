/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 18:27:52 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/31 20:41:49 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"

void	check_unsetenv(char **input_copy, t_env *env)
{
	if (!input_copy[1] && ft_strcmp(input_copy[0], "unsetenv") == 0)
		ft_printf("%sunsetenv: not enough arguments\n", KRED);
	else if (ft_strcmp(input_copy[0], "unsetenv") == 0 && input_copy[2])
		ft_printf("%ssetenv: too many arguments\n", KRED);
	else if (input_copy[1] && ft_strcmp(input_copy[0], "unsetenv") == 0)
	{
		if (find_unset_var(input_copy, env) == 0)
			ft_printf("%sunsetenv: variable doesnt exist: %s\n", KRED,
				input_copy[1]);
	}
}

int		unset_env(char *temp, t_env *env, int k)
{
	int		i;
	char	*swap;

	i = -1;
	swap = NULL;
	while (env->env_copy[++i])
	{
		if (ft_strccmp(temp, env->env_copy[i], '=') == 0)
		{
			free(env->env_copy[i]);
			k = 1;
		}
		if (k == 1 && env->env_copy)
		{
			swap = env->env_copy[i + 1];
			env->env_copy[i] = swap;
		}
	}
	return (k);
}

int		find_unset_var(char **input_copy, t_env *env)
{
	int		k;
	char	*temp;

	k = 0;
	temp = ft_strdup(input_copy[1]);
	ft_strcat(temp, "=");
	if (unset_env(temp, env, k) == 1)
	{
		free(temp);
		return (1);
	}
	free(temp);
	return (0);
}
