#include "minishell.h"

void	msg(char *str)
{
    int	i;

	i = -1;
	while(str[++i] != '\0')
		write(2, &str[i], 1);
	write(1, "\n", 1);
	exit(1);
}