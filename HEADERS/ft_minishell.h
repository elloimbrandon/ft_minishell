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

# define BLUE "\x1B[34m"

/*
** Structs
*/

typedef struct		s_env
{
    char            **env_copy; // copy of env varibles
    char            **cmd_copy; // copy of input from command line
    char            *input; // command line input
}					t_env;

typedef struct      s_cmd // think of multiple and path for cd ls commands 
{
    int             echo; // echo command
    int             exit; // exit command 
    int             cd; // change dir
    int             set_e; // set global env var
    int             unset_e; // unset global env var
    int             qoutes; // (has to equal 2) if theirs "  " for use of sentences for cat and echo
    int             nbr_of_cmds;
}                   t_cmd;

/*
** Functions
*/

void        sigint_handler(int sig_num);
int         display_prompt(void);
void		init_struct(t_env *env);
void		copy_env_var(t_env *env);
void        display_get_input(t_env *env);
void        init_input_check(t_cmd *input_check);
void        ft_parse_cmd(t_env *env);
int         check_exit(t_env *env);
//void        ft_parse_cmd(t_env *env);
#endif
