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
# include <signal.h>
# include "utils/utils.h"

# define PROMPT  "\033[3;36mShell<3\033[0m "

typedef struct dir_info
{
	char	**env_dup;
	char	*dir;
	char	*prev_dir;
}	t_dir_info;

// BUILT IN //
void		show_env(char **envp);
void		my_cd(char **cmds, char **envp, t_dir_info *dir);

// SHOW ERROR ON SCREEN//
void		msg(char *str);

//	PARSER   //
void		parser(t_dir_info *dir, char **envp, char *cmd);

// PATHS //
char		*getpatharray(char **envp);
char		*getpath(char *args, char *envp[]);
void		matrixfree(char	**matrix);

// EXECUTION //
void		to_exec(char *cmd, char **envp);

// PROMPT //
int			prompt(char **envp);

// SIGNALS //
void		signal_handler(void);

// DIRS AND ENV //
t_dir_info	*my_pwd(char **envp);
char		*lookinenv(char **envp, char *lookfor);

#endif