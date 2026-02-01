/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copito <copito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:14:07 by copito            #+#    #+#             */
/*   Updated: 2025/07/09 21:42:33 by copito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_null(t_var *var, t_envp *envp_d)
{
	char	*new;

	new = ft_strjoin(var->name, var->value);
	if (new == NULL)
		msg("Memory error\n");
	envp_d->vars = (char **)malloc(2 * sizeof(char *));
	if (envp_d->vars == NULL)
		msg("Memory error\n");
	envp_d->vars[0] = new;
	envp_d->vars[1] = NULL;
	return (1);
}

int	check_vars(t_var *var, t_envp *envp_d)
{
	int		i;
	char	*new;
	int		result;

	if (envp_d->vars != NULL)
	{
		i = -1;
		new = ft_strjoin(var->name, var->value);
		if (new == NULL)
			msg("Memory error\n");
		while (envp_d->vars[++i] != NULL)
		{
			if (ft_strncmp(envp_d->vars[i], var->name,
					ft_strlen(var->name)) == 0)
			{
				free(envp_d->vars[i]);
				envp_d->vars[i] = new;
				return (1);
			}
		}
		result = var_no_null(var, envp_d);
		free(new);
		return (result);
	}
	return (var_null(var, envp_d));
}

int	check_dup(t_var *var, t_envp *envp_d)
{
	int		i;
	char	*new;

	if (envp_d->env_dup == NULL)
		return (0);
	i = 0;
	new = ft_strjoin(var->name, var->value);
	if (new == NULL)
		msg("Memory error\n");
	while (envp_d->env_dup[i] != NULL)
	{
		if (ft_strncmp(envp_d->env_dup[i], var->name,
				ft_strlen(var->name)) == 0)
		{
			free(envp_d->env_dup[i]);
			envp_d->env_dup[i] = new;
			return (1);
		}
		i++;
	}
	free(new);
	return (0);
}

int	process_variable_assignment(t_envp *envp_d, char *cmd)
{
	t_var	*var;
	int		result;

	var = malloc(sizeof(t_var));
	if (var == NULL)
		return (memory_error());
	var->name = extract_name(cmd);
	var->value = extract_value(cmd);
	if (check_var_name(var->name) == 0)
		return (0);
	if (var->value[0] == '\0')
		return (1);
	result = check_dup(var, envp_d);
	if (result == 0)
	{
		result = check_vars(var, envp_d);
		if (result == 0)
		{
			free_var(var);
			return (0);
		}
	}
	free_var(var);
	return (1);
}

void	check_variables(char *cmd, t_envp *envp_d)
{
	int		i;
	int		result;

	i = 0;
	while (cmd[i] != '=' && cmd[i] != '\0')
		i++;
	if (cmd[i] != '\0')
	{
		if (i != 0 && cmd[i - 1] != ' ' && cmd[i + 1] != ' ')
		{
			result = process_variable_assignment(envp_d, cmd);
			if (result == 0)
			{
				printf("aCommand not found\n");
				set_exit_status(127);
			}
			print_matrix(envp_d->vars);//no olvidar quitarlo
		}
		else
		{
			printf("bCommand not found\n");
			set_exit_status(127);
		}
	}
}
