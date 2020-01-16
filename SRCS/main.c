/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:16:50 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/15 20:13:19 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"

/*
** test with csh
*/

/*
** to do's: break up functions into files, norm, check for leaks and fix envunset free problem /// think about getting rid of addenv
*/

void     check_bultin(char **input_copy, t_cmd *input_check, t_env *env)
{
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
        check_set_unset_env(input_copy[i], input_check);
        if(input_check->expansions == 1)
            input_copy[i] = exp_tilde_check(input_copy[i], input_check, env);
        if(input_check->tilde == 1)
        {
            input_copy[i] = exp_tilde_check(input_copy[i], input_check, env);
            if(!input_copy[1])
                chdir(input_copy[0]);
        }
    }
}

// void    free_mini(char **input_copy, t_cmd *input_check, t_env *env)
// {
//     ft_free_2d(input_copy);
// }

void    ft_parse_mini(t_env *env, t_cmd *input_check)
{
    char **input_copy;

    input_copy = ft_strsplit(env->input, ';');
    input_copy = split_by_space(input_copy);
    ft_parse_input(env, input_check, input_copy);
    ft_zero_out(input_check);
    check_bultin(input_copy, input_check, env);
    ft_already_exc(input_check, input_copy);
    ft_local_exec(input_copy, input_check, env);
    if(input_check->executed == 0)
        check_system_cmd(input_copy, input_check, env);
    input_check->executed = 0;
    if (ft_strcmp(input_copy[0], "cat") == 0)
        ft_printf("\n");
    ft_free_2d(input_copy);
    //free_mini(input_copy, input_check, env);
}


void    display_get_input(t_env *env, t_cmd *input_check)
{
    while(!display_prompt())
    {
        env->input = get_input();
        if(env->input)
            ft_parse_mini(env, input_check); /// seg faults on ctrl-d
        free(env->input);
    }
}

int        main(void)
{
    t_env   *env;
    t_cmd   *input_check;
    char    *temp;

    temp = NULL;
    env = ft_memalloc(sizeof(t_env));
    input_check = ft_memalloc(sizeof(t_cmd));
    init_structs(env, input_check);
    ft_hello();
    signal(SIGQUIT, sigquit_handler);
    signal(SIGINT, sigint_handler);
    display_get_input(env, input_check);
    ft_free_2d(env->env_copy); // might need to move
    return(0);
}