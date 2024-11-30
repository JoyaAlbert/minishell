#include "minishell.h"

char	**dupmatrix(char **og)
{
	char	**dest;
	int		count;
	int		i;

	count = -1;
	i = -1;
	while(og[++count] != NULL)
		;
	dest = malloc((count + 1) * sizeof(char *));
	if (!dest)
		msg("Error allocating memory");
	while(++i < count)
	{
		dest[i] = ft_strndup(og[i], ft_strlen(og[i]) + 1);
        if (!dest[i]) 
		{ 
            matrixfree(dest);
            msg("Error allocating memory");
		}
	}
	dest[i] = NULL;
	return (dest);
}

int	main(int argc, char **argv, char **envp)
{
	t_envp	*envp_d;

	(void)argv;
	if (argc != 1)
		msg("\033[31mNO arguments accepted");
	if (envp == NULL)
		msg("\033[31mNO Envp variable");
	if (getpatharray(envp) == NULL)
		msg("\033[31mNO Path variable on Envp");
	if (lookinenv(envp, "PWD=/") == NULL)
		msg("\033[31mNO PWD variable on Envp");
	envp_d = malloc(sizeof(t_envp));
	if (envp_d == NULL)
		msg("Error allocating memory");
	envp_d->env_dup = dupmatrix(envp);
	to_exec("clear", envp);
	while (prompt(envp_d) == 0)
		;
}
