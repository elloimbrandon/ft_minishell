/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 19:52:35 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/31 19:52:46 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"

void			ft_already_exc(t_cmd *input_check, char **input_copy)
{
	if (ft_strcmp(input_copy[0], "echo") == 0)
		input_check->executed = 1;
	else if (ft_strcmp(input_copy[0], "cd") == 0)
		input_check->executed = 1;
	else if (ft_strcmp(input_copy[0], "env") == 0)
		input_check->executed = 1;
	else if (ft_strcmp(input_copy[0], "pwd") == 0)
		input_check->executed = 1;
	else if (ft_strcmp(input_copy[0], "exit") == 0)
		input_check->executed = 1;
	else if (ft_strcmp(input_copy[0], "setenv") == 0)
		input_check->executed = 1;
	else if (ft_strcmp(input_copy[0], "unsetenv") == 0)
		input_check->executed = 1;
	else if (ft_strcmp(input_copy[0], "addenv") == 0)
		input_check->executed = 1;
}

void			ft_local_exec(char **input_copy, t_cmd *input_check, t_env *env)
{
	char		*exec;
	struct stat buf;

	if (ft_strchr(input_copy[0], '/') != NULL && ft_strchr(input_copy[0], '.') != NULL)
	{
		if (lstat(input_copy[0], &buf) != -1)
		{
			if S_ISREG(buf.st_mode)
			{
				if (access(input_copy[0], X_OK) == 0)
				{
					exec = ft_strdup(input_copy[0]);
					ft_fork(exec, input_copy, env);
				}
				else
					ft_printf("%sshell: Permission denied: %s\n", KRED, input_copy[0]);
			}
			chdir(input_copy[0]);
		}
		else
			ft_printf("%sshell: no such file or directory: %s\n", KRED, input_copy[0]);
		input_check->executed = 1;
	}
}

void			check_system_cmd(char **input_copy, t_env *env)
{
	char		*hold;

	hold = get_path(env);
	if (hold)
		check_exec(hold, input_copy, env);
	else
		ft_printf("%sshell: command not found: %s\n", KRED, input_copy[0]);
	free(hold);
}

void			check_exec(char *hold, char **input_copy, t_env *env)
{
	char		**path;
	int			k;

	path = ft_strsplit(hold, ':');
	k = check_path_build_path(path, input_copy, env);
	ft_free_2d(path);
	if (k == 0 && ft_strcmp(input_copy[0], "\n") != 0)
		ft_printf("%sshell: command not found: %s\n", KRED, input_copy[0]);
}

int				check_path_build_path(char **path, char **input_copy, t_env *env)
{
	int			i;
	int			k;
	struct stat buf;
	char		*exec;

	i = 0;
	k = 0;
	while(path[++i])
	{
		exec = build_path(input_copy[0], path[i]);
		if (lstat(exec, &buf) != 1)
		{
			if (access(exec, X_OK) == 0)
			{
				ft_fork(exec, input_copy, env);
				k = 1;
				break ;
			}
		}
		free(exec);
	}
	return (k);
}
