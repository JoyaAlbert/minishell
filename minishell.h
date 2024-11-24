#ifndef MINISHELL_H
# define MINISHELL_H


# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>


# include "utils/utils.h"

# define PROMPT  "\033[3;36mShell<3\033[0m "


// SHOW ERROR ON SCREEN//
void    msg(char *str);


// PATHS //
char	*getpatharray(char **envp);
char	*getpath(char *args, char *envp[]);
void	matrixfree(char	**matrix);

// EXECUTION //
void    to_exec(char *cmd, char **envp);
// PROMPT //
int prompt(char **envp);
#endif