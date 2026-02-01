/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copito <copito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:11:57 by copito            #+#    #+#             */
/*   Updated: 2025/07/09 20:45:27 by copito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_dup(t_envp *envp_d, t_var *var)
{
	int		i;
	char	*new;

	if (envp_d->env_dup == NULL)
		return (0);
	i = -1;
	new = ft_strjoin(var->name, var->value);
	if (new == NULL)
		msg("Memory error\n");
	while (envp_d->env_dup[++i] != NULL)
	{
		if (ft_strncmp(envp_d->env_dup[i], var->name,
				ft_strlen(var->name)) == 0)
		{
			free(envp_d->env_dup[i]);
			envp_d->env_dup[i] = new;
			return (1);
		}
	}
	free(new);
	add_dup(envp_d, var);
	return (1);
}

void	delete_var(t_envp *envp_d, t_var *var)
{
	int		i;
	int		j;
	char	**au;

	i = -1;
	j = 0;
	au = malloc((sizematrix(envp_d->vars) - 1) * sizeof(char *));
	if (au == NULL)
		msg("Memory error\n");
	while (envp_d->vars[++i] != NULL)
	{
		if (ft_strncmp(envp_d->vars[i], var->name, ft_strlen(var->name)) == 0)
			i++;
		if (envp_d->vars[i] != NULL)
			au[j] = ft_strndup(envp_d->vars[i], ft_strlen(envp_d->vars[i]) + 1);
		if (au[j] == NULL)
			msg("Memory error\n");
		if (envp_d->vars[i] == NULL)
			break ;
		j++;
	}
	au[j] = NULL;
	matrixfree(envp_d->vars);
	envp_d->vars = dupmatrix(au);
	matrixfree(au);
}

int	export_var(t_envp *envp_d, t_var *var)
{
	int		i;

	if (envp_d->vars != NULL)
	{
		i = 0;
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
	export_dup(envp_d, var);
	return (0);
}
