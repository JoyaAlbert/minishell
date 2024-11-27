#include "minishell.h"

void	show_env(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i] != NULL)
		printf("%s\n", envp[i]);
}

char	*lookinenv(char **envp, char *lookfor)
{
	int	i;

	i = 0;
	while (envp[i] != 0)
	{
		if (ft_strnstr(envp[i], lookfor, ft_strlen(lookfor)) != NULL)
			return (ft_strnstr(envp[i], lookfor, ft_strlen(lookfor))
				+ ft_strlen(lookfor));
		i++;
	}
	return (NULL);
}

t_dir_info	*my_pwd(char **envp)
{
	char cwd[4026];
	t_dir_info	*aux;
	
	(void)envp;
	aux = malloc(sizeof(t_dir_info));
	if (aux == NULL)
		return (NULL);
	aux->prev_dir = aux->dir;
	getcwd(aux->dir, sizeof(cwd));
	return (aux);
}

void	my_cd(char **cmds, char **envp, t_dir_info *dir)
{
	char		*home;
	t_dir_info	*dir_info;
	int			check;

	check = 1;
	if (cmds[1] == NULL
		|| (ft_strncmp(cmds[1], "~", 1) == 0 && ft_strlen(cmds[1]) == 1))
	{
		home = lookinenv(envp, "HOME=");
		if (home == NULL)
			printf("HOME variable not set");
		check = chdir(home);
	}
	else
		check = chdir(cmds[1]);
	dir_info = my_pwd(envp);
	if (check == 0)
		printf("%s\n", dir_info->dir);
	else if (check < 0)
		printf("cd: %s: not a path or directory\n", cmds[1]);
	dir = dir_info;
	(void)dir;
	free(dir_info);
}
