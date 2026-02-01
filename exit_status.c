/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copito <copito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:11:47 by copito            #+#    #+#             */
/*   Updated: 2025/07/09 20:38:03 by copito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// EXIT STATUS FUNCTIONS
void	set_exit_status(int status)
{
	g_exit_status = status;
}

int	get_exit_status(void)
{
	return (g_exit_status);
}

// Helper function to count the new string length after $? expansion
int	count_expanded_length(char *str, char *exit_str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			j += ft_strlen(exit_str);
			i += 2;
		}
		else
		{
			j++;
			i++;
		}
	}
	return (j);
}

// Helper function to replace $? with exit status value
void	replace_exit_status_in_string(char *str, char *result, char *exit_str)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			temp = exit_str;
			while (*temp)
				result[j++] = *temp++;
			i += 2;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
}

char	*expand_exit_status(char *str)
{
	char	*result;
	char	*exit_str;
	int		new_length;

	if (!str)
		return (NULL);
	exit_str = ft_itoa(g_exit_status);
	if (!exit_str)
		return (NULL);
	new_length = count_expanded_length(str, exit_str);
	result = malloc(new_length + 1);
	if (!result)
	{
		free(exit_str);
		return (NULL);
	}
	replace_exit_status_in_string(str, result, exit_str);
	free(exit_str);
	return (result);
}
