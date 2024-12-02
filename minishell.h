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

# define PROMPT  "\033[31mサ »\033[0m " //➤ 

//on a typical Linux system, the PATH_MAX limit is usually set to 4096 characters
//on windows 256

typedef struct dir_info
{
	char	dir[4096];
	char	*prev_dir;
}	t_dir_info;

typedef struct env
{
	char	**env_dup;
}	t_envp;

// CD //
void		my_cd(char **cmds, char **envp, t_dir_info *dir);

// PIPES //
void	pipeline(char *cmd, char **envp);

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
int			prompt(t_envp *envp_d);

// SIGNALS //
void		signal_handler(void);

// DIRS AND ENV //
void		show_env(char **envp);
t_dir_info	*my_pwd(char **envp);
char		*lookinenv(char **envp, char *lookfor);
void		update_env(char **envp, t_dir_info *dir);

#endif