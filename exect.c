/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exect.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copito <copito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:11:42 by copito            #+#    #+#             */
/*   Updated: 2025/07/25 17:56:17 by copito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exec(char *cmd, char **args, t_exec_ctx *ctx)
{
	if (check_builtins(cmd) == 0)
	{
		sendto_builtin(args, ctx->dir, ctx->envp, ctx->envp_d);
		matrixfree(args);
		exit(0);
	}
}

void	execution(char *path, char **cmds, char **envp)
{
	int	check;

	if (path == NULL)
	{
		free_arraymatrix(path, cmds);
		printf("Command not found\n");
		exit(127);
	}
	check = execve(path, cmds, envp);
	if (check == -1)
	{
		free_arraymatrix(path, cmds);
		printf("ERROR while executing\n");
		exit(127);
	}
}

//path contiene el primer cmd pero en parse_path nada más entrar 
//se libera, para que está path entonces?
void	to_exec(char *cmd, char **envp)
{
	char	*path;
	char	**cmds;
	pid_t	pid;
	int		status;

	cmds = ft_split(cmd, ' ');
	pid = fork();
	path = ft_strndup(cmds[0], ft_strlen(cmds[0]) + 1);
	fork_fail(cmds, pid);
	if (pid == 0)
		parse_path(path, cmds, envp);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			set_exit_status(WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			set_exit_status(128 + WTERMSIG(status));
	}
	free_arraymatrix(path, cmds);
}
	/*if (pid == -1)
	{
		matrixfree(cmds);
		msg("fork failed");
	}*/
//entre fok fail  condicionales, ya no necesario 