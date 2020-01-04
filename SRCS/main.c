/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:16:50 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/04 00:55:09 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"
#include <stdio.h> /////////////////// REMOVE


void    ft_parse_cmd(t_env *env, t_cmd *input_check) // find a way to handle quoutes // output might have to be a 2d array
{
   
    char **input_copy;
    int i;

    i = -1;
    input_copy = ft_strsplit(env->input, ';');
    free(env->input);
    input_copy = split_by_space(input_copy); // split 2d array by spaces
    search_input(input_copy, input_check); // searching for expansions and tilde
    while(input_copy[++i])
    {
        handle_exp_tilde(input_copy[i], input_check, env); // add a check for struct 1d after expansion handle
        check_commands(input_copy[i], input_check, env); // WORKING ON THIS ATM
        //execute_commands()
    }
    ft_free_2d(input_copy);
}

void    check_commands(char *input_copy, t_cmd *input_check, t_env *env)
{
    // maybe check and see if tilde and expansions are 0??
    if (ft_strcmp(input_copy, "cd") == 0)
        input_check->cd += 1;
    else if (ft_strcmp(input_copy, "env") == 0)
        input_check->env += 1;
    else if (ft_strcmp(input_copy, "exit") == 0)
        input_check->exit += 1;
    else if (ft_strcmp(input_copy, "env") == 0)
        input_check->echo += 1;
    else if (ft_strcmp(input_copy, "setenv") == 0)
        input_check->set_e += 1;
    else if (ft_strcmp(input_copy, "unsetenv") == 0)
        input_check->unset_e += 1;
    else
    {
        printf("its a system command\n");
        //check_sys_cmd(input_copy, input_check, env);
    }
}

// void    check_sys_cmd(char *input_copy, t_cmd *input_check, t_env *env)
// {
    
// }

static char		*get_input(void)
{
	char	*buf;
    char    *temp;
	int		result;

    buf = ft_memalloc(sizeof(char*));
    temp = ft_memalloc(sizeof(char*));
	while ((result = read(0, buf, 1)) && (buf[0] != '\n'))
	{
        temp = ft_strjoin(temp, buf);
        if (!temp)
			temp = ft_strdup(buf);
        ft_strclr(buf);
	}
    if(buf[0] == '\n')
        temp[0] = *ft_strjoin(temp, buf); // works?? 
    free(buf);
    return(temp);
}

void    display_get_input(t_env *env, t_cmd *input_check)
{  
    while(!display_prompt())
    {
        env->input = get_input();
        if(env->input)
            ft_parse_cmd(env, input_check); /// seg faults on ctrl-d
        ft_strclr(env->input);
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
    return(0);
}

// int        main(void)
// {
//     t_env   *env;

//     env = ft_memalloc(sizeof(t_env));
//     init_struct(env);
//     int i = 0;
//     while(env->env_copy[i])
//     {
//         printf("%s", env->env_copy[i]);
//         printf("\n");
//         i++;
//     }
//     return(0);
// }