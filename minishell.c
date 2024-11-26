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
		dest[i] = ft_strndup(og[i], ft_strlen(og[i]+1));  // Duplicate the string
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
	(void)argv;
	if (argc != 1)
		msg("\033[31mNO arguments accepted");
	if (envp == NULL)
		msg("\033[31mNO Envp variable");
	if (getpatharray(envp) == NULL)
		msg("\033[31mNO Path variable on Envp");
	if (lookinenv(envp, "PWD=/") == NULL)
		msg("\033[31mNO PWD variable on Envp");
	while (prompt(envp) == 0)
		;
}
