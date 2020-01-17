/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_b_checks2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 23:50:09 by brfeltz           #+#    #+#             */
/*   Updated: 2020/01/16 20:39:28 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_minishell.h"


void     check_cd_dir(char **input_copy, t_cmd *input_check)
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

void     ft_cd(char **input_copy, t_cmd *input_check, t_env *env)
{
    char *temp;

    temp = ft_memalloc(sizeof(char*) + 1);
    if(!input_copy[1] || ft_strcmp(input_copy[1], "--") == 0)
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

void   check_env(char *input_copy, t_cmd *input_check)
{
    int i;

    i = -1;
    while(input_copy[++i])
    {
        if(input_copy[i] == '$')
            input_check->expansions++;
    }
}

void   check_tilde(char *input_copy, t_cmd *input_check)
{
    int i;

    i = -1;
    while(input_copy[++i])
    {
        if(input_copy[i] == '~')
            input_check->tilde++;
    }
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
