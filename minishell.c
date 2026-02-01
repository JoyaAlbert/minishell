/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copito <copito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:12:22 by copito            #+#    #+#             */
/*   Updated: 2025/07/09 20:50:34 by copito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Global variable for exit status ($?) (da aviso, que no error, de norminette)
int	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_envp	*envp_d;

	(void)argv;
	if (argc != 1)
		msg("\033[31mNo arguments accepted");
	if (envp == NULL)
		msg("\033[31mNo Envp variable");
	if (lookinenv(envp, "PATH=/") == NULL)
		msg("\033[31mNo Path variable on Envp");
	if (lookinenv(envp, "PWD=/") == NULL)
		msg("\033[31mNo PWD variable on Envp");
	envp_d = malloc(sizeof(t_envp));
	if (envp_d == NULL)
		msg("\033[31mError allocating memory");
	envp_d->env_dup = dupmatrix(envp);
	envp_d->vars = NULL;
	update_shlvl(envp_d->env_dup);
	to_exec("clear", envp);
	while (prompt(envp_d) == 0)
		;
	matrixfree(envp_d->env_dup);
	if (envp_d->vars != NULL)
		matrixfree(envp_d->vars);
	free(envp_d);
}
