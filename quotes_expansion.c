/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copito <copito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:13:04 by copito            #+#    #+#             */
/*   Updated: 2025/07/31 14:06:17 by copito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Expande una variable dentro de comillas dobles
** Parametros: comando, indice actual, estructura de entorno, puntero a variable
** Como: Obtiene el valor de la variable usando get_variable y avanza
** el indice saltando el nombre de la variable
** Retorna 1 si la variable es $? y 0 en caso contrario
*/
int	expand_variable_in_quotes(char *cmd, int *i, t_envp *envp_d,
	char **variable)
{
	*variable = get_variable(cmd + *i + 1, envp_d);
	(*i)++;
	if (cmd[*i] == '?')
	{
		(*i)++;
		return (1);
	}
	while (cmd[*i] && cmd[*i] != ' ' && cmd[*i] != '\''
		&& cmd[*i] != '\"' && cmd[*i] != '\0')
		(*i)++;
	return (0);
}

/*
** Expande variables dentro de comillas dobles
** Parametros: estructura de datos, entorno
*/
char	*expand_double_quote_variable(t_quote_data *data, t_envp *envp_d)
{
	char	*variable;
	int		should_free;

	should_free = expand_variable_in_quotes(data->cmd, data->i,
			envp_d, &variable);
	if (variable)
	{
		data->tmp = copy_var_to_buff(data->tmp, data->j,
				variable, ft_strlen(data->cmd) * 16);
		if (should_free)
			free(variable);
		if (!data->tmp)
			return (NULL);
	}
	return (data->tmp);
}

/*
** Maneja la expansion de variables en comillas dobles
** Parametros: estructura de datos, tipo de comilla, entorno
*/
char	*handle_variable_expansion(t_quote_data *data, char quote,
		t_envp *envp_d)
{
	if (quote == '\"' && data->cmd[*(data->i)] == '$')
		return (expand_double_quote_variable(data, envp_d));
	else if (quote == '\'' && data->cmd[*(data->i)] == '$')
		return (copy_literal_in_single_quotes(data, quote));
	else
	{
		data->tmp[*(data->j)] = data->cmd[*(data->i)];
		(*(data->j))++;
		(*(data->i))++;
	}
	return (data->tmp);
}

/*
** Procesa expansion de $? fuera de comillas
*/
void	handle_exit_status_expansion(char *tmp, int *j, int *i)
{
	char	*exit_str;
	int		k;

	exit_str = ft_itoa(get_exit_status());
	if (exit_str)
	{
		k = 0;
		while (exit_str[k])
			tmp[(*j)++] = exit_str[k++];
		free(exit_str);
	}
	*i += 2;
}

/*
** Copia el contenido de una variable expandida al buffer temporal
** Parametros: buffer temporal, indice actual, variable a copiar, 
longitud del comando
** Como: Itera caracter por caracter copiando la variable al buffer
** respetando los limites para evitar desbordamiento
*/
char	*copy_var_to_buff(char *tmp, int *j, char *variable,
		int buf_size)
{
	while (*variable && *j < buf_size - 1)
	{
		tmp[(*j)++] = *variable++;
	}
	return (tmp);
}
