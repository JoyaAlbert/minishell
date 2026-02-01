/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copito <copito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:11:52 by copito            #+#    #+#             */
/*   Updated: 2025/07/09 20:41:19 by copito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_and_process_var(t_envp *envp_d, char *cmd, t_var *var)
{
	int		i;

	i = -1;
	while (envp_d->vars[++i] != NULL)
	{
		if (ft_strncmp(envp_d->vars[i], cmd, ft_strlen(cmd)) == 0)
		{
			var->name = extract_name(envp_d->vars[i]);
			var->value = extract_value(envp_d->vars[i]);
			if (sizematrix(envp_d->vars) == 2)
			{
				envp_d->vars = NULL;
				return (1);
			}
			delete_var(envp_d, var);
			return (1);
		}
	}
	return (0);
}

void	export_no_equal(t_envp *envp_d, char *cmd)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (var == NULL)
		msg("Memory error\n");
	var->name = NULL;
	var->value = NULL;
	if (envp_d->vars != NULL)
	{
		if (find_and_process_var(envp_d, cmd, var))
			add_dup(envp_d, var);
	}
	free_var(var);
}

void	add_dup(t_envp *envp_d, t_var *var)
{
	char	**aux;
	char	*new;
	int		i;

	i = 0;
	new = ft_strjoin(var->name, var->value);
	aux = malloc((sizematrix(envp_d->env_dup) + 2) * sizeof(char *));
	if (aux == NULL || new == NULL)
		msg("Memory error\n");
	while (envp_d->env_dup[i] != NULL)
	{
		aux[i] = ft_strndup(envp_d->env_dup[i],
				ft_strlen(envp_d->env_dup[i]) + 1);
		i++;
	}
	aux[i] = ft_strndup(new, ft_strlen(new) + 1);
	i++;
	aux[i] = NULL;
	matrixfree(envp_d->env_dup);
	envp_d->env_dup = dupmatrix(aux);
	matrixfree(aux);
	free(new);
}
