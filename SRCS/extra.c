 
 /*
 void    **find_path(t_env *env) 
    int i;

    i= 0;
    while(env->env_copy[i])
    {
        if(ft_strcmp(env->cmd_copy, "PATH") == 0)
            return (ft_strsplit(env->env_copy, ':'));
        i++;
    }
    return(ft_strsplit("", ';'));
}

int     check_exit(t_env *env)
{
    if (ft_strcmp(env->input, "exit") == 0)
    {
        free(env->input);
        free(env);
        return(1);
    }
    else
        return(0);
}

void    search_input(char *input_copy, t_cmd *input_check)
{
    int i;

    i = -1;
    while(input_copy[++i])
    {
        if(ft_strrchr(input_copy[i], '$') && !(ft_strrchr(input_copy[i + 1], '$'))) // could do the same for qoutes
        {
            input_check->expansions += 1; // minus one away after execution
            printf("its regestering a struct hit for $\n");
        }
        else if(ft_strchr(input_copy[i], '~') && !(ft_strrchr(input_copy[i + 1], '~')))
            input_check->tilde += 1;  // minus one away after execution
    }    
}
*/