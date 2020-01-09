/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandonf <brfeltz@student.42.us.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:16:50 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/09 03:54:19 by brandonf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"
#include <stdio.h> /////////////////// REMOVE


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

static void    print_errors(char *input_copy, int i)
{
    if (i == 1)
        ft_printf("cd: no such file or directory: %s\n", input_copy);
    else if (i == 2)
        ft_printf("cd: not a directory: %s\n", input_copy);
    else if (i == 3)
        ft_printf("cd: many arguments\n");
    else if (i == 4)
        ft_printf("cd: string not in pwd: %s\n", input_copy);
}

static void     ft_print_2d(char **two_d)
{
    int i;

    i = -1;
    while(two_d[++i])
        ft_printf("%s\n", two_d[i]);
}

static char     *find_home(t_env *env)
{
    int i;

    i = -1;
    while(env->env_copy[++i])
    {
        if (strncmp("HOME=", env->env_copy[i], 5) == 0)
            return(ft_strdup(env->env_copy[i] + 5));
    }
    return(0);
}

static char     *find_old_pwd(t_env *env)
{
    int i;

    i = -1;
    while(env->env_copy[++i])
    {
        if (strncmp("OLDPWD=", env->env_copy[i], 7) == 0)
            return(ft_strdup(env->env_copy[i] + 7));
    }
    return(0);
}

static void     check_cd_dir(char **input_copy, t_cmd *input_check)
{
    DIR *dir;
    struct stat sbuf;
    
    lstat(input_copy[1], &sbuf);
    if (!(dir = opendir(input_copy[1])))
    {
        if (S_ISREG(sbuf.st_mode))
            print_errors(input_copy[1], 2);
        else if (!S_ISREG(sbuf.st_mode))
            print_errors(input_copy[1], 1);
    }
    else
        chdir(input_copy[1]);
}

static void     ft_cd(char **input_copy, t_cmd *input_check, t_env *env) // need to testy test
{
    char *temp;

    temp = ft_memalloc(sizeof(char*));
    if(!input_copy[1] || ft_strcmp(input_copy[1], "--") == 0) //split into 2 maybe
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
    else if(input_copy[1] && !input_copy[2])
        check_cd_dir(input_copy, input_check);
    else if(input_copy[2] && !input_copy[3])
        print_errors(input_copy[1], 4);
    else if(input_copy[3] && !input_copy[4])
        print_errors(input_copy[1], 3);
    else
        print_errors(input_copy[1], 3);

}

static void     check_cd_cmd(char **input_copy, t_cmd *input_check, t_env *env)
{
    //if (input_check->cd == 1) // && !input_check->printed_errors) // need to have env vars update
    if(strcmp(input_copy[0], "cd") == 0)
        ft_cd(input_copy,input_check, env);
}

static void     check_env_cmd(char **input_copy, t_cmd *input_check, t_env *env)
{
    if(strcmp(input_copy[0], "env") == 0)
        ft_print_2d(env->env_copy);
}

static void     check_bultin(char **input_copy, t_cmd *input_check, t_env *env)
{
    check_cd_cmd(input_copy, input_check, env);
    check_env_cmd(input_copy, input_check, env);
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
        if(input_check->expansions >= 1 || input_check->tilde >= 1)
        {
            handle_exp_tilde(input_copy[i], input_check, env); // add a check for struct 1d after expansion handle
            input_copy[i] = ft_strdup(env->output);
            free(env->output);
        }
        //check_bultin(input_copy, input_check, env);
    }
    check_bultin(input_copy, input_check, env);
    //printf("%s <-- output\n", env->output);
    //ft_free_2d(input_copy);
}

// void    check_sys_cmd(char *input_copy, t_cmd *input_check, t_env *env)
// {
//     char *path;
//     //struct stat buf;

//     //path = ft_memalloc(sizeof(char*));    //path = ft_memalloc(sizeof(char**))
//     //path = get_path(path, env);
//     //path = ft_strsplit(path , ':');
//     // ft_print_2d(input_copy);
//     //if(path)
//         //ft_which_cmd(path, env); // throw a check to see if path exists
//     //ft_print_path(path);
//     //ft_print_2d(env->env_copy);
    
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
    int i;

    i = 0;
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