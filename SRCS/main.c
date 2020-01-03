/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:16:50 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/02 22:10:32 by brfeltz          ###   ########.fr       */
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
    env->solo_exp = 0;
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


void    search_input(char **input_copy, t_cmd *input_check)
{
    int i;

    i = -1;
    while(input_copy[++i])
    {
        if(ft_strrchr(input_copy[i], '$')) // do the same for qoutes
            input_check->expansions += 1; // minus one away after execution so they dont stack
        else if(ft_strchr(input_copy[i], '~'))
            input_check->tilde += 1;  // minus one away after execution so they dont stack
    }
}

char    **split_by_space(char **input_copy)
{
    char **ret;
    int i;

    i = 0;
    while(input_copy[i])
        ret = ft_strsplit(input_copy[i++], ' ');
    ft_free_2d(input_copy);
    return(ret);
}

void    find_env_var(char *temp, t_env *env)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(temp);
    while(env->env_copy[i])
    {
        if(ft_strccmp(temp, env->env_copy[i], '=') == 0)
        {
            if(ft_strcmp(temp, env->env_copy[i]) == 0) // if the env values are the same change nothing
                break ;
            if(!env->solo_exp && temp[len -= 1] == '=') // if the command isnt just $USER and it had '=' at the end dont change value
                break ;
            if(env->solo_exp)
            {
                temp = ft_strdup(env->env_copy[i]);
                env->solo_exp = 0;
            }
            env->output = ft_strdup(temp);
            ft_strdel(&env->env_copy[i]);
            env->env_copy[i] = ft_strdup(env->output);
        }
        i++;
    }
}

void    handle_exp(char *input_copy, t_cmd *input_check, t_env *env)
{
    char *temp;
    int i;

    i = 0;
    while(input_copy[i] && input_check->expansions >= 1)
    {
        if(ft_strrchr(input_copy, '$'))
        {
            if(!ft_strrchr(input_copy, '='))
                env->solo_exp += 1;
            ft_memmove(&input_copy[i], &input_copy[i + 1], ft_strlen(input_copy) - i);
            temp = ft_strdup(input_copy);
            if(env->solo_exp)
                temp = ft_strcat(temp, "=");
            find_env_var(temp, env);
            free(temp);
        }
        i++;
    }
    printf("%s <-- output str for exp && new env value\n", env->output);
}

void    handle_cmds(char *input_copy, t_cmd *input_check, t_env *env)
{
    if(input_check->expansions >= 1)
    {   
        handle_exp(input_copy, input_check, env);
        input_check->expansions--;
    }
    else if(input_check->tilde >= 1)
    {
        printf("hit handle_tilde func\n");
        //handle_tilde(input_copy, input_check);
        input_check->tilde--;
    }
    else if(!input_check->expansions && !input_check->tilde)
    {
        printf("hit exec_cmd func\n");
        //exec_cmd(input_copy, input_check);
    }
}

void    ft_parse_cmd(t_env *env, t_cmd *input_check) // find a way to handle quoutes
{
   
    char **input_copy;
    int i;

    i = -1;
    input_copy = ft_strsplit(env->input, ';');
    free(env->input);
    // if (!input_copy)
    input_copy = split_by_space(input_copy); // split 2d array by spaces
    search_input(input_copy, input_check); // searching for expansions and tilde
    while(input_copy[++i])
        handle_cmds(input_copy[i], input_check, env); // add a check for struct 1d after expansion handle
    ft_free_2d(input_copy);
}

static char		*get_input(void)
{
	char	*buf;
    char    *temp;
	int		result;

	buf = ft_strnew(1);
    temp = ft_strnew(1);
    buf[1] = 0;
	while ((result = read(0, buf, 1)) && buf[0] != '\n')
	{
        temp = ft_strjoin(temp, buf);
		//if (!temp)
			//temp = ft_strdup(buf); // might not need these 2 lines
		ft_bzero(buf, ft_strlen(buf));
	}
    // if(buf[0] == '\n') // allows you to press enter EOF but wont parse_cmd and store input
    // {
    //     free(buf);
    //     return(0);
    // }
    free(buf);
    return(temp);
}

void    display_get_input(t_env *env, t_cmd *input_check)
{  
    while(!display_prompt())
    {
        env->input = get_input();
        // if(!env->input)
        //     continue ;
        // else
        if(env->input)
            ft_parse_cmd(env, input_check); /// seg faults on ctrl-d and with space now
    }
}

/// cntrl-d (no input like enter)
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