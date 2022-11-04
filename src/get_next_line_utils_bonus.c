/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils_bonus.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/08 11:59:50 by wkonings      #+#    #+#                 */
/*   Updated: 2022/11/04 19:19:55 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line_bonus.h"

int	ft_chrlen(const char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c && c != '\0')
			return (-1);
		i++;
	}
	return (i);
}

char	*gnl_strjoin(char *s1, char const *s2, size_t i, size_t j)
{
	char	*str;

	if (!s1)
		return (NULL);
	str = malloc(sizeof(char) * (ft_chrlen(s1, 0) + ft_chrlen(s2, 0) + 1));
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	free(s1);
	return (str);
}

/*
**	opt 2 skips the up to and then past the first newline then goes to opt 1
**	opt 1 copies the whole string (regular strdup)
**	opt 0 stops when it reaches a newline (used to write into **line)
*/

char	*ft_strdup_opt(const char *str, int opt, size_t i, size_t j)
{
	char	*dup;

	dup = malloc(sizeof(char) * (ft_chrlen(str, 0) + 1));
	if (!dup)
		return (NULL);
	if (opt == 2)
	{
		while (str[j] && str[j] != '\n')
			j++;
		j++;
		opt = 1;
	}
	while (str[i + j] && opt == 1)
	{
		dup[i] = str[i + j];
		i++;
	}
	while (str[i] && str[i] != '\n' && opt == 0)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
