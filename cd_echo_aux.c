/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_echo_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joya <joya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:14:06 by joya              #+#    #+#             */
/*   Updated: 2025/07/24 12:20:52 by joya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_quotes(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	echo_nothing(char **cmds)
{
	int	i;

	i = 1;
	if (sizematrix(cmds) == 3 && cmds[1] != NULL && cmds[1][0] == '-'
		&& cmds[1][1] == 'n')
		return (0);
	if (cmds[1] == NULL)
	{
		printf("\n");
		set_exit_status(0);
		return (0);
	}
	if (cmds[1] != NULL && cmds[1][1] == 'n' && cmds[1][0] == '-')
		i++;
	return (i);
}

void	echo_smth(char **cmds, int i, t_envp *envp_d)
{
	char	*arg;

	while (cmds[i + 1] != NULL)
	{
		arg = check_quotes(ft_strndup(cmds[i], ft_strlen(cmds[i]) + 1), envp_d);
		if (arg)
		{
			printf("%s ", arg);
			free(arg);
		}
		i++;
	}
	if (cmds[i] != NULL)
	{
		arg = check_quotes(ft_strndup(cmds[i], ft_strlen(cmds[i]) + 1), envp_d);
		if (arg)
		{
			printf("%s", arg);
			free(arg);
		}
	}
}
