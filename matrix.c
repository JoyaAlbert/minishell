/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copito <copito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:12:16 by copito            #+#    #+#             */
/*   Updated: 2025/07/09 20:49:21 by copito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_matrix(char **matrix)//no se usa
{
	int	i;

	if (matrix == NULL)
		return ((void)0);
	i = 0;
	while (matrix[i] != NULL)
	{
		printf("%s\n", matrix[i]);
		i++;
	}
}

void	free_arraymatrix(char *array, char **matrix)
{
	free(array);
	matrixfree(matrix);
}

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

int	sizematrix(char **matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL)
		return (0);
	while (matrix[i] != NULL)
		i++;
	return (i + 1);
}

char	**dupmatrix(char **og)
{
	char	**dest;
	int		count;
	int		i;

	count = -1;
	i = -1;
	while (og[++count] != NULL)
		;
	dest = malloc((count + 1) * sizeof(char *));
	if (!dest)
	{
		msg("Error allocating memory");
		return (NULL);
	}
	while (++i < count)
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
