/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_processing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copito <copito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:13:09 by copito            #+#    #+#             */
/*   Updated: 2025/07/31 14:10:43 by copito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Procesa el contenido dentro de comillas (simples o dobles)
** Parametros: estructura de datos, tipo de comilla, entorno
** Como: Distingue entre comillas dobles (expande variables) y simples (literal)
** Para comillas dobles: expande variables con $, para simples: copia literal
*/
char	*process_quoted_content(t_quote_data *data, char quote, t_envp *envp_d)
{
	while (data->cmd[*(data->i)] && data->cmd[*(data->i)] != quote)
	{
		data->tmp = handle_variable_expansion(data, quote, envp_d);
		if (!data->tmp)
			return (NULL);
	}
	return (data->tmp);
}

/*
** Procesa una seccion con comillas del comando
** Parametros: estructura de datos, entorno
*/
char	*process_quote_section(t_quote_data *data, t_envp *envp_d)
{
	char	quote;
	char	*tmp;

	quote = data->cmd[*(data->i)];
	(*(data->i))++;
	tmp = process_quoted_content(data, quote, envp_d);
	if (!tmp)
		return (NULL);
	if (data->cmd[*(data->i)] == quote)
		(*(data->i))++;
	return (tmp);
}

char	*dollarout(char *cmd)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = malloc(ft_strlen(cmd));
	if (tmp == NULL)
		return (NULL);
	i = 1;
	j = 0;
	while (cmd[i] != '\0')
	{
		tmp[j] = cmd[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

/*
** Procesa contenido fuera de comillas
*/
int	process_unquoted_content(t_quote_data *data, t_envp *envp_d)
{
	char	*var;
	int		free_var;

	if (data->cmd[*(data->i)] == '\'' || data->cmd[*(data->i)] == '"')
	{
		if (!process_quote_section(data, envp_d))
			return (0);
	}
	else if (data->cmd[*(data->i)] == '$' && data->cmd[*(data->i) + 1] == '?')
		handle_exit_status_expansion(data->tmp, data->j, data->i);
	else if (data->cmd[*(data->i)] == '$' && data->cmd[*(data->i) + 1]
		&& data->cmd[*(data->i) + 1] != ' ' && data->cmd[*(data->i) + 1] != '\''
		&& data->cmd[*(data->i) + 1] != '"' && data->cmd[*(data->i) + 1] != '?')
	{
		free_var = expand_variable_in_quotes(data->cmd, data->i, envp_d, &var);
		if (var)
		{
			data->tmp = copy_var_to_buff(data->tmp, data->j, var,
					ft_strlen(data->cmd) * 16);
			if (free_var)
				free(var);
		}
	}
	else
		data->tmp[(*data->j)++] = data->cmd[(*data->i)++];
	return (1);
}

/*
** Copia caracteres literales dentro de comillas simples
** Parametros: estructura de datos, tipo de comilla
*/
char	*copy_literal_in_single_quotes(t_quote_data *data, char quote)
{
	data->tmp[*(data->j)] = data->cmd[*(data->i)];
	(*(data->j))++;
	(*(data->i))++;
	while (data->cmd[*(data->i)] && data->cmd[*(data->i)] != quote)
	{
		data->tmp[*(data->j)] = data->cmd[*(data->i)];
		(*(data->j))++;
		(*(data->i))++;
	}
	return (data->tmp);
}
