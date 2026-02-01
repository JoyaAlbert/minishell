/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copito <copito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:12:10 by copito            #+#    #+#             */
/*   Updated: 2025/07/09 20:46:53 by copito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Lee una línea y verifica si es el delimitador de heredoc
 * Retorna 1 si es el delimitador, 0 si no lo es, -1 si hay error
 */
int	read_and_check_delimiter(int pipe_fd, char *delimiter)
{
	char	*line;
	int		is_delimiter;

	line = readline("> ");
	if (!line)
		return (-1);
	is_delimiter = (ft_strlen(line) == ft_strlen(delimiter)
			&& ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0);
	if (!is_delimiter)
	{
		write(pipe_fd, line, ft_strlen(line));
		write(pipe_fd, "\n", 1);
	}
	free(line);
	return (is_delimiter);
}

/*
 * Configura la redirección de entrada desde el pipe de heredoc
 */
void	setup_heredoc_input(int pipe_fd[2])
{
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		msg("Error while duping file descriptor for heredoc");
	close(pipe_fd[0]);
}
