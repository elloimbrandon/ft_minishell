#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H
# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <time.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <string.h>
# include <signal.h>

/*
** Macros
*/

/*
** Structs
*/

typedef struct		s_env
{
    char            **env_copy; // copy of env varibles
    char            **cmd_copy; // copy of input from command line
    char            *input;
}					t_env;

/*
** Functions
*/

void        sigint_handler(int sig_num);
int         display_prompt(void);
void		init_struct(t_env *env);
void		copy_env_var(t_env *env);
void        display_get_input(t_env *env);
//void        ft_store_cmd(t_env *env, int argc, char **argv);
#endif
