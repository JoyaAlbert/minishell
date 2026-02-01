/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_outside_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joya <joya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:29:22 by joya              #+#    #+#             */
/*   Updated: 2025/07/24 12:19:24 by joya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>

int	quotes(const char *s, int i, char sep)
{
	int	in_single;
	int	in_double;

	in_double = 0;
	in_single = 0;
	while (s[i])
	{
		if (s[i] == '"' && !in_single)
			in_double = !in_double;
		else if (s[i] == '\'' && !in_double)
			in_single = !in_single;
		if (s[i] == sep && !in_single && !in_double)
			break ;
		i++;
	}
	return (i);
}

static int	countwords_quotes(const char *s, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == sep)
			i++;
		if (!s[i])
			break ;
		count++;
		i = quotes(s, i, sep);
	}
	return (count);
}

static char	*strndup_quotes(const char *s, int n)
{
	char	*out;
	int		i;

	i = 0;
	out = malloc(n + 1);
	if (!out)
		return (NULL);
	while (i < n)
	{
		out[i] = s[i];
		i++;
	}
	out[n] = '\0';
	return (out);
}

int	count_quotes(const char *s)
{
	int	i;
	int	i_single;
	int	i_double;

	i = 0;
	i_double = 0;
	i_single = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '"')
		{
			if (i_single == 0)
				i_double = !i_double;
		}
		else if (s[i] == '\'')
		{
			if (i_double == 0)
				i_single = !i_single;
		}
		i++;
	}
	if (i_double || i_single)
		return (0);
	return (1);
}

char	**split_outside_quotes(const char *s, char sep)
{
	int		i;
	int		k;
	int		start;
	char	**split;

	if (count_quotes(s) == 0)
	{
		printf("Syntax error around quotes\n");
		return (NULL);
	}
	i = 0;
	k = 0;
	split = malloc((countwords_quotes(s, sep) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	while (s[i])
	{
		while (s[i] == sep)
			i++;
		if (!s[i])
			break ;
		start = i;
		i = quotes(s, i, sep);
		split[k++] = strndup_quotes(s + start, i - start);
	}
	split[k] = NULL;
	return (split);
}
