/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_parsing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joya <joya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:13:40 by copito            #+#    #+#             */
/*   Updated: 2025/07/22 21:28:44 by joya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Cuenta el número de tokens en un comando con redirecciones
 * Identifica los operadores de redirección (<, >, <<, >>)
 * Cuenta los argumentos y nombres de archivos
 * Detecta errores de sintaxis como combinaciones inválidas de redirecciones
 * Retorna el número de tokens o -1 si hay un error de sintaxis
 */
int	count_tokens(char *cmd)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (cmd[i])
	{
		if ((cmd[i] == '<' || cmd[i] == '>') && (cmd[i + 1] == '<'
				|| cmd[i + 1] == '>'))
		{
			if (cmd[i] != cmd[i + 1])
				return (-1);
			i++;
		}
		if (cmd[i] == '<' || cmd[i] == '>')
			count++;
		else if (cmd[i] != ' ')
		{
			count++;
			while (cmd[i] && cmd[i] != ' ' && cmd[i] != '<' && cmd[i] != '>')
				i++;
		}
		i = check_end_of_token(cmd, i);
	}
	return (count);
}

/*
 * Cuenta el número total de tokens en el array de comandos
 */
int	count_total_tokens(char **cmds)
{
	int	total_count;

	total_count = 0;
	while (cmds[total_count])
		total_count++;
	return (total_count);
}

/*
 * Extrae un operador de redirección o un token de texto
 * Maneja correctamente operadores de redirección dobles (<<, >>)
 * Extrae un token completo (palabra) si no es un operador
 * Detecta errores de sintaxis en las redirecciones
 * Retorna la posición después del token procesado o -1 si hay error
 */
int	extract_operator_or_token(char *cmd, int i, char **result, int j)
{
	int	start;

	if ((cmd[i] == '<' || cmd[i] == '>') && (cmd[i + 1] == '<'
			|| cmd[i + 1] == '>') && cmd[i] != cmd[i + 1])
		printf("Syntax error\n");
	else if (ft_strncmp(cmd + i, "<<", 2) == 0
		|| ft_strncmp(cmd + i, ">>", 2) == 0)
	{
		result[j] = ft_strndup(cmd + i, 3);
		return (i + 2);
	}
	else if (cmd[i] == '<' || cmd[i] == '>')
	{
		result[j] = ft_strndup(cmd + i, 2);
		return (i + 1);
	}
	else
	{
		start = i;
		while (cmd[i] && cmd[i] != ' ' && cmd[i] != '<' && cmd[i] != '>')
			i++;
		result[j] = ft_strndup(cmd + start, i - start + 1);
		return (i);
	}
	return (-1);
}

/*
 * Verifica si hay errores de sintaxis en las redirecciones
 * Retorna 1 si hay error, 0 si no
 */
int	check_redirection_syntax(char **cmds)
{
	if (cmds[0] && (ft_strncmp(cmds[0], ">>", 3) == 0
			|| ft_strncmp(cmds[0], "<<", 3) == 0
			|| ft_strncmp(cmds[0], ">", 2) == 0
			|| ft_strncmp(cmds[0], "<", 2) == 0)
		&& (cmds[1] == NULL || cmds[1][0] == '\0'))
	{
		printf("Syntax error\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}

/*
 * Procesa un token individual de redirección
 * Retorna el tipo de redirección: 1=heredoc, 2=otros, 0=no es redirección
 */
int	process_redirection_token(char **cmds, int i)
{
	if (cmds[i] && ft_strncmp(cmds[i], "<<", 3) == 0)
	{
		handle_heredoc_redirection(cmds, i);
		return (1);
	}
	else if (cmds[i] && ft_strncmp(cmds[i], ">", 2) == 0)
	{
		handle_output_redirection(cmds, i);
		return (2);
	}
	else if (cmds[i] && ft_strncmp(cmds[i], ">>", 3) == 0)
	{
		handle_append_redirection(cmds, i);
		return (2);
	}
	else if (cmds[i] && ft_strncmp(cmds[i], "<", 2) == 0)
	{
		handle_input_redirection(cmds, i);
		return (2);
	}
	return (0);
}
