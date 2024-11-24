#include "minishell.h"

int prompt(char **envp)
{
    char    *cmd;

	cmd = readline(PROMPT);
	if (cmd == NULL)
		return (1);
	to_exec(cmd, envp);
    return (0);
}