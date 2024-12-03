#include "../minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strnstr(char *hay, char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[0] == '\0')
		return ((char *)hay);
	else if (len == 0)
		return (NULL);
	while (hay[i] != '\0' && (i < len))
	{
		j = 0;
		while (hay[i + j] == needle[j] && hay[i + j] != '\0'
			&& i + j < len)
			j++;
		if (needle[j] == '\0')
			return ((char *)hay + i);
		i++;
	}
	return (NULL);
}

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

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char			*total;
	unsigned int	i;
	unsigned int	size;
	unsigned int	size1;

	i = 0;
	size = ft_strlen(s1);
	size1 = ft_strlen(s2);
	total = (char *)malloc((size * sizeof(char)) + (size1 * sizeof(char)) + 1);
	if (total == NULL)
		return (NULL);
	while (i < size)
	{
		total[i] = s1[i];
		i++;
	}
	size = 0;
	while (size < size1)
	{
		total[i] = s2[size];
		i++;
		size++;
	}
	total[i] = '\0';
	return (total);
}
