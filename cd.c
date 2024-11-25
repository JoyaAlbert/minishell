#include "minishell.h"

void show_env(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i] != NULL)
		printf("%s\n", envp[i]);
}
char *lookinenv(char **envp, char *lookfor)
{
	int	i;

	i = 0;
	while (envp[i] != 0)
	{
		if (ft_strnstr(envp[i], lookfor, ft_strlen(lookfor)) != NULL)
			return (ft_strnstr(envp[i], lookfor, ft_strlen(lookfor)) + ft_strlen(lookfor));
		i++;
	}
	return (NULL);
}

t_dir_info *my_pwd(char **envp)
{
	t_dir_info *aux;
	
	aux = malloc(sizeof(t_dir_info));
	if (aux == NULL)
		return (NULL);
	aux->dir = lookinenv(envp, "PWD=");
	aux->prev_dir = lookinenv(envp, "OLDPWD=");
	return (aux);
}

void my_cd(char **cmds, char **envp, t_dir_info *dir)
{
	char *home;
	t_dir_info *dir_info;

	if (cmds[1] == NULL
		|| (ft_strncmp(cmds[1], "~", 1) == 0 && ft_strlen(cmds[1]) == 1))
		{
			home = lookinenv(envp, "HOME=");
			if (home == NULL)
				printf("HOME variable not set");
			chdir(home);
		}
	else if (ft_strncmp(cmds[1], "-", 1) == 0)
		chdir(dir->prev_dir);
	else
		chdir(cmds[1]);
	dir_info = my_pwd(envp);
	dir = dir_info;
	free(dir_info);
}
