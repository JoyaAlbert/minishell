/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_ft1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copito <copito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:11:13 by copito            #+#    #+#             */
/*   Updated: 2025/07/31 11:01:36 by copito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (ft_strlen(s1) == 0 && ft_strlen(s2) == 0)
		return (0);
	if (n < 1)
		return (0);
	n--;
	while ((i < n) && (s1[i] == s2[i]) && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (((unsigned char)s1[i] - (unsigned char)s2[i]));
}

int	ft_isalpha(int argument)
{
	if ((argument > 64 && argument < 91) || (argument > 96 && argument < 123))
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int	i;
	int	j;

	j = 0;
	i = (int)n - 1;
	if (!dest && !src)
		return (NULL);
	if (dest > src)
	{
		while (i >= 0)
		{
			*(char *)(dest + i) = *(char *)(src + i);
			i--;
		}
	}
	else
	{
		while (i >= 0)
		{
			*(char *)(dest + j) = *(char *)(src + j);
			i--;
			j++;
		}
	}
	return (dest);
}
