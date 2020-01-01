/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:16:50 by brfeltz           #+#    #+#             */
/*   Updated: 2019/12/28 03:05:53 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"
#include <stdio.h> /////////////////// REMOVE


/*
** copying evironment varibles from (**environ) to a 2d array we 
** created for parsing and later output if needed
** setting up struct variables, setting some to 0 or NULL and allocating space
** for others for later use
*/

void    init_structs(t_env *env, t_cmd *input_check)
{
    extern char **environ;

    env->env_copy = copy_2d_array(environ);
    env->cmd_copy = ft_memalloc(sizeof(char **));
    env->input = NULL;
    env->output = NULL;
    input_check->echo = 0;
    input_check->exit = 0;
    input_check->cd = 0;
    input_check->set_e = 0;
    input_check->unset_e = 0;
    input_check->qoutes = 0;
    input_check->tilde = 0;
    input_check->expansions = 0;
    input_check->nbr_of_cmds = 0;
}

// void    handle_cmds(char *input_copy, t_cmd *input_check, t_env *env)
// {
//     if(input_check->expansions >= 1)
//     {   
//         printf("hit handle_exp func\n");
//         handle_exp(input_copy, input_check, env);
//     }
//     else if(input_check->tilde >= 1)
//     {
//         printf("hit handle_tilde func\n");
//         //handle_tilde(input_copy, input_check);
//     }
//     else if(!input_check->expansions && !input_check->tilde)
//     {
//         printf("hit exec_cmd function \n");
//         //exec_cmd(input_copy, input_check);
//     }
// }

// void    handle_exp(char *input_copy, t_cmd *input_check, t_env *env)
// {
//     char *temp;
//     int i;

//     i = 0;
//     while(input_copy[i] && input_check->expansions >= 1)
//     {
//         if(ft_strrchr(input_copy, '$'))
//         {
//             ft_memmove(&input_copy[i], &input_copy[i + 1], ft_strlen(input_copy) - i);
//             temp = ft_memalloc(sizeof(char*) * ft_strlen(input_copy));
//             temp = ft_strcpy(temp, input_copy);
//             temp = ft_strcat(temp, "=");
//             find_env_var(temp, env); // place in a local? or stuct 1d array for return mmmmm??
//             input_check->expansions--;
//             free(temp);
//         }
//     }
// }

// void    find_env_var(char *temp, t_env *env)
// {
//     int i;
//     int len;

//     i = 0;
//     len = ft_strlen(temp);
//     while(env->env_copy[i])
//     {
//         if(ft_strccmp(temp, env->env_copy[i], '=') == 0)
//         {
//             len += ft_strlen(env->env_copy[i]);
//             env->output = ft_memalloc(sizeof(char *) + len);
//             env->output = ft_strcpy(env->output, temp);
//             ft_strcat(env->output, env->env_copy[i]);
//         }
//         i++;
//     }
// }

// void    search_input(char *input_copy, t_cmd *input_check)
// {
//     if(ft_strrchr(input_copy, '$')) // do the same for qoutes
//     {
//         input_check->expansions += 1; // minus one away after execution
//         printf("its regestering a struct hit for $\n");
//     }
//     else if(ft_strchr(input_copy, '~'))
//         input_check->tilde += 1;  // minus one away after execution
// }

// char    **split_by_space(char *input_copy)
// {
//     char **ret;
//     int i;

//     i = 0;
//     while(input_copy[i])
//     {
//         ret = ft_strsplit(&input_copy[i], ' ');
//         i++;
//     }
//     free(input_copy);
//     return(ret);
// }

void    ft_parse_cmd(t_env *env, t_cmd *input_check) // find a way to handle quoutes
{
   
    char **input_copy;
    int i;

    i = 0;
    input_copy = ft_strsplit(env->input, ';');
    free(env->input);
    if (!input_copy)
    {
        printf("somthings wrong\n");
        exit(1);
    }
    // while(input_copy[i])
    // {
    //     input_copy = split_by_space(input_copy[i]);
    //     search_input(input_copy[i], input_check); // searching for expansions and tilde
    //     handle_cmds(input_copy[i], input_check, env); // add a check for struct 1d after expansion handle
    //     i++;
    // }
    ft_free_2d(input_copy);
}

void    display_get_input(t_env *env, t_cmd *input_check) // changed from void
{
    // while(get_next_line(0, &(env->input)) == 1)
    while(1)
    {
        display_prompt();
        get_next_line(0, &(env->input));
        if(env->input)
            ft_parse_cmd(env, input_check);
    }
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