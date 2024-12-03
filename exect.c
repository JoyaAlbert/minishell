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
	path = ft_strndup(cmds[0], ft_strlen(cmds[0]) + 1);
	if (pid == -1)
	{
		matrixfree(cmds);
		msg("fork failed");
	}
	if (pid == 0)
	{
		if (cmds[0][0] != '/' && cmds[0][0] != '.')
		{
			free(path);
			path = getpath(cmds[0], envp);
			execution(path, cmds, envp);
			free(path);
		}
		else
			execution(path, cmds, envp);
	}
	else
		waitpid(pid, NULL, 0);
	free(path);
	matrixfree(cmds);
}

void	builtin_pipes(char *cmd, char **args, char **envp, t_dir_info *dir)
{
	if (check_builtins(cmd) == 0)
	{
		sendto_builtin(args, dir, envp);
		matrixfree(args);
		exit(0);
	}
}

void	to_execpipe(char *cmd, char **envp, t_dir_info *dir)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	builtin_pipes(cmd, args, envp, dir);
	if (cmd[0] != '/' && cmd[0] != '.')
		path = getpath(args[0], envp);
	else
		path = ft_strndup(args[0], ft_strlen(args[0]) + 1);
	if (path == NULL)
	{
		free(path);
		matrixfree(args);
		msg("No path found\n");
	}
	if (execve(path, args, envp) == -1)
	{
		free(path);
		matrixfree(args);
		msg("ERROR executing\n");
	}
}
