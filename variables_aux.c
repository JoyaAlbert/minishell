/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copito <copito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:14:00 by copito            #+#    #+#             */
/*   Updated: 2025/07/09 21:40:44 by copito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_variable_assignment(char *cmd)
{
	int	i;

	i = 0;
	if (ft_strncmp(cmd, "export ", 7) == 0)
		return (0);
	while (cmd[i] != '=' && cmd[i] != '\0')
		i++;
	if (cmd[i] != '\0' && i != 0 && cmd[i - 1] != ' ' && cmd[i + 1] != ' ')
		return (1);
	return (0);
}

int	check_var_name(char *var_name)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (var_name[i] != '\0' && var_name[i] != '=')
	{
		if (ft_isalpha(var_name[i]) == 1)
			a++;
		i++;
	}
	if (a == 0)
		return (0);
	return (1);
}

/*ASIGNACIÓN: 
87= : command not found 0
87=h: command not found 0
hola=: nada 1
EXPORT:
67= : not a valid identifier
87=u : ==
hola=: lo pone
*/
char	*extract_name(char *cmd)
{
	int		i;
	char	*aux;

	i = 0;
	while (cmd[i] && cmd[i] != '=')
		i++;
	aux = ft_strndup(cmd, i + 2);
	if (aux == NULL)
	{
		printf("Memory error\n");
		return (NULL);
	}
	return (aux);
}

char	*extract_value(char *cmd)
{
	int		i;
	char	*aux;

	i = 0;
	while (cmd[i] && cmd[i] != '=')
		i++;
	if (cmd[i] == '=')
		i++;
	aux = ft_strndup(&cmd[i], ft_strlen(cmd + i) + 1);
	if (aux == NULL)
	{
		printf("Memory error\n");
		return (NULL);
	}
	return (aux);
}

int	var_no_null(t_var *var, t_envp *envp_d)
{
	char	**aux;
	char	*new;
	int		i;

	i = 0;
	new = ft_strjoin(var->name, var->value);
	aux = malloc((sizematrix(envp_d->vars) + 2) * sizeof(char *));
	if (aux == NULL || new == NULL)
		msg("Memory error\n");
	while (envp_d->vars[i] != NULL)
	{
		aux[i] = ft_strndup(envp_d->vars[i], ft_strlen(envp_d->vars[i]) + 1);
		i++;
	}
	aux[i] = ft_strndup(new, ft_strlen(new) + 1);
	i++;
	aux[i] = NULL;
	free(new);
	matrixfree(envp_d->vars);
	envp_d->vars = dupmatrix(aux);
	matrixfree(aux);
	return (1);
}
