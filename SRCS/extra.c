 
 /*

 void    find_env_var(char *temp, t_env *env) <----- OLD
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(temp);
    while(env->env_copy[i])
    {
        if(ft_strccmp(temp, env->env_copy[i], '=') == 0)
        {
            printf("%s <-- old env name\n", env->env_copy[i]); // prints old env value!!
            //len += ft_strlen(env->env_copy[i]);
            //env->output = ft_memalloc(sizeof(char *) + len);
            env->output = ft_memalloc(sizeof(char *));
            env->output = ft_strcpy(env->output, temp);
            ft_strdel(&env->env_copy[i]);
            env->env_copy[i] = ft_strdup(env->output);
            //ft_strcat(env->output, env->env_copy[i]); // also handle if the strings are the same then dont replace
        }
        i++;
    }
}

void    ft_which_cmd(char **path, t_env *env)
{
    int i;
    char *temp;

    i = 0;
    temp = ft_memalloc(sizeof(char *));
    while(path[i])
    {
        if(ft_strcmp(path[i], env->input) == 0)
            env->output = ft_strdup(path[i]);
        i++;
    }
}

void    check_commands(char *input_copy, t_cmd *input_check, t_env *env)
{

    // maybe check and see if tilde and expansions are 0?

    if (!input_check->expansions && !input_check->tilde) // i might have to figure out what to do with the output string with other cmmds id their is exp-tilde
    {
        printf("its a system command\n");
        check_sys_cmd(input_copy, input_check, env);
    }
}

char    *find_path(char *path, t_env *env)
{
    int i;

    i = 0;
    while(env->env_copy[i])
    {
        if(ft_strcmp(env->env_copy[i], "PATH") == 0)
        {
            printf("%s <-- found path\n", env->env_copy[i]);
            return (ft_strsplit(env->env_copy[i], ':'));
        }
        i++;
    }
    printf("didnt find path\n");
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

int exec_fork(t_env *env)
{
    pid_t child;

    child = fork();
    if (child == 0)
    {
        ft_printf("found command\n");
        //execve();
    }
    else if (child < 0)
    {
        ft_printf("could not create process\n");
        printf("%s\n <-- contents of env->input", env->input);
        return (1);
    }
    wait(&child);
    return (0);
}

// while(!display_prompt() && get_next_line(STDIN_FILENO, &(temp))) <------ for read loop alternative
*/