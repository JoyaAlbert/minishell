#include "minishell.h"

void	update_cmd(char **cmds)
{
	int	i;
	int	len;

	i = 0;
	while (cmds[i] != NULL)
	{
		len = ft_strlen(cmds[i]);
		if (len > 0 && cmds[i][len - 1] == '|')
			cmds[i][len - 1] = '\0';
		i++;
	}
}

int	pipe_process(char **cmds, char **envp, t_dir_info *dir, int prev_fd)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	fork_fail(cmds, pid);
	if (pid == 0)
	{
		dup2(prev_fd, 0);
		dup2(fd[1], 1);
		close(fd[0]);
		to_execpipe(*cmds, envp, dir);
	}
	else
	{
		close(fd[1]);
		if (prev_fd != 0)
			close(prev_fd);
		prev_fd = fd[0];
	}
	return (prev_fd);
}

void	pipeaux(char **cmds, char **envp, t_dir_info *dir)
{
	pid_t	pid;
	int		i;
	int		prev_fd;

	prev_fd = 0;
	i = -1;
	while (cmds[++i + 1] != NULL)
		prev_fd = pipe_process(&cmds[i], envp, dir, prev_fd);
	pid = fork();
	fork_fail(cmds, pid);
	if (pid == 0)
	{
		dup2(prev_fd, 0);
		to_execpipe(cmds[i], envp, dir);
		exit(EXIT_FAILURE);
	}
	else
		close(prev_fd);
	while (wait(NULL) > 0)
		;
}

void	pipeline(char *cmd, char **envp, t_dir_info *dir)
{
	char	**cmds;

	cmds = ft_split(cmd, '|');
	update_cmd(cmds);
	pipeaux(cmds, envp, dir);
	matrixfree(cmds);
}
