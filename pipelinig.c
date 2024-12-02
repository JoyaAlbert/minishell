#include "minishell.h"


void to_execpipe(char *cmd, char **envp) 
{
    char **args;
	char *path;
	
	args = ft_split(cmd, ' '); 
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

void	fork_fail(char **cmds, int pid)
{
	if (pid < 0)
	{
		matrixfree(cmds);
		msg("Fork Failed");
	}
}

void	pipeaux(char **cmds, char **envp)
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
			to_execpipe(cmds[i], envp);
        } 
		else
		{
			close(pd[1]);
			dup2(pd[0], 0);
		}
		waitpid(0, NULL, 0);
    }
	to_execpipe(cmds[i], envp);
	waitpid(pid, NULL, 0);
}

void pipeline(char *cmd, char **envp) 
{
    char **cmds;
	pid_t pid1;

    cmds = ft_split(cmd, '|');
    update_cmd(cmds);
	pid1 = fork();
	fork_fail(cmds, pid1);
    if (pid1 == 0) 
    {
    	pipeaux(cmds, envp);
    	matrixfree(cmds);
	}
	else
		waitpid(pid1, NULL, 0);
	matrixfree(cmds);
}

