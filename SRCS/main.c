/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:16:50 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/09 13:04:20 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"
#include <stdio.h> /////////////////// REMOVE

///////////////////use csh

// static char    *get_path(char *temp, t_env *env)
// {
//     int i;

//     i = -1;
//     while(env->env_copy[++i])
//     {
//         if (strncmp("PATH=", env->env_copy[i], 5) == 0)
//         temp = ft_strdup(env->env_copy[i] + 5);
//         temp = ft_strdup(temp);
//     }
//     return(temp);
// }

static void    print_errors(char *input_copy, t_cmd *input_check, int i)
{
    if (i == 1)
        ft_printf("cd: no such file or directory: %s\n", input_copy);
    else if (i == 2)
        ft_printf("cd: not a directory: %s\n", input_copy);
    else if (i == 3)
        ft_printf("cd: too many arguments\n");
    else if (i == 4)
        ft_printf("cd: string not in pwd: %s\n", input_copy);
    input_check->printed_errors++;
    
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
            print_errors(input_copy[1], input_check, 2);
        else if (!S_ISREG(sbuf.st_mode))
            print_errors(input_copy[1], input_check, 1);
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
        print_errors(input_copy[1], input_check, 4);
    else if(input_copy[3] && !input_copy[4])
        print_errors(input_copy[1], input_check, 3);
    else
        print_errors(input_copy[1], input_check, 3);
}

void    print_path(t_env *env)
{
    char display[BUFF + 1];
    
    getcwd(display, BUFF);
    ft_printf("%s\n", display);
}

static void     check_cd_cmd(char **input_copy, t_cmd *input_check, t_env *env)
{
    if(ft_strcmp(input_copy[0], "cd") == 0)
        ft_cd(input_copy,input_check, env);
}

static void     check_exit_cmd(char **input_copy, t_cmd *input_check, t_env *env)
{
    if(ft_strcmp(input_copy[0], "exit") == 0)
    {
        ft_printf("%sGoodbye!\n", KMAG);
        exit(1);
    }
}

static void     check_env_cmd(char **input_copy, t_cmd *input_check, t_env *env)
{
    if(!input_copy[1] && ft_strcmp(input_copy[0], "env") == 0)
        ft_print_2d(env->env_copy);
    else if (input_copy[1] && ft_strcmp(input_copy[0], "env") == 0)
        ft_printf("env: %s: No such file or directory\n", input_copy[1]);
}

static void     check_pwd_cmd(char **input_copy, t_cmd *input_check, t_env *env)
{
    if(!input_copy[1] && ft_strcmp(input_copy[0], "pwd") == 0)
        print_path(env);
    else if(!input_check->printed_errors && ft_strcmp(input_copy[0], "pwd") == 0)
        ft_printf("pwd: too many arguments\n");
}

static void     ft_remove_qoutes(char *input_copy, t_cmd *input_check)
{
    int k;

    k = 0;
    while(input_copy[k])
    {
        if(input_copy[k] != '"')
            ft_printf("%c", input_copy[k]);
        // if (input_copy[k - 1] != ' ' && input_copy[k + 1] != ' ' // dont fkin need
        //     && input_copy[k] == '"' && input_copy[k - 1] != 0)
        //     ft_printf(" ");
        k++;
    }
}
static void     ft_print_echo(char **input_copy, t_cmd *input_check)
{
    int i;

    i = 0;
    while(input_copy[++i])
    {
        if(input_check->qoutes)
            ft_remove_qoutes(input_copy[i], input_check);
        if (!input_check->qoutes)
            ft_printf("%s", input_copy[i]);
        if (input_copy[i + 1])
            ft_printf(" ");
    }
    printf("\n");
}

static void     handle_qoutes(char **input_copy, t_cmd *input_check)
{
    if(input_check->qoutes % 2 == 0)
        ft_print_echo(input_copy, input_check);
    else
        ft_printf("echo: Unmatched \" \" \n");
}

static void     check_qoutes(char *input_copy, t_cmd *input_check)
{
    int i;
    int qoute_count;

    i = -1;
    qoute_count = 0; 
    while(input_copy[++i])
    {
        if(input_copy[i] == '"')
            input_check->qoutes++;
    }
}

static void     check_echo_cmd(char **input_copy, t_cmd *input_check, t_env *env)
{
    if(!input_copy[1] && ft_strcmp(input_copy[0], "echo") == 0)
        printf("\n");
    else if(input_check->qoutes && ft_strcmp(input_copy[0], "echo") == 0)
    {
        if(input_check->qoutes % 2 == 0)
            ft_print_echo(input_copy, input_check);
        else
            ft_printf("echo: Unmatched \" \" \n");
        input_check->qoutes = 0;
    }
    else if(input_copy[1] && ft_strcmp(input_copy[0], "echo") == 0)
        ft_print_echo(input_copy, input_check);
}

static void     check_bultin(char **input_copy, t_cmd *input_check, t_env *env)
{
    input_check->printed_errors = 0; // moved inside function
    check_cd_cmd(input_copy, input_check, env);
    check_env_cmd(input_copy, input_check, env);
    check_pwd_cmd(input_copy, input_check, env);
    check_exit_cmd(input_copy, input_check, env);
    check_echo_cmd(input_copy, input_check, env);
}

void    ft_parse_cmd(t_env *env, t_cmd *input_check)
{
    char **input_copy;
    int i;

    i = -1;
    input_copy = ft_strsplit(env->input, ';');
    free(env->input);
    input_copy = split_by_space(input_copy);
    while(input_copy[++i])
    {
        search_input(input_copy[i], input_check);
        check_qoutes(input_copy[i], input_check);
        if(input_check->expansions >= 1 || input_check->tilde >= 1)
        {
            handle_exp_tilde(input_copy[i], input_check, env);
            input_copy[i] = ft_strdup(env->output);
            ft_printf("bash: command not found: %s\n", input_copy[i]); /// experiment // cant use with other commands
            free(env->output); // rename output
        }
    }
    check_bultin(input_copy, input_check, env);
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