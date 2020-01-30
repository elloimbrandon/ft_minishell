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
#include <stdio.h> /////////////////// j ghjjvguvgfguyvfgug
/*
** Structs
*/

typedef struct		s_env
{
    char            **env_copy; // copy of env varibles
    char            *input; // command line input
    char            *output; // might not need
    char            *exp_hold; // holds env expansion str
    char            *tilde_hold; // hold home path
}					t_env;

typedef struct      s_cmd // think of multiple and path for cd ls commands 
{
    unsigned int    executed;
    unsigned int    qoutes; // counts qoutes used for echo
    unsigned int    tilde; // for use of home dir
    unsigned int    expansions; // number of found $ for expansions
    unsigned int    printed_errors; // counts number of errors that have been printed
}                   t_cmd;

/*
** Functions
*/


int     display_prompt(void);
int		ft_size_2d(char **arr);
int     ft_count_words_2d(char **s);
int    ft_same_cmd(char *exec, char **input_copy);
// char		*get_input(void);
char    **split_by_space(char **input_copy);
char    *get_path(char *hold, t_env *env);
char    *build_path(char *input_copy, char *path);
char     *find_home(t_env *env);
char     *find_old_pwd(t_env *env);
char    *exp_tilde_check(char *input_copy, t_cmd *input_check, t_env *env);
void    ft_hello(void);
void    sigint_handler(int sig_num);
void    sigquit_handler(int sig_num);
void    check_bultin(char **input_copy, t_cmd *input_check, t_env *env);
void    check_cd_cmd(char **input_copy, t_cmd *input_check, t_env *env);
void    check_env_cmd(char **input_copy, t_cmd *input_check, t_env *env);
void    check_pwd_cmd(char **input_copy, t_cmd *input_check, t_env *env);
void    check_echo_cmd(char **input_copy, t_cmd *input_check, t_env *env);
void    check_exit_cmd(char **input_copy, t_cmd *input_check, t_env *env);
void    check_system_cmd(char **input_copy, t_cmd *input_check, t_env *env);
void    check_cd_dir(char **input_copy, t_cmd *input_check);
void    check_env(char *input_copy, t_cmd *input_check);
void    check_qoutes(char *input_copy, t_cmd *input_check);
void    check_tilde(char *input_copy, t_cmd *input_check);
void    check_exec(char *hold, char **input_copy, t_env *env);
void    handle_tilde(char *input_copy, t_cmd *input_check, t_env *env);
void    handle_env(char *input_copy, t_cmd *input_check, t_env *env);
void    handle_qoutes(char **input_copy, t_cmd *input_check);
void    find_env_var(char *temp, t_cmd *input_check, t_env *env);
void    ft_parse_mini(t_env *env, t_cmd *input_check);
void    ft_parse_input(t_env *env, t_cmd *input_check, char **input_copy);
void    ft_remove_qoutes(char *input_copy, t_cmd *input_check);
void    ft_print_echo(char **input_copy, t_cmd *input_check);
void    ft_local_exec(char **input_copy, t_cmd *input_check, t_env *env);
void    ft_already_exc(t_cmd *input_check, char **input_copy);
//void    ft_zero_out(t_cmd *input_check);
void    ft_print_2d(char **two_d);
void    ft_fork(char *exec, char **input_copy, t_env *env);
void    ft_cd(char **input_copy, t_cmd *input_check, t_env *env);
void    print_path(t_env *env);
void    print_errors(char *input_copy, t_cmd *input_check, int i);
void    get_home_path(char *temp, t_env *env);
//void    add_env_var(char *temp, t_cmd *input_check, t_env *env);
void    init_structs(t_env *env, t_cmd *input_check);


void    check_setenv(char **input_copy, t_cmd *input_check, t_env *env);
void    check_unsetenv(char **input_copy, t_cmd *input_check, t_env *env);

#endif
