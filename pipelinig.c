#include "minishell.h"

void	builtin_pipes(char *cmd, char **args, char **envp, t_dir_info *dir)
{
	if (check_builtins(cmd) == 0)
	{
		sendto_builtin(args, dir, envp);
		matrixfree(args);
		exit(0);
	}
}
void to_execpipe(char *cmd, char **envp, t_dir_info *dir) 
{
    char **args;
	char *path;
	
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

void update_cmd(char **cmds)
{
	int i;
	int len;

	i = 0;
    while (cmds[i] != NULL) 
	{
        len = ft_strlen(cmds[i]);
        if (len > 0 && cmds[i][len - 1] == '|')
            cmds[i][len - 1] = '\0';
        i++;
    }
}

void	pipeaux(char **cmds, char **envp, t_dir_info *dir)
{
	pid_t pid;
	int	i;
	int pd[2];

	i = -1;
	while (cmds[++i + 1] != NULL)
	{
        pipe(pd);
		pid = fork();
		fork_fail(cmds, pid);
		if (pid == 0)
		{
			dup2(pd[1], 1);
			close(pd[0]);
			to_execpipe(cmds[i], envp, dir);
        } 
		else
		{
			close(pd[1]);
			dup2(pd[0], 0);
		}
		waitpid(0, NULL, 0);
    }
	to_execpipe(cmds[i], envp, dir);
	waitpid(pid, NULL, 0);
}

void pipeline(char *cmd, char **envp, t_dir_info *dir) 
{
    char **cmds;
	pid_t pid1;

    cmds = ft_split(cmd, '|');
    update_cmd(cmds);
	pid1 = fork();
	fork_fail(cmds, pid1);
    if (pid1 == 0) 
    {
    	pipeaux(cmds, envp, dir);
    	matrixfree(cmds);
	}
	else
		waitpid(pid1, NULL, 0);
	matrixfree(cmds);
}

