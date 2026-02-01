/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copito <copito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:12:35 by copito            #+#    #+#             */
/*   Updated: 2025/07/23 22:18:02 by copito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils/utils.h"

char	**validate_and_prepare_cmd(char *cmd, char **envp)
{
	char	**cmds;
	int		path_exists;

	if (check_pipe(cmd) == -1 || parse_redirections(cmd) == -1)
	{
		printf("No accepted ||, >>>, <<< or no args after |\n");
		return (NULL);
	}
	cmds = split_outside_quotes(cmd, ' ');
	path_exists = (lookinenv(envp, "PATH=/") != NULL);
	if (!path_exists && check_builtins(cmd) != 0 && cmds[0][0] != '/')
	{
		printf("Error: No PATH variable.");
		printf(" Only builtins or absolute paths allowed.\n");
		matrixfree(cmds);
		return (NULL);
	}
	return (cmds);
}

void	parser(t_dir_info *dir, char **envp, char *cmd, t_envp *envp_d)
{
	char	**cmds;

	cmds = validate_and_prepare_cmd(cmd, envp);
	if (!cmds)
		return ;
	if (check_builtins(cmd) == 1 && check_pipe(cmd) == 1
		&& parse_redirections(cmd) != 0 && !is_variable_assignment(cmd))
		to_exec(cmd, envp);
	if (check_pipe(cmd) == 0)
		pipeline(cmd, envp, dir, envp_d);
	else if (parse_redirections(cmd) == 0)
		execute_with_redirections(cmd, envp, dir, envp_d);
	else if (check_builtins(cmd) == 0 && check_pipe(cmd) == 1)
		sendto_builtin(cmds, dir, envp, envp_d);
	matrixfree(cmds);
}
