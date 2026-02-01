/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joya <joya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:13:53 by copito            #+#    #+#             */
/*   Updated: 2025/07/22 21:54:13 by joya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_dup(t_envp *envp_d, t_var *var)
{
	int		i;
	int		j;
	char	**aux;

	i = -1;
	j = 0;
	aux = malloc((sizematrix(envp_d->env_dup) - 1) * sizeof(char *));
	if (aux == NULL)
		msg("Memory error\n");
	while (envp_d->env_dup[++i] != NULL)
	{
		if (ft_strncmp(envp_d->env_dup[i], var->name,
				ft_strlen(var->name)) == 0)
			i++;
		if (envp_d->env_dup[i] != NULL)
			aux[j] = ft_strndup(envp_d->env_dup[i],
					ft_strlen(envp_d->env_dup[i]) + 1);
		if (aux[j] == NULL)
			msg("Memory error\n");
		if (envp_d->env_dup[i] == NULL)
			break ;
		j++;
	}
	aux[j] = NULL;
	free_dup(envp_d, aux);
}

void	unset_dup(t_var *var, t_envp *envp_d)
{
	int	i;

	i = 0;
	if (envp_d->env_dup != NULL)
	{
		while (envp_d->env_dup[i] != NULL)
		{
			if (ft_strncmp(envp_d->env_dup[i], var->name,
					ft_strlen(var->name)) == 0)
			{
				delete_dup(envp_d, var);
				break ;
			}
			i++;
		}
	}
}

void	unset_var(t_var *var, t_envp *envp_d)
{
	int	i;

	i = 0;
	if (envp_d->vars != NULL)
	{
		while (envp_d->vars[i] != NULL)
		{
			if (ft_strncmp(envp_d->vars[i], var->name,
					ft_strlen(var->name)) == 0)
			{
				if (sizematrix(envp_d->vars) == 2)
				{
					envp_d->vars = NULL;
					break ;
				}
				delete_var(envp_d, var);
				break ;
			}
			i++;
		}
	}
}

int	chaeck_equal_var_name(char *var_name)
{
	int	i;

	i = 0;
	while (var_name[i] != '\0' && var_name[i] != '=')
		i++;
	if (var_name[i] == '=')
		return (0);
	return (1);
}

void	unset_variable(char **cmds, t_envp *envp_d)
{
	int		i;
	t_var	*var;

	i = 0;
	var = malloc(sizeof(t_var));
	if (var == NULL)
		msg("Memory error\n");
	while (cmds[i] != NULL)
	{
		var->name = extract_name(cmds[i]);
		var->value = extract_value(cmds[i]);
		if (var->value[0] == '\0' && chaeck_equal_var_name(var->name) == 1)
		{
			unset_var(var, envp_d);
			unset_dup(var, envp_d);
		}
		free(var->name);
		free(var->value);
		i++;
	}
	free(var);
}
