/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copito <copito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:11:20 by copito            #+#    #+#             */
/*   Updated: 2025/07/31 11:01:54 by copito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../minishell.h"

char			*ft_strnstr(char *hay, char *needle, size_t len);
int				ft_atoi(char *str);
char			*ft_itoa(int nb);
char			*ft_strndup(char *s1, int n);
char			**ft_split(char *s, char c);
char			**split_outside_quotes(const char *s, char sep);
int				ft_strlen(char *str);
char			*ft_strchr(char *s, int c);
char			*ft_strjoin(char *s1, char *s2);
unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size);
int				ft_strncmp(char *s1, char *s2, unsigned int n);
int				ft_isalpha(int argument);
int				ft_isdigit(int c);
void	        *ft_memmove(void *dest, const void *src, size_t n);

#endif