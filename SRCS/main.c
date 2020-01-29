/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:16:50 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/28 22:23:27 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"

/*
** test with csh
*/

/*
** to do's: break up functions into files, norm, check for leaks and fix envunset free problem /// think about getting rid of addenv
*/

// static char		*get_input(void)
// {
// 	char	*buf;
//     char    *temp;
//     char    *leak; // added
// 	int		result;

//     buf = ft_memalloc(sizeof(char*) + 1);
//     temp = ft_memalloc(sizeof(char*) + 1);
// 	while ((result = read(0, buf, 1)) && (buf[0] != '\n'))
// 	{
//         leak = temp; //added
//         temp = ft_strjoin(temp, buf);
//         if (!temp)
// 			temp = ft_strdup(buf);
//         free(leak); // added 
//         ft_strclr(buf);
// 	}
//     if(buf[0] == '\n')
//         *temp = *ft_strjoin(temp, buf);
//     free(buf); // possibly make struct to clear temp outside of function??
//     return(temp);
// }

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
        if(input_check->expansions == 1)
        {
            input_copy[i] = exp_tilde_check(input_copy[i], input_check, env);
            input_check->expansions = 0;
        }
        if(input_check->tilde == 1)
        {
            input_copy[i] = exp_tilde_check(input_copy[i], input_check, env);
            if(!input_copy[1])
                chdir(input_copy[0]);
        }
    }
}

void    ft_parse_mini(t_env *env, t_cmd *input_check)
{
    char **input_copy;

    input_copy = ft_strsplit(env->input, ';');
    free(env->input);
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
}

static void		get_input(t_env *env)
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
    while(!display_prompt())
    {
        // maybe allocate env var here and free after
        // env->input = get_input();
        get_input(env);
        if(env->input[0] != '\n')
            ft_parse_mini(env, input_check); /// seg faults on ctrl-d
        else
            free(env->input);
    }
    ft_free_2d(env->env_copy); // might need to move // free env var copy
    free(env); // testing 
    free(input_check); // testing
    return(0);
}