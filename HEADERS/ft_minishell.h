#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H
# include "../libft/libft.h"
# include <dirent.h>
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

# define KRED "\x1B[31m"
# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"

# define BUFF 2048

char    **global_env;
/*
** Structs
*/

typedef struct		s_env
{
    char            **env_copy; // copy of env varibles
    char            **cmd_copy; // copy of input from command line
    char            *input; // command line input
    char            *output;
    char            *exp_hold; // holds env expansion str
    char            *tilde_hold; // hold home path
}					t_env;

typedef struct      s_cmd // think of multiple and path for cd ls commands 
{
    int             echo; // echo command
    int             exit; // exit command 
    int             cd; // change dir
    int             env; // show all env variables
    int             pwd; // get current path
    unsigned int    add_env;
    unsigned int    set_e; // set global env var
    unsigned int    unset_e; // unset global env var
    unsigned int    qoutes; // counts qoutes used for echo
    unsigned int    tilde; // for use of home dir
    unsigned int    expansions; // number of found $ for expansions
    unsigned int    printed_errors; // counts number of errors that have been printed
}                   t_cmd;

/*
** Functions
*/

void            sigint_handler(int sig_num);
void            sigquit_handler(int sig_num);
static char		*get_input(void);
void            ft_hello(void);
int             ft_size2d(char **arr);
int             display_prompt(void);
void		    init_structs(t_env *env, t_cmd *input_check);
void            display_get_input(t_env *env, t_cmd *input_check);
void            init_input_check(t_cmd *input_check);
void            ft_parse_cmd(t_env *env, t_cmd *input_check);
void            search_input(char *input_copy, t_cmd *input_check);
char            **split_by_space(char **input_copy);
void            handle_exp_tilde(char *input_copy, t_cmd *input_check, t_env *env);
void            handle_env(char *input_copy, t_cmd *input_check, t_env *env);
void            find_env_var(char *temp, t_cmd *input_check, t_env *env);
char            *build_path(char *input_copy, char *path);

// testing these functions
void        ft_which_cmd(char **path, t_env *env);
char        *find_path(char *path, t_env *env);
void        check_sys_cmd(char *input_copy, t_cmd *input_check, t_env *env);
void        check_commands(char *input_copy, t_cmd *input_check, t_env *env);
void        get_home_path(char *temp, t_env *env);
void        handle_tilde(char *input_copy, t_cmd *input_check, t_env *env);
//int         exec_fork(t_env *env);

#endif
