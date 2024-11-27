#include "minishell.h"

int	exit_built(char *cmd, t_dir_info *dir_info)
{
	if (ft_strnstr(cmd, "exit", ft_strlen(cmd) + 1) != NULL)
	{
		free(cmd);
		free(dir_info);
		return (1);
	}
	free(cmd);
	free(dir_info);
	return (0);
}
int	prompt(char **envp)
{
	char		*cmd;
	t_dir_info	*dir_info;

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
	return (exit_built(cmd, dir_info));
}
