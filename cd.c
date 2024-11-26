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

/**
void	update_env(t_dir_info *dir, char **cmds)
{
    int i;
	char cwd[4026];
	char	*aux;

	(void)cmds;
    i = -1;
    while (dir->env_dup[++i] != NULL && ft_strnstr(dir->env_dup[i], "PWD", 3) == NULL)
        ;
    if (dir->env_dup[i] != NULL) 
	{
        getcwd(cwd, 0);
        aux = ft_strjoin("PWD=", cwd);
		dir->env_dup[i] = ft_strndup(aux, (ft_strlen(aux))+1);
    }
    i = -1;
    while (dir->env_dup[++i] != NULL && ft_strnstr(dir->env_dup[i], "OLDPWD", 6) == NULL)
        ;
    if (dir->env_dup[i] != NULL) 
    {
        if (dir->dir != NULL) 
            aux = ft_strjoin("OLDPWD=", dir->dir); 
        else
            aux = ft_strndup("OLDPWD=", 7);
		dir->env_dup[i] = ft_strndup(aux, (ft_strlen(aux))+1);
    }
}

void	my_cd(char **cmds,  t_dir_info *dir)
{
	char		*home;
	int			check;

	check = 1;
	if (cmds[1] == NULL
		|| (ft_strncmp(cmds[1], "~", 1) == 0 && ft_strlen(cmds[1]) == 1))
	{
		home = lookinenv(dir->env_dup, "HOME=");
		if (home == NULL)
			printf("HOME variable not set");
		else
			check =chdir(home);
	}
	else if (ft_strncmp(cmds[1], "-", 1) == 0)
		check = chdir(dir->prev_dir);
	else
		check = chdir(cmds[1]);
	if (check == 0)
		update_env(dir, cmds);
	else if (check < 0)
		printf("cd: %s: not a path or directory\n", cmds[1]);
}*/

t_dir_info	*my_pwd(char **envp)
{
	char cwd[4026];
	t_dir_info	*aux;
	
	getcwd(cwd, 0);
	aux = malloc(sizeof(t_dir_info));
	if (aux == NULL)
		return (NULL);
	aux->dir = lookinenv(envp, "PWD=");
	aux->prev_dir = lookinenv(envp, "OLDPWD=");
	return (aux);
}

void	my_cd(char **cmds, char **envp, t_dir_info *dir)
{
	char		*home;
	t_dir_info	*dir_info;

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
