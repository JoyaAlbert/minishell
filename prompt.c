/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joya <joya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:12:59 by copito            #+#    #+#             */
/*   Updated: 2025/07/24 10:40:42 by joya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exit_args(char **cmds)
{
	int	i;

	i = -1;
	if (cmds[1] != NULL && cmds[2] != NULL)
	{
		printf("exit: too many arguments\n");
		matrixfree(cmds);
		return (0);
	}
	if (cmds[1] != NULL)
	{
		while (cmds[1][++i] != '\0')
		{
			if (!ft_isdigit(cmds[1][i]))
			{
				printf("exit: numeric argument required\n");
				matrixfree(cmds);
				return (0);
			}
		}
	}
	return (1);
}

int	exit_built(char *cmd, t_dir_info *dir_info, t_envp *envp_d)
{
	char	**cmds;

	cmds = ft_split(cmd, ' ');
	(void)envp_d;
	if (ft_strnstr(cmd, "exit", ft_strlen(cmd) + 1) != NULL)
	{
		free(cmd);
		free(dir_info);
		if (check_exit_args(cmds) == 0)
			return (0);
		if (cmds[1] != NULL)
			exit(ft_atoi(cmds[1]));
		matrixfree(cmds);
		exit(0);
	}
	free(cmd);
	free(dir_info);
	matrixfree(cmds);
	return (0);
}

int	check_spaces(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] == ' ' || cmd[i] == '\t')
		i++;
	if (cmd[i] == '\0')
		return (1);
	return (0);
}

int	free_struct_cmd(char *cmd, t_dir_info *dir_info)
{
	free(dir_info);
	free(cmd);
	return (0);
}

int	prompt(t_envp *envp_d)
{
	char		*cmd;
	t_dir_info	*dir_info;

	signal_handler();
	dir_info = my_pwd(envp_d->env_dup);
	cmd = readline(PROMPT);
	if (cmd == NULL)
	{
		free(dir_info);
		return (1);
	}
	add_history(cmd);
	if (ft_strncmp(cmd, "echo", 4) && ft_strlen(cmd) != 4)
		cmd = check_quotes(cmd, envp_d);
	if (cmd == NULL)
	{
		free(dir_info);
		return (0);
	}
	if (ft_strlen(cmd) == 0 || check_spaces(cmd) == 1)
		return (free_struct_cmd(cmd, dir_info));
	parser(dir_info, envp_d->env_dup, cmd, envp_d);
	if (is_variable_assignment(cmd) == 1)
		check_variables(cmd, envp_d);
	return (exit_built(cmd, dir_info, envp_d));
}
