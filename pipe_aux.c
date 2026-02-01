/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joya <joya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:12:47 by copito            #+#    #+#             */
/*   Updated: 2025/07/22 21:28:44 by joya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Verifica si alguno de los comandos contiene redirección heredoc (<<)
 * Recorre los tokens del comando buscando el operador heredoc
 * Cuenta el número de redirecciones heredoc presentes
 * Retorna el número de redirecciones heredoc encontradas
 */
int	check_here(char **cmd_parts)
{
	int	i;
	int	check;

	check = 0;
	i = -1;
	while (cmd_parts[++i] != NULL)
	{
		if (ft_strncmp(cmd_parts[i], "<<", 3) == 0)
			check++;
	}
	return (check);
}

/*
 * Maneja el proceso padre en una tubería
 * Espera a que el hijo termine si hay heredocs presentes
 * Libera la memoria de los tokens del comando
 * Cierra los descriptores de archivo no necesarios
 * Actualiza el descriptor de entrada para el siguiente comando
 */
int	parent(int fd[2], char **cmd_parts, int prev_fd, int check)
{
	if (check != 0)
		waitpid(0, NULL, 0);
	matrixfree(cmd_parts);
	close(fd[1]);
	if (prev_fd != 0)
		close(prev_fd);
	prev_fd = fd[0];
	return (prev_fd);
}

char	**check_fork_cmd(char **cmds, pid_t pid)
{
	fork_fail(cmds, pid);
	return (ft_split(*cmds, ' '));
}

int	pipe_process(char **cmds, t_pipe_params *params, int prev_fd)
{
	pid_t		pid;
	int			fd[2];
	char		**cmd_parts;
	int			check;
	t_pipe_data	data;

	pipe(fd);
	pid = fork();
	cmd_parts = check_fork_cmd(cmds, pid);
	check = check_here(cmd_parts);
	if (pid == 0)
	{
		data.cmd_parts = cmd_parts;
		data.check = check;
		data.prev_fd = prev_fd;
		data.fd[0] = fd[0];
		data.fd[1] = fd[1];
		data.envp = params->envp;
		data.dir = params->dir;
		data.envp_d = params->envp_d;
		handle_child_process(&data);
	}
	else
		prev_fd = parent(fd, cmd_parts, prev_fd, check);
	return (prev_fd);
}
/**

void	setup_child_redirections(t_pipe_data *data)
{
	if (data->check > 0)
		handle_redirections(data->cmd_parts);
	if (data->prev_fd != 0)
	{
		dup2(data->prev_fd, 0);
		close(data->prev_fd);
	}
	dup2(data->fd[1], 1);
	close(data->fd[0]);
	close(data->fd[1]);
}


void	execute_child_command(t_pipe_data *data)
{
	t_exec_ctx	ctx;

	if (data->check == 0)
		do_redirections(data->cmd_parts, data->envp, data->dir, data->envp_d);
	else
	{
		if (data->cmd_parts[0])
		{
			ctx.envp = data->envp;
			ctx.dir = data->dir;
			ctx.envp_d = data->envp_d;
			builtin_exec(data->cmd_parts[0], data->cmd_parts, &ctx);
			parse_path(ft_strndup(data->cmd_parts[0],
					ft_strlen(data->cmd_parts[0]) + 1),
				data->cmd_parts, data->envp);
		}
		matrixfree(data->cmd_parts);
		exit(0);
	}
}


void	handle_child_process(t_pipe_data *data)
{
	setup_child_redirections(data);
	execute_child_command(data);
}*/