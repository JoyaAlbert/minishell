/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joya <joya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:13:47 by copito            #+#    #+#             */
/*   Updated: 2025/07/22 21:28:44 by joya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Maneja la redirección de salida en modo append (>>)
 * Abre o crea el archivo especificado con permisos 0644 en modo append
 * Redirige la salida estándar al archivo
 * Libera la memoria asignada a los tokens de redirección
 */
void	handle_append_redirection(char **cmds, int i)
{
	int	fd;

	if (!cmds[i + 1] || cmds[i + 1][0] == '\0')
	{
		printf("Syntax error\n");
		exit(EXIT_FAILURE);
	}
	fd = open(cmds[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		msg("Error opening file for appending");
	if (dup2(fd, STDOUT_FILENO) == -1)
		msg("Error while duping file descriptor");
	close(fd);
	free(cmds[i]);
	free(cmds[i + 1]);
	cmds[i] = NULL;
	cmds[i + 1] = NULL;
}

/*
 * Implementa la funcionalidad de heredoc (<<)
 * Crea una tubería para almacenar la entrada
 * Lee líneas desde la entrada estándar hasta encontrar el delimitador
 * Redirige la entrada estándar para leer desde la tubería
 * Libera la memoria asignada a los tokens de redirección
 */
void	handle_heredoc_redirection(char **cmds, int i)
{
	int	pipe_fd[2];
	int	result;

	if (!cmds[i + 1] || cmds[i + 1][0] == '\0')
	{
		printf("Syntax error\n");
		exit(EXIT_FAILURE);
	}
	if (pipe(pipe_fd) == -1)
		msg("Error creating pipe for heredoc");
	result = 0;
	while (result == 0)
		result = read_and_check_delimiter(pipe_fd[1], cmds[i + 1]);
	setup_heredoc_input(pipe_fd);
	free(cmds[i]);
	free(cmds[i + 1]);
	cmds[i] = NULL;
	cmds[i + 1] = NULL;
}

/*
 * Maneja la redirección de entrada (<)
 * Abre el archivo especificado en modo de solo lectura
 * Redirige la entrada estándar para leer desde el archivo
 * Libera la memoria asignada a los tokens de redirección
 */
void	handle_input_redirection(char **cmds, int i)
{
	int	fd;

	if (!cmds[i + 1] || cmds[i + 1][0] == '\0')
	{
		printf("Syntax error\n");
		exit(EXIT_FAILURE);
	}
	fd = open(cmds[i + 1], O_RDONLY);
	if (fd == -1)
		msg("Error opening input file");
	if (dup2(fd, STDIN_FILENO) == -1)
		msg("Error while duping file descriptor");
	close(fd);
	free(cmds[i]);
	free(cmds[i + 1]);
	cmds[i] = NULL;
	cmds[i + 1] = NULL;
}

/*
 * Maneja la redirección de salida (>)
 * Abre o crea el archivo especificado con permisos 0644, truncando si ya existe
 * Redirige la salida estándar al archivo
 * Libera la memoria asignada a los tokens de redirección
 */
void	handle_output_redirection(char **cmds, int i)
{
	int	fd;

	if (!cmds[i + 1] || cmds[i + 1][0] == '\0')
	{
		printf("Syntax error\n");
		exit(EXIT_FAILURE);
	}
	fd = open(cmds[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		msg("Error opening output file");
	if (dup2(fd, STDOUT_FILENO) == -1)
		msg("Error while duping file descriptor");
	close(fd);
	free(cmds[i]);
	free(cmds[i + 1]);
	cmds[i] = NULL;
	cmds[i + 1] = NULL;
}

/*
 * Función principal para manejar todas las redirecciones en un comando
 * 
 * Esta función procesa todos los tipos de redirección en una línea de comandos:
 * - Redirección de entrada (<): lee datos desde un archivo
 * - Redirección de salida (>): escribe datos a un archivo, truncándolo
 * - Redirección de salida en modo append (>>): añade datos al final 
 de un archivo
 * - Heredoc (<<): lee entrada interactiva hasta encontrar un delimitador
 * 
 * Funcionamiento:
 * 1. Cuenta el total de tokens en el comando usando count_total_tokens()
 * 2. Verifica la sintaxis de las redirecciones con check_redirection_syntax():
 *    - Operadores de redirección sin argumento (como "ls >")
 *    - Operadores seguidos de argumento vacío
 *    - Si encuentra un error, termina con mensaje y código de salida apropiado
 * 3. Itera sobre todos los tokens del comando manteniendo el orden de 
 procesamiento:
 *    - Mantiene el orden exacto de las redirecciones tal como aparecen en 
 el comando
 *    - Esto es importante porque cada redirección puede sobrescribir 
 descriptores anteriores
 * 4. Para cada token, usa process_redirection_token(cmds, i)
  que determina el tipo:
 *    - Tipo 1: heredoc ("<<") - maneja entrada interactiva hasta delimitador
 *    - Tipo 2: redirección de salida (">") - trunca y escribe al archivo
 *    - Tipo 3: redirección de salida append (">>") - añade al final del archivo
 *    - Tipo 4: redirección de entrada ("<") - lee desde archivo
 *    - Tipo 0: no es una redirección
 * 5. Cada función de redirección específica:
 *    - Abre/crea archivos con permisos y opciones adecuadas
 *    - Redirige los descriptores de archivo estándar (STDIN/STDOUT)
 *    - Libera la memoria de los tokens procesados para evitar memory leaks
 * 6. Usa free_extra_token() para liberar argumentos extra después de 
 redirecciones
 * 
 * Gestión de memoria:
 * - Los tokens de redirección y sus argumentos se liberan en cada función 
 específica
 * - Los tokens extra después de redirecciones se liberan para evitar 
 memory leaks
 * - Se utiliza una bandera (seen_redirection) para controlar qué tokens liberar
 * - Permite comandos complejos como "cmd < input > output >> append extra_args"
 */
void	handle_redirections(char **cmds)
{
	int	i;
	int	total_count;
	int	seen_redirection;
	int	redir_type;

	seen_redirection = 0;
	total_count = count_total_tokens(cmds);
	check_redirection_syntax(cmds);
	i = -1;
	while (++i < total_count)
	{
		redir_type = process_redirection_token(cmds, i);
		if (redir_type > 0)
		{
			seen_redirection = 1;
			if (redir_type == 1)
				i++;
		}
		else
			free_extra_token(cmds, i, seen_redirection);
	}
}
