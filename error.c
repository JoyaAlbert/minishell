/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copito <copito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:11:35 by copito            #+#    #+#             */
/*   Updated: 2025/07/09 20:31:23 by copito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//revisar donde se usa si tiene que salir del programa o no
void	msg(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
		write(2, &str[i], 1);
	write(2, "\n", 1);
	exit(1);
}

void	fork_fail(char **cmds, int pid)
{
	if (pid < 0)
	{
		matrixfree(cmds);
		msg("Fork Failed");
	}
}

void	free_var(t_var *var)
{
	if (var->name != NULL)
		free(var->name);
	if (var->value != NULL)
		free(var->value);
	free(var);
}

int	memory_error(void)
{
	printf("Memory error\n");
	return (-1);
}
