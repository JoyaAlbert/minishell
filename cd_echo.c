/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joya <joya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:11:25 by copito            #+#    #+#             */
/*   Updated: 2025/07/24 12:16:08 by joya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_echo(char **cmds, t_envp *envp_d)
{
	int		i;

	i = echo_nothing(cmds);
	if (i == 0)
		return ;
	echo_smth(cmds, i, envp_d);
	if (cmds[1] != NULL && (cmds[1][1] != 'n' || cmds[1][0] != '-'))
		printf("\n");
	set_exit_status(0);
}

void	aux_mycd(char **cmds, t_dir_info *dir, t_dir_info *dir_info, int check)
{
	if (check < 0 && ft_strncmp(cmds[1], "-", 1) != 0)
	{
		printf("cd: %s: not a path or directory\n", cmds[1]);
		set_exit_status(1);
		return ;
	}
	dir = dir_info;
	(void)dir;
	free(dir_info);
	set_exit_status(0);
}

int	my_prevcd(char **cmds, char **envp, t_dir_info *dir)
{
	int		check;
	char	*env;

	(void)dir;
	check = 1;
	if (cmds[1] == NULL)
		return (check);
	if (ft_strncmp(cmds[1], "-", 1) == 0 && ft_strlen(cmds[1]) == 1)
	{
		env = lookinenv(envp, "OLDPWD=");
		if (env == NULL)
		{
			printf("cd: OLDPWD not set\n");
			set_exit_status(1);
		}
		check = chdir(env);
	}
	return (check);
}

t_dir_info	*update_and_change(char **envp, t_dir_info *dir)
{
	t_dir_info	*aux;

	update_env(envp, dir);
	aux = my_pwd(envp);
	printf("%s\n", aux->dir);
	set_exit_status(0);
	return (aux);
}

void	my_cd(char **cmds, char **envp, t_dir_info *dir)
{
	char		*home;
	int			check;
	t_dir_info	*dir_info;

	//check = 1;
	check = my_prevcd(cmds, envp, dir);
	if (cmds[1] == NULL
		|| (ft_strncmp(cmds[1], "-", 1) == 0 && ft_strlen(cmds[1]) == 1))
	{
		home = lookinenv(envp, "HOME=");
		if (home == NULL)
		{
			printf("HOME variable not set");
			set_exit_status(1);
			return ;
		}
		check = chdir(home);
	}
	else if (cmds[1] != NULL && ft_strncmp(cmds[1], "-", 1) != 0)
		check = chdir(cmds[1]);
	if (check == 0)
		dir_info = update_and_change(envp, dir);
	else
		set_exit_status(1);
	aux_mycd(cmds, dir, dir_info, check);
}
