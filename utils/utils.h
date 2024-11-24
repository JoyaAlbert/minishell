#ifndef UTILS_H
# define UTILS_H

# include "../minishell.h"

char			*ft_strnstr(char *hay, char *needle, size_t len);
int				ft_strncmp(char *s1, char *s2, unsigned int n);
int				ft_strlen(char *str);
char			*ft_strjoin(char *s1, char *s2);
char			**ft_split(char *s, char c);
char			*ft_strchr(char *s, int c);
unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size);

#endif