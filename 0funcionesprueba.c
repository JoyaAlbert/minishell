#include "minishell.h"
 »
void	update_env(char **envp)
{
    int i;
	char cwd[4026];
	char	*aux;

    i = -1;
    while (envp[++i] != NULL && ft_strnstr(envp[i], "PWD", 3) == NULL)
        ;
    if (envp[i] != NULL) 
	{
        getcwd(cwd, 0);
        aux = ft_strjoin("PWD=", cwd);
		envp[i] = ft_strndup(aux, (ft_strlen(aux))+1);
    }
	free(aux);
    i = -1;
    while (envp[++i] != NULL && ft_strnstr(envp[i], "OLDPWD", 6) == NULL)
        ;
    if (envp[i] != NULL) 
    {
        //if (dir->dir != NULL) 
           // aux = ft_strjoin("OLDPWD=", dir->dir); 
       // else
         //   aux = ft_strndup("OLDPWD=", 7);
		//envp[i] = ft_strndup(aux, (ft_strlen(aux))+1);
    }
}
/**
void	my_cd(char **cmds,  t_dir_info *dir)
{
	char		*home;
	int			check;

	check = 1;
	if (cmds[1] == NULL
		|| (ft_strncmp(cmds[1], "~", 1) == 0 && ft_strlen(cmds[1]) == 1))
	{
		home = lookinenv(envp, "HOME=");
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