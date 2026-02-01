/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copito <copito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:13:20 by copito            #+#    #+#             */
/*   Updated: 2025/07/31 11:26:30 by copito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//myvar="hola" '$myvar' "$PWD"
char	*get_variable(char *cmd, t_envp *envp_d)
{
	int		i;
	char	*variable;
	char	*clean;
	char	*temp;

	clean = NULL;
	i = 0;
	if (cmd[0] == '?' && (cmd[1] == ' ' || cmd[1] == '\''
			|| cmd[1] == '\"' || cmd[1] == '\0'))
		return (ft_itoa(get_exit_status()));
	while (cmd[i] != ' ' && cmd[i] != '\'' && cmd[i] != '\"' && cmd[i] != '\0')
		i++;
	temp = ft_strndup(cmd, i + 1);
	if (temp == NULL)
		return (NULL);
	variable = ft_strjoin(temp, "=");
	free(temp);
	if (variable == NULL)
		return (NULL);
	clean = lookinenv(envp_d->env_dup, variable);
	if (clean == NULL)
		clean = lookinenv(envp_d->vars, variable);
	free(variable);
	return (clean);
}

/*
** Inicializa la estructura de datos para el procesamiento de comillas
** Parametros: comando, buffer temporal, estructura de datos, indices
*/
void	init_quote_data(char *cmd, char *tmp, t_quote_data *data)
{
	data->cmd = cmd;
	data->i = 0;
	data->tmp = tmp;
	data->j = 0;
}

/*
** Elimina comillas y expande variables
*/
char	*remove_quotes_from_cmd(char *cmd, t_envp *envp_d)
{
	int				i;
	int				j;
	char			*result;
	char			*tmp;
	t_quote_data	data;

	tmp = malloc(ft_strlen(cmd) * 16 + 1);
	if (!tmp)
		return (NULL);
	init_quote_data(cmd, tmp, &data);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		data.i = &i;
		data.j = &j;
		if (!process_unquoted_content(&data, envp_d))
			return (free(tmp), NULL);
	}
	tmp[j] = '\0';
	free(cmd);
	result = ft_strndup(tmp, ft_strlen(tmp) + 1);
	free(tmp);
	return (result);
}

char	*quotes_actions(char *cmd, int i_double, int i_single, t_envp *envp_d)
{
	if (i_double || i_single)
	{
		printf("Syntax error around quotes\n");
		free(cmd);
		return (NULL);
	}
	return (remove_quotes_from_cmd(cmd, envp_d));
}

char	*check_quotes(char *cmd, t_envp *envp_d)
{
	int	i;
	int	i_double;
	int	i_single;

	i = 0;
	i_double = 0;
	i_single = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '"')
		{
			if (i_single == 0)
				i_double = !i_double;
		}
		else if (cmd[i] == '\'')
		{
			if (i_double == 0)
				i_single = !i_single;
		}
		i++;
	}
	cmd = quotes_actions(cmd, i_double, i_single, envp_d);
	return (cmd);
}
