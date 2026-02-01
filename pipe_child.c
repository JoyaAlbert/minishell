/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joya <joya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:00:00 by copito            #+#    #+#             */
/*   Updated: 2025/07/23 00:06:31 by joya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
}
