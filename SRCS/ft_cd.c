/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 18:44:17 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/31 19:26:37 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"

void		ft_cd(char **input_copy, t_cmd *input_check, t_env *env)
{
	char		*temp;

	if (!input_copy[1] || ft_strcmp(input_copy[1], "--") == 0)
	{
		temp = find_home(env);
		chdir(temp);
		free(temp);
	}
	else if (ft_strcmp(input_copy[1], "-") == 0)
	{
		temp = find_old_pwd(env);
		chdir(temp);
		ft_printf("~%s\n", temp);
		free(temp);
	}
	else if (input_copy[1] && !input_copy[2])
		check_cd_dir(input_copy, input_check);
	else if (input_copy[2] && !input_copy[3])
		print_errors(input_copy[1], input_check, 4);
	else if (input_copy[3] && !input_copy[4])
		print_errors(input_copy[1], input_check, 3);
	else
		print_errors(input_copy[1], input_check, 3);
}

void		check_cd_dir(char **input_copy, t_cmd *input_check)
{
	DIR			*dir;
	struct stat sbuf;

	lstat(input_copy[1], &sbuf);
	if (!(dir = opendir(input_copy[1])))
	{
		if (S_ISREG(sbuf.st_mode))
			print_errors(input_copy[1], input_check, 2);
		else if (!S_ISREG(sbuf.st_mode))
			print_errors(input_copy[1], input_check, 1);
	}
	else
	{
		chdir(input_copy[1]);
		closedir(dir);
	}
}
