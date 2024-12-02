#include "minishell.h"

int	check_builtins(char *cmd)
{
	char	**cmds;
	int		i;

	i = -1;
	cmds = ft_split(cmd, ' ');
	while (cmds[++i] != NULL)
	{
		if ((!ft_strncmp(cmds[0], "cd", 2) && ft_strlen(cmds[0]) == 2)
			|| (!ft_strncmp(cmds[0], "pwd", 3) && ft_strlen(cmds[0]) == 3)
			|| (!ft_strncmp(cmds[0], "echo", 4) && ft_strlen(cmds[0]) == 4)
			|| (!ft_strncmp(cmds[0], "export", 6) && ft_strlen(cmds[0]) == 6)
			|| (!ft_strncmp(cmds[0], "unset", 5) && ft_strlen(cmds[0]) == 5)
			|| (!ft_strncmp(cmds[0], "env", 3) && ft_strlen(cmds[0]) == 3)
			|| (!ft_strncmp(cmds[0], "exit", 4) && ft_strlen(cmds[0]) == 4))
		{
			matrixfree(cmds);
			return (0);
		}
	}
	matrixfree(cmds);
	return (1);
}

int	check_redirect(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i] != '\0')
	{
		if (cmd[i] == '|' || cmd[i] == '<' || cmd[i] == '>')
			return (0);
	}
	return (1);
}

void	sendto_builtin(char **cmds, t_dir_info *dir, char **envp)
{
	(void)envp;

	if (!ft_strncmp(cmds[0], "pwd", 3) && ft_strlen(cmds[0]) == 3)
		printf("%s\n", dir->dir);
	if (!ft_strncmp(cmds[0], "env", 3) && ft_strlen(cmds[0]) == 3)
		show_env(envp);
	if (!ft_strncmp(cmds[0], "cd", 2) && ft_strlen(cmds[0]) == 2)
	{
		if (cmds[1] != NULL && cmds[2] != NULL)
		{
			printf("cd: too many arguments\n");
			return (void)(0);
		}
		my_cd(cmds, envp, dir);
	}
	if (!ft_strncmp(cmds[0], "unset", 5) && ft_strlen(cmds[0]) == 5)
	{}
}

void	parser(t_dir_info *dir, char **envp, char *cmd)
{
	char	**cmds;

	///SI CAMBIAMOS A USAR TODAS LAS VRIABLES CON UN DUP CAMBIAR BUILT INS QUE USEN ENV CON DIR_>ENV
	if (check_builtins(cmd) == 1 && check_redirect(cmd) == 1)
		to_exec(cmd, envp);
	cmds = ft_split(cmd, ' ');
	if (check_redirect(cmd) == 0)
		pipeline(cmd, envp);
	if (check_builtins(cmd) == 0)
		sendto_builtin(cmds, dir, envp);
	matrixfree(cmds);
}
