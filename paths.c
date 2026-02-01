/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joya <joya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:12:40 by copito            #+#    #+#             */
/*   Updated: 2025/07/23 00:25:37 by joya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**get_paths_array(char *envp[])
{
	char	*patharr;

	patharr = getpatharray(envp);
	if (!patharr)
		return (NULL);
	return (ft_split(ft_strchr(patharr, '/'), ':'));
}

char	*find_executable_in_paths(char *args, char **paths)
{
	int		i;
	int		fd;
	char	*aux;
	char	*path;

	i = 0;
	if (!paths)
		return (NULL);
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

char	*getpath(char *args, char *envp[])
{
	char	**paths;

	paths = get_paths_array(envp);
	return (find_executable_in_paths(args, paths));
}

void	parse_path(char *path, char **cmds, char **envp)
{
	if (cmds[0][0] != '/' && cmds[0][0] != '.')
	{
		free(path);
		path = getpath(cmds[0], envp);
		execution(path, cmds, envp);
		free(path);
	}
	else
	{
		execution(path, cmds, envp);
		free(path);
	}
}

/*
char	*getpath(char *args, char *envp[])
{
	int		i;
	int		fd;
	char	**paths;
	char	*aux;
	char	*path;
	char	*patharr;

	i = 0;
	patharr = getpatharray(envp);
	if (!patharr)
		return (NULL);
	paths = ft_split(ft_strchr(patharr, '/'), ':');
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
*/
