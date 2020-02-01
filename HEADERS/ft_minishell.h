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

# define BUFF 2000

/*
** Structs
*/

typedef struct		s_env
{
    char            **env_copy;
    char            *input;
    char            *exp_hold;
    char            *tilde_hold;
}					t_env;

typedef struct      s_cmd 
{
    unsigned int    executed;
    unsigned int    qoutes;
    unsigned int    tilde;
    unsigned int    expansions;
    unsigned int    printed_errors;
}                   t_cmd;

/*
** Functions
*/


int     display_prompt(void);
int     get_input(t_env *env);
int		ft_size_2d(char **arr);
int     ft_count_words_2d(char **s);
int     ft_same_cmd(char *exec, char **input_copy);
int     find_set_var(char **input_copy, t_env *env);
int      find_unset_var(char **input_copy, t_env *env);
int     unset_env(char *temp, t_env *env, int k);
int     check_path_build_path(char **path, char **input_copy, t_env *env);
char    *get_path(t_env *env);
char    *build_path(char *input_copy, char *path);
char    *find_home(t_env *env);
char    *find_old_pwd(t_env *env);
char    *exp_tilde_check(char *input_copy, t_cmd *input_check, t_env *env);
char    **add_new_line(t_env *env, char **input_copy);
void    ft_hello(void);
void    sigint_handler(int sig_num);
void    sigquit_handler(int sig_num);
void    sigint_handler_2(int sig_num);
void    get_home_path(t_env *env);
void    init_structs(t_env *env, t_cmd *input_check);
void    add_env_var(char **input_copy, t_env *env);
void    check_env_tilde_qoutes(char *input_copy, t_cmd *input_check);
void    check_bultin(char **input_copy, t_cmd *input_check, t_env *env);
void    check_cd_cmd(char **input_copy, t_cmd *input_check, t_env *env);
void    check_env_cmd(char **input_copy, t_env *env);
void    check_pwd_cmd(char **input_copy, t_cmd *input_check);
void    check_echo_cmd(char **input_copy, t_cmd *input_check);
void    check_setenv(char **input_copy, t_env *env);
void    check_unsetenv(char **input_copy, t_env *env);
void    check_exit_cmd(char **input_copy);
void    check_system_cmd(char **input_copy, t_env *env);
void    check_cd_dir(char **input_copy, t_cmd *input_check);
void    check_env(char *input_copy, t_cmd *input_check);
void    check_qoutes(char *input_copy, t_cmd *input_check);
void    check_tilde(char *input_copy, t_cmd *input_check);
void    check_exec(char *hold, char **input_copy, t_env *env);
void    handle_tilde(char *input_copy, t_env *env);
void    handle_env(char *input_copy, t_env *env);
void    handle_qoutes(char **input_copy, t_cmd *input_check);
void    find_env_var(char *temp, t_env *env);
void    ft_minishell(t_env *env, t_cmd *input_check);
void    ft_parse_mini(t_env *env, t_cmd *input_check);
void    ft_parse_mini_2(t_env *env, t_cmd *input_check, char **input);
void    ft_parse_input(t_env *env, t_cmd *input_check, char **input_copy);
void    ft_remove_qoutes(char *input_copy);
void    ft_print_echo(char **input_copy, t_cmd *input_check);
void    ft_local_exec(char **input_copy, t_cmd *input_check, t_env *env);
void    ft_already_exc(t_cmd *input_check, char **input_copy);
void    ft_print_2d(char **two_d);
void    ft_fork(char *exec, char **input_copy, t_env *env);
void    ft_cd(char **input_copy, t_cmd *input_check, t_env *env);
void    print_path(void);
void    print_errors(char *input_copy, t_cmd *input_check, int i);

#endif
