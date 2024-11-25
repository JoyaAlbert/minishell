#include "minishell.h"

int prompt(char **envp)
{
    char    *cmd;
 	t_dir_info *dir_info;
	
	signal_handler();
	dir_info = my_pwd(envp);
	cmd = readline(PROMPT);
	if (cmd == NULL)
		return (1);
	if (ft_strlen(cmd) == 0)
	{	
		free(dir_info);
		free(cmd);
		return (0);
	}
	add_history(cmd);
	parser(dir_info, envp, cmd);
	free(cmd);
	free(dir_info);
    return (0);
}
