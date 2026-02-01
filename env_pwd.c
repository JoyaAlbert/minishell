/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copito <copito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:11:31 by copito            #+#    #+#             */
/*   Updated: 2025/07/25 18:01:01 by copito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dir_info	*my_pwd(char **envp)
{
	char		cwd[4026];
	t_dir_info	*aux;

	(void)envp;
	aux = malloc(sizeof(t_dir_info));
	if (aux == NULL)
	{
		msg("Error allocating memory");
		return (NULL);
	}
	aux->prev_dir = getenv("OLDPWD");
	getcwd(aux->dir, sizeof(cwd));
	return (aux);
}

int	show_env(char **envp)
{
	int	i;

	i = -1;
	if (envp == NULL)
		return (0);
	while (envp[++i] != NULL)
		printf("%s\n", envp[i]);
	return (1);
}

void	update_env(char **envp, t_dir_info *dir)
{
	int		i;
	char	cwd[4026];
	char	*aux;

	i = -1;
	while (envp[++i] != NULL && ft_strnstr(envp[i], "PWD", 3) == NULL)
		;
	if (envp[i] != NULL)
	{
		free(envp[i]);
		getcwd(cwd, sizeof(cwd));
		aux = ft_strjoin("PWD=", cwd);
		envp[i] = ft_strndup(aux, (ft_strlen(aux)) + 1);
	}
	free(aux);
	i = -1;
	while (envp[++i] != NULL && ft_strnstr(envp[i], "OLDPWD", 6) == NULL)
		;
	if (envp[i] != NULL)
	{
		free(envp[i]);
		aux = ft_strjoin("OLDPWD=", dir->dir);
		envp[i] = ft_strndup(aux, (ft_strlen(aux)) + 1);
		free(aux);
	}
}

char	*lookinenv(char **envp, char *lookfor)
{
	int	i;

	i = 0;
	if (envp == NULL || lookfor == NULL)
		return (NULL);
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], lookfor, ft_strlen(lookfor)) != NULL)
		{
			if (ft_strnstr(lookfor, "PATH=/", 6) != NULL)
				return (ft_strnstr(envp[i], lookfor, ft_strlen(lookfor)));
			else
				return (ft_strnstr(envp[i], lookfor, ft_strlen(lookfor))
					+ ft_strlen(lookfor));
		}
		i++;
	}
	return (NULL);
}

void	update_shlvl(char **envp)
{
	int		i;
	char	*aux;
	char	*num;

	i = -1;
	while (envp[++i] != NULL && ft_strnstr(envp[i], "SHLVL", 5) == NULL)
		;
	if (envp[i] == NULL)
		return ;
	num = ft_itoa(ft_atoi(lookinenv(envp, "SHLVL=")) + 1);
	aux = ft_strjoin("SHLVL=", num);
	free(envp[i]);
	envp[i] = ft_strndup(aux, (ft_strlen(aux)) + 1);
	free(aux);
	free(num);
}
