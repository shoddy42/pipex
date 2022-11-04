/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_funcs1.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/02 21:22:56 by wkonings      #+#    #+#                 */
/*   Updated: 2022/11/04 19:18:36 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	check;
	unsigned char	*d;
	unsigned char	*s;

	check = (unsigned char)c;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (n)
	{
		n--;
		*d = *s;
		if (*d == check)
			return (d + 1);
		d++;
		s++;
	}
	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dst, char const *src, size_t dstsize)
{
	char	*tmp;

	if (!dst && !src)
		return (0);
	tmp = ft_memccpy(dst, src, '\0', dstsize);
	if (!tmp && dstsize)
		dst[dstsize - 1] = '\0';
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	i;

	i = 0;
	s2 = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!s2)
		return (NULL);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (!s || start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) + start)
		len = ft_strlen(s) - start;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}
