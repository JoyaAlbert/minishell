#include "utils.h"

unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] != '\0' && i < (size - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

static int	check(int nb)
{
	int	i;

	i = 1;
	if (nb == -2147483648)
		return (12);
	if (nb < 0)
		i++;
	while (nb / 10 != 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i + 1);
}

static char	*exceptions(int nb, int i, char *a)
{
	if (nb == 0)
	{
		ft_strlcpy(a, "0", i);
		return (a);
	}
	else if (nb == -2147483648)
	{
		ft_strlcpy(a, "-2147483648", i);
		return (a);
	}
	return (NULL);
}

char	*ft_itoa(int nb)
{
	char	*a;
	int		i;

	i = check(nb);
	a = (char *)malloc(i * sizeof(char));
	if (a == NULL)
		return (NULL);
	if (nb == 0 || nb == -2147483648)
		return (exceptions(nb, i, a));
	if (nb < 0 && nb != -2147483648)
	{
		a[0] = '-';
		nb = nb * (-1);
	}
	a[i - 1] = '\0';
	i--;
	while (nb != 0 && nb != -2147483648 && i != 0)
	{
		a[i - 1] = (nb % 10) + '0';
		nb = nb / 10;
		i--;
	}
	return (a);
}

static int	ft_isspace(int c)
{
	if (c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v'
		|| c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int	i;
	int	n;
	int	sign;

	i = 0;
	n = 0;
	sign = 1;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '-')
	{
		i++;
		sign = -1;
	}
	else if (str[i] == '+')
		i++;
	if (str[i] == '-' || str[i] == '+')
		return (0);
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (sign * n);
}
