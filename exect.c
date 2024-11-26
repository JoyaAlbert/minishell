#include "minishell.h"

void	execution(char *path, char **cmds, char **envp)
{
	int	check;

	if (path == NULL)
	{
		free(path);
		matrixfree(cmds);
		msg("ERROR: no path found");
	}
	check = execve(path, cmds, envp);
	if (check == -1)
	{
		free(path);
		matrixfree(cmds);
		msg("ERROR while executing");
	}
}

void	to_exec(char *cmd, char **envp)
{
	char	*path;
	char	**cmds;
	pid_t	pid;

	cmds = ft_split(cmd, ' ');
	pid = fork();
	if (pid == -1)
	{
		matrixfree(cmds);
		msg("fork failed");
	}
	if (pid == 0)
	{
		if (cmds[0][0] != '/' && cmds[0][0] != '.')
		{
			path = getpath(cmds[0], envp);
			execution(path, cmds, envp);
			free(path);
		}
		else
			execution(cmds[0], cmds, envp);
	}
	else
		waitpid(0, NULL, 0);

	matrixfree(cmds);
}
