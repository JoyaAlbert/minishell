/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copito <copito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:12:06 by copito            #+#    #+#             */
/*   Updated: 2025/07/09 22:07:41 by copito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_equal(t_envp *envp_d, char *cmd)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (var == NULL)
		msg("Memory error\n");
	var->name = extract_name(cmd);
	var->value = extract_value(cmd);
	export_var(envp_d, var);
	free_var(var);
	return (0);
}

static void	print_exported_vars(t_envp *envp_d)
{
	int	i;

	if (envp_d->env_dup != NULL)
	{
		i = 0;
		while (envp_d->env_dup[i] != NULL)
		{
			printf("declare -x %s\n", envp_d->env_dup[i]);
			i++;
		}
	}
}

int	export_variable(char *cmd, t_envp *envp_d)
{
	int		i;

	if (cmd == NULL)
	{
		print_exported_vars(envp_d);
		return (0);
	}
	i = 0;
	if (check_var_name(cmd) == 0)
	{
		printf("Not a valid argument\n");
		return (0);
	}
	while (cmd[i] != '\0' && cmd[i] != '=')
		i++;
	if (cmd[i] == '=')
	{
		if (i != 0 && cmd[i - 1] != ' ')
			export_equal(envp_d, cmd);
	}
	else
		export_no_equal(envp_d, cmd);
	return (0);
}

void	free_dup(t_envp *envp_d, char **aux)
{
	matrixfree(envp_d->env_dup);
	envp_d->env_dup = dupmatrix(aux);
	matrixfree(aux);
}
