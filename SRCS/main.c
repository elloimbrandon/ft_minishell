/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandonf <brfeltz@student.42.us.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:16:50 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/11 05:24:58 by brandonf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"
#include <stdio.h> /////////////////// REMOVE
/////////////////// REMOVE EVERY PRINTF!!!
///////////////////use csh

static void    print_errors(char *input_copy, t_cmd *input_check, int i)
{
    if (i == 1)
        ft_printf("%scd: no such file or directory: %s\n", KRED, input_copy);
    else if (i == 2)
        ft_printf("%scd: not a directory: %s\n", KRED, input_copy);
    else if (i == 3)
        ft_printf("%scd: too many arguments\n", KRED);
    else if (i == 4)
        ft_printf("%scd: string not in pwd: %s\n", KRED, input_copy);
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
        ft_printf("%senv: %s: No such file or directory\n", KRED, input_copy[1]);
}

static void     check_pwd_cmd(char **input_copy, t_cmd *input_check, t_env *env)
{
    if(!input_copy[1] && ft_strcmp(input_copy[0], "pwd") == 0)
        print_path(env);
    else if(!input_check->printed_errors && ft_strcmp(input_copy[0], "pwd") == 0)
        ft_printf("%spwd: too many arguments\n", KRED);
}

static void     ft_remove_qoutes(char *input_copy, t_cmd *input_check)
{
    int k;

    k = -1;
    while(input_copy[++k])
    {
        if(input_copy[k] != '"')
            ft_printf("%c", input_copy[k]);
        // if (input_copy[k - 1] != ' ' && input_copy[k + 1] != ' ' // dont fkin need
        //     && input_copy[k] == '"' && input_copy[k - 1] != 0)
        //     ft_printf(" ");
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
        ft_printf("%secho: Unmatched \" \" \n", KRED);
}

static void     check_qoutes(char *input_copy, t_cmd *input_check)
{
    int i;

    i = -1;
    while(input_copy[++i])
    {
        if(input_copy[i] == '"')
            input_check->qoutes++;
    }
}

static void   check_env(char *input_copy, t_cmd *input_check)
{
    int i;

    i = -1;
    while(input_copy[++i])
    {
        if(input_copy[i] == '$')
            input_check->expansions++;
    }
}

static void   check_tilde(char *input_copy, t_cmd *input_check)
{
    int i;

    i = -1;
    while(input_copy[++i])
    {
        if(input_copy[i] == '~')
            input_check->tilde++;
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
            ft_printf("%secho: Unmatched \" \" \n", KRED);
        input_check->qoutes = 0;
    }
    else if(input_copy[1] && ft_strcmp(input_copy[0], "echo") == 0)
        ft_print_echo(input_copy, input_check);
}


static void     check_bultin(char **input_copy, t_cmd *input_check, t_env *env)
{
    check_cd_cmd(input_copy, input_check, env);
    check_env_cmd(input_copy, input_check, env);
    check_pwd_cmd(input_copy, input_check, env);
    check_exit_cmd(input_copy, input_check, env);
    check_echo_cmd(input_copy, input_check, env);
}

char    *exp_tilde_check(char *input_copy, t_cmd *input_check, t_env *env)
{
    char *ret;

    ret = NULL;
    if(input_check->expansions == 1 && input_copy[1])
    {
        handle_env(input_copy, input_check, env);
        if(env->exp_hold)
        {
            ret = ft_strdup(env->exp_hold);
            if(!input_check->set_e || !input_check->unset_e || !input_check->add_env)
                ft_printf("bash: command not found: %s\n", ret); //figure out a way for it not to throw 2 errors using other commands
            free(env->exp_hold);
            return(ret);
        }
    }
    if(input_check->tilde == 1)
    {
        handle_tilde(input_copy, input_check, env);
        if(env->tilde_hold)
        {
            ret = ft_strdup(env->tilde_hold);
            free(env->tilde_hold);
            return(ret);
        }
    }
    return(input_copy);
}

static void   check_set_unset_env(char *input_copy, t_cmd *input_check)
{
    if (ft_strcmp(input_copy, "setenv") == 0)
        input_check->set_e++;
    else if (ft_strcmp(input_copy, "unsetenv") == 0)
        input_check->unset_e++;
    else if (ft_strcmp(input_copy, "addenv") == 0)
        input_check->add_env++;
}

static char    *get_path(char *hold, t_env *env)
{
    int i;
    char *temp;

    i = -1;
    while(env->env_copy[++i])
    {
        if (strncmp("PATH=", env->env_copy[i], 5) == 0)
        temp = ft_strdup(env->env_copy[i] + 5);
    }
    return(temp);
}

char    *build_path(char *input_copy, char *path)
{
    path = ft_strcat(path, "/");
    return(ft_strjoin(path, input_copy));
}

void    ft_fork(char *exec, char **input_copy)
{
    pid_t child_p;

    child_p = fork();
    if(child_p == 0)
    {
        printf("%s<----exec\n", exec);
        execve(exec, input_copy, global_env);
    }
    else if (child_p < 0)
        ft_printf("could not create process\n");
    wait(&child_p);
}

static void    ft_same(char *exec, char **input_copy)
{
    int i;
    int len;
    char *temp;

    i = 0;
    temp = NULL;
    len = ft_strlen(exec);
    while(exec[len] != '/')
        len--;
    len++;
    temp = ft_strdup(exec + len);
    if(ft_strcmp(input_copy[0], temp) != 0)
        ft_printf("cd: command not found: %s\n", input_copy[0]);
    free(temp);
}

static void    exec_cmd(char *exec, struct stat buf, char **input_copy)
{
    //if(!(lstat(input_copy[0], &buf) != -1) && !exec) // try without -1
    //ft_same(exec, input_copy);
    if(!(lstat(input_copy[0], &buf)))
        ft_printf("cd: command not found: %s\n", input_copy[0]);
    if (exec)
    {
        lstat(input_copy[0], &buf);
        ft_fork(exec, input_copy);
    }
    else if (lstat(input_copy[0], &buf) != -1)
    {
        if(S_ISDIR(buf.st_mode))
            chdir(input_copy[0]);
        else if (S_ISREG(buf.st_mode))
            ft_fork(input_copy[0], input_copy);
    }
}

static void    verify_cmd(char *exec, char **input_copy)
{
    struct stat buf;

    // ft_same(exec, input_copy);
    if (lstat(exec, &buf) != -1)
        exec_cmd(exec, buf, input_copy);
    else
        free(exec);
}

static void    check_system_cmd(char **input_copy, t_cmd *input_check, t_env *env)
{
    char **path;
    char *hold;
    char *exec;
    int i;

    i = -1;
    exec = NULL;
    hold = get_path(hold, env);
    if(path)
    {
        path = ft_strsplit(hold , ':');
        while(path[++i])
        {
            if(ft_strcmp(input_copy[0], path[i]) == 0)
                exec = ft_strdup(input_copy[0]);
            else
                exec = build_path(input_copy[0],path[i]);
            verify_cmd(exec, input_copy);
            //free(exec); // added
        }
        ft_free_2d(path);
    }
    // else
    //     ft_printf("cd: command not found: %s\n", input_copy[0]);
}

static void    ft_zero_out(t_cmd *input_check)
{
    input_check->add_env = 0;
    input_check->set_e = 0;
    input_check->unset_e = 0;
    input_check->expansions = 0; // possibly move back into checker
    input_check->tilde = 0; // possibly move back into checker
    input_check->printed_errors = 0;
}

void    ft_already_exc(t_cmd *input_check, char **input_copy)
{
    if (ft_strcmp(input_copy[0], "echo") == 0)
        input_check->executed = 1;
    else if (ft_strcmp(input_copy[0], "cd") == 0)
        input_check->executed = 1;
    else if (ft_strcmp(input_copy[0], "env") == 0)
        input_check->executed = 1;
    else if (ft_strcmp(input_copy[0], "pwd") == 0)
        input_check->executed = 1;
    else if (ft_strcmp(input_copy[0], "exit") == 0)
        input_check->executed = 1;
    else if (ft_strcmp(input_copy[0], "setenv") == 0)
        input_check->executed = 1;
    else if (ft_strcmp(input_copy[0], "unsetenv") == 0)
        input_check->executed = 1;
    else if (ft_strcmp(input_copy[0], "addenv") == 0)
        input_check->executed = 1;
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
        check_env(input_copy[i], input_check);
        check_tilde(input_copy[i], input_check);
        check_qoutes(input_copy[i], input_check);
        check_set_unset_env(input_copy[i], input_check);
        if(input_check->expansions == 1)
            input_copy[i] = exp_tilde_check(input_copy[i], input_check, env);
        if(input_check->tilde == 1)
            input_copy[i] = exp_tilde_check(input_copy[i], input_check, env);
    }
    ft_zero_out(input_check);
    check_bultin(input_copy, input_check, env);
    ft_already_exc(input_check, input_copy);
    if(!input_check->executed)
        check_system_cmd(input_copy, input_check, env);
    input_check->executed = 0;
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
    int i;

    i = 0;
    while(!display_prompt())
    {
        env->input = get_input();
        if(env->input)
            ft_parse_cmd(env, input_check); /// seg faults on ctrl-d
        ft_strclr(env->input); // maybe free?
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