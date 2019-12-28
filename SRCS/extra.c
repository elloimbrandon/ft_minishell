 
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
*/