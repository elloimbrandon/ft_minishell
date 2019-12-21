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
    char            **env_copy;

}					t_env;

/*
** Functions
*/

void		init_struct(t_env *env);
void		copy_env(t_env *env);
#endif
