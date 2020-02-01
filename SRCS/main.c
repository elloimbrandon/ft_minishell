/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:16:50 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/31 19:05:29 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"

/*
** test with csh
*/

void    ft_fork(char *exec, char **input_copy, t_env *env)
{
    pid_t child_p;

    child_p = fork();
    signal(SIGINT,sigint_handler_2);
    if (child_p == 0)
        execve(exec, input_copy, env->env_copy);
    else if (child_p < 0)
        ft_printf("%sshell: could not create process\n", KRED);
    free(exec);
    wait(&child_p);
}

int		get_input(t_env *env)
{
    char    *buf;
    char    *temp;
    char    *leak;
    int     count;
	int		result;

    count = 0;
    buf = ft_memalloc(sizeof(char*) + 1);
    temp = ft_memalloc(sizeof(char*) + 1);
	while((result = read(0, buf, 1)) && (buf[0] != '\n'))
	{
        leak = temp;
        temp = ft_strjoin(temp, buf);
        free(leak);
        count = 1;
	}
    if (buf[0] == '\n' && count != 1)
        env->input = ft_strdup(buf);
    else
        env->input = ft_strdup(temp);
    free(buf);
    free(temp);
    return (result == 0 ? 1 : 0);
}

void       ft_minishell(t_env *env, t_cmd *input_check)
{
    while(!display_prompt())
    {
        if (get_input(env) == 0)
        {
            if (env->input[0] != '\n')
                ft_parse_mini(env, input_check);
            else
                free(env->input);
        }
        else
        {
            free(env->input);
            ft_printf("\n");
        }
    }
    ft_free_2d(env->env_copy);
}

int        main(void)
{
    t_env   *env;
    t_cmd   *input_check;

    env = ft_memalloc(sizeof(t_env));
    input_check = ft_memalloc(sizeof(t_cmd));
    init_structs(env, input_check);
    ft_hello();
    signal(SIGQUIT, sigquit_handler);
    signal(SIGINT, sigint_handler);
    ft_minishell(env, input_check);
    return (0);
}