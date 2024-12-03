#include "minishell.h"

void	aux_mycd(char **cmds, t_dir_info *dir, t_dir_info *dir_info, int check)
{
	if (check < 0 && ft_strncmp(cmds[1], "-", 1) != 0)
	{
		printf("cd: %s: not a path or directory\n", cmds[1]);
		return ;
	}
	dir = dir_info;
	(void)dir;
	free(dir_info);
}

int	my_prevcd(char **cmds, char **envp, t_dir_info *dir)
{
	int			check;
	char		*env;

	(void)dir;
	check = 1;
	if (cmds[1] == NULL)
		return (check);
	if (ft_strncmp(cmds[1], "-", 1) == 0 && ft_strlen(cmds[1]) == 1)
	{
		env = lookinenv(envp, "OLDPWD=");
		if (env == NULL)
			printf("cd: OLDPWD not set\n");
		check = chdir(env);
	}
	return (check);
}

void	my_cd(char **cmds, char **envp, t_dir_info *dir)
{
	char		*home;
	t_dir_info	*dir_info;
	int			check;

	check = 1;
	check = my_prevcd(cmds, envp, dir);
	if (cmds[1] == NULL
		|| (ft_strncmp(cmds[1], "~", 1) == 0 && ft_strlen(cmds[1]) == 1))
	{
		home = lookinenv(envp, "HOME=");
		if (home == NULL)
			printf("HOME variable not set");
		check = chdir(home);
	}
	else if (cmds[1] != NULL && ft_strncmp(cmds[1], "-", 1) != 0)
		check = chdir(cmds[1]);
	if (check == 0)
	{
		update_env(envp, dir);
		dir_info = my_pwd(envp);
		printf("%s\n", dir_info->dir);
	}
	aux_mycd(cmds, dir, dir_info, check);
}
