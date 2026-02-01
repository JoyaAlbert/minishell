/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copito <copito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 21:57:05 by joya              #+#    #+#             */
/*   Updated: 2025/07/31 15:22:24 by copito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils/utils.h"

int	check_builtins(char *cmd)
{
	char	**cmds;

	cmds = split_outside_quotes(cmd, ' ');
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
	matrixfree(cmds);
	return (1);
}

int	check_pipe(char *cmd)
{
	int	i;
	int	count;
	int	in_single;
	int	in_double;

	i = -1;
	in_single = 0;
	in_double = 0;
	while (cmd[++i] != '\0')
	{
		if (cmd[i] == '"' && !in_single)
			in_double = !in_double;
		else if (cmd[i] == '\'' && !in_double)
			in_single = !in_single;
		if (cmd[i] == '|' && !in_single && !in_double)
		{
			count = 0;
			while (cmd[i] == '|' && cmd[i] != '\0')
			{
				i++;
				count++;
			}
			if (count > 1)
				return (-1);
			while (cmd[i] == ' ')
				i++;
			if (cmd[i] == '\0')
				return (-1);
		}
	}
	// Buscar un pipe fuera de comillas
	i = 0;
	in_single = 0;
	in_double = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '"' && !in_single)
			in_double = !in_double;
		else if (cmd[i] == '\'' && !in_double)
			in_single = !in_single;
		if (cmd[i] == '|' && !in_single && !in_double)
			return (0);
		i++;
	}
	return (1);
}

int	parse_redirections(char *cmd)
{
	int	i;

	i = 0;
	if (!ft_strncmp(cmd, "echo", 4) && echo_quotes(cmd) == 1)
		return (1);
	while (cmd[i])
	{
		if (cmd[i] == '>' && cmd[i + 1] == '>')
		{
			if (cmd[i + 2] == '>')
				return (-1);
			i = i + 2;
		}
		else if (cmd[i] == '<' && cmd[i + 1] == '<')
		{
			if (cmd[i + 2] == '<')
				return (-1);
			i = i + 2;
		}
		else
			i++;
	}
	if (ft_strnstr(cmd, "<", ft_strlen(cmd)) != NULL
		|| ft_strnstr(cmd, ">", ft_strlen(cmd)) != NULL)
		return (0);
	return (1);
}

void	exit_build(char **cmd)
{
	int	exit_status;

	if (cmd[1] != NULL && cmd[2] != NULL)
	{
		printf("exit: too many arguments\n");
		return ;
	}
	if (cmd[1] == NULL)
	{
		//free_envp(envp_d);
		exit(0);
	}
	exit_status = ft_atoi(cmd[1]);
	if (exit_status < 0 || exit_status > 255)
	{
		printf("exit: %s: numeric argument required\n", cmd[1]);
		//free_envp(envp_d);
		exit(255);
	}
	//free_envp(envp_d);
	exit(exit_status);
}

void	sendto_builtin(char **cmds, t_dir_info *dir,
		char **envp, t_envp *envp_d)
{
	(void)envp;
	if (!ft_strncmp(cmds[0], "pwd", 3) && ft_strlen(cmds[0]) == 3)
		printf("%s\n", dir->dir);
	else if (!ft_strncmp(cmds[0], "env", 3) && ft_strlen(cmds[0]) == 3)
		show_env(envp);
	else if (!ft_strncmp(cmds[0], "cd", 2) && ft_strlen(cmds[0]) == 2)
	{
		if (cmds[1] != NULL && cmds[2] != NULL)
		{
			printf("cd: too many arguments\n");
			return ((void)0);
		}
		my_cd(cmds, envp, dir);
	}
	else if (!ft_strncmp(cmds[0], "echo", 4) && ft_strlen(cmds[0]) == 4)
		my_echo(cmds, envp_d);
	else if (!ft_strncmp(cmds[0], "unset", 5) && ft_strlen(cmds[0]) == 5)
		unset_variable(cmds, envp_d);
	else if (!ft_strncmp(cmds[0], "export", 6) && ft_strlen(cmds[0]) == 6)
		export_variable(cmds[1], envp_d);
	if (!ft_strncmp(cmds[0], "exit", 4) && ft_strlen(cmds[0]) == 6)
		exit_build(cmds);
}
