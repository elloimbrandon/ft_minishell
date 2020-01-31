/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:16:50 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/30 23:51:26 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"

/*
** test with csh
*/
 
void     check_bultin(char **input_copy, t_cmd *input_check, t_env *env)
{
    input_check->printed_errors = 0;
    check_cd_cmd(input_copy, input_check, env);
    check_env_cmd(input_copy, input_check, env);
    check_pwd_cmd(input_copy, input_check, env);
    check_exit_cmd(input_copy, input_check, env);
    check_echo_cmd(input_copy, input_check, env);
    check_setenv(input_copy, input_check, env);
    check_unsetenv(input_copy,input_check,env);
}

void    ft_parse_input(t_env *env, t_cmd *input_check, char **input_copy)
{
    int i;

    i = -1;
    while(input_copy[++i])
    {
        check_env(input_copy[i], input_check);
        check_tilde(input_copy[i], input_check);
        check_qoutes(input_copy[i], input_check);
        if(input_check->expansions == 1)
        {
            input_copy[i] = exp_tilde_check(input_copy[i], input_check, env);
            input_check->expansions = 0;
        }
        if(input_check->tilde == 1)
        {
            if(!input_copy[1])
            {
                handle_tilde(input_copy[i], input_check, env);
                chdir(env->tilde_hold);
                free(env->tilde_hold);
                input_check->executed = 1;
            }
            else
                input_copy[i] = exp_tilde_check(input_copy[i], input_check, env);
            input_check->tilde = 0;
        }
    }
}

void    ft_parse_mini(t_env *env, t_cmd *input_check)
{
    char **input_copy;
    char **input;
    int i;
    int total_wrds;

    i = -1;
    if(!(input = ft_strsplit(env->input, ';')))
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
    while (input[++i])
    {
        if(!(input_copy = ft_strsplit(input[i], ' ')))
        {
            ft_free_2d(input_copy);
            return ;
        }
        ft_parse_input(env, input_check, input_copy);
        check_bultin(input_copy, input_check, env);
        ft_already_exc(input_check, input_copy);
        ft_local_exec(input_copy, input_check, env);
        if(input_check->executed == 0)
            check_system_cmd(input_copy, input_check, env);
        input_check->executed = 0;
        if (ft_strcmp(input_copy[0], "cat") == 0)
            ft_printf("\n");
        ft_free_2d(input_copy);
    }
    ft_free_2d(input);
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
	while ((result = read(0, buf, 1)) && (buf[0] != '\n'))
	{
        leak = temp;
        temp = ft_strjoin(temp, buf);
        free(leak);
        count = 1;
	}
    if(buf[0] == '\n' && count != 1)
        env->input = ft_strdup(buf);
    else
        env->input = ft_strdup(temp);
    free(buf);
    free(temp);
    return(result == 0 ? 1: 0);
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
    while(!display_prompt()) 
    {
        if(get_input(env) == 0)
        {
            if(env->input[0] != '\n')
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
    return(0);
}