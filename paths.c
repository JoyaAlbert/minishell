#include "minishell.h"

void	matrixfree(char	**matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}


char	*getpatharray(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != 0)
	{
		if (ft_strnstr(envp[i], "PATH=/", 6) != NULL)
			return (ft_strnstr(envp[i], "PATH=", 5));
		i++;
	}
	return (NULL);
}

char	*getpath(char *args, char *envp[])
{
	char	**paths;
	int		i;
	char	*aux;
	char	*path;
	int		fd;

	i = 0;
	paths = ft_split(ft_strchr(getpatharray(envp), '/'), ':');
	while (paths[i] != NULL)
	{
		aux = ft_strjoin(paths[i], "/");
		path = ft_strjoin(aux, args);
		free(aux);
		fd = open(path, O_RDONLY);
		if (fd >= 0)
		{
			matrixfree(paths);
			close(fd);
			return (path);
		}
		free(path);
		i++;
	}
	matrixfree(paths);
	return (NULL);
}
