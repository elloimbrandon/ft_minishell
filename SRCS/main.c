/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:16:50 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/07 21:41:21 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"
#include <stdio.h> /////////////////// REMOVE

static void    check_bultin(char *input_copy, t_cmd *input_check, t_env *env)
{
    if(input_check->cd >= 1)
        printf("hit cd\n");
    if(input_check->env >= 1)
        printf("hit env\n");
    if(input_check->exit >= 1)
        printf("hit exit\n");
    if(input_check->echo >= 1)
        printf("hit echo\n");
    if(input_check->pwd >= 1)
        printf("hit pwd\n");
    if(input_check->set_e >= 1)
        printf("hit set_e\n");
    if(input_check->unset_e >= 1)
        printf("hit unset_e\n");
}

void    ft_parse_cmd(t_env *env, t_cmd *input_check) // find a way to handle quoutes // output might have to be a 2d array
{
   
    char **input_copy;
    int i;

    i = -1;
    input_copy = ft_strsplit(env->input, ';');
    free(env->input);
    input_copy = split_by_space(input_copy); // split 2d array by spaces
    while(input_copy[++i])
    {
        search_input(input_copy[i], input_check);
        if(input_check->expansions >= 1)
        {
            handle_exp_tilde(input_copy[i], input_check, env); // add a check for struct 1d after expansion handle
            input_copy[i] = ft_strdup(env->output);
            free(env->output);
        }
        check_bultin(input_copy[i], input_check, env);
        //check_sys_cmd(input_copy[i], input_check, env);
        printf("%s <--- command\n", input_copy[i]);
    }
    //printf("%s <-- output\n", env->output);
    ft_free_2d(input_copy);
}

static char    *get_path(char *temp, t_env *env)
{
    int i;

    i = -1;
    while(env->env_copy[++i])
    {
        if (strncmp("PATH=", env->env_copy[i], 5) == 0)
        temp = ft_strdup(env->env_copy[i] + 5);
        temp = ft_strdup(temp);
    }
    return(temp);
}

static void     ft_print_2d(char **two_d)
{
    int i;

    i = -1;
    while(two_d[++i])
        printf("%s <-- current path 2d\n", two_d[i]);
}

void    check_sys_cmd(char *input_copy, t_cmd *input_check, t_env *env)
{
    char *path;
    //struct stat buf;

    //path = ft_memalloc(sizeof(char*));    //path = ft_memalloc(sizeof(char**))
    //path = get_path(path, env);
    //path = ft_strsplit(path , ':');
    // ft_print_2d(input_copy);
    //if(path)
        //ft_which_cmd(path, env); // throw a check to see if path exists
    //ft_print_path(path);
    //ft_print_2d(env->env_copy);
    
}

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