/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/08 11:59:59 by wkonings      #+#    #+#                 */
/*   Updated: 2022/11/04 19:19:49 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line_bonus.h"

int	handle_final(char **buff, char **line, int fd, int ret)
{
	int	i;

	i = 0;
	if (buff[fd])
	{
		*line = ft_strdup_opt(buff[fd], 1, 0, 0);
		free(buff[fd]);
		buff[fd] = NULL;
	}
	if (!line)
		return (-1);
	return (ret);
}

int	handle_error(char **buff, int fd)
{
	if (buff[fd])
	{
		free(buff[fd]);
		buff[fd] = NULL;
	}
	return (-1);
}

int	handle_newline(char **buff, char **line, int fd)
{
	char	*copy;

	copy = ft_strdup_opt(buff[fd], 1, 0, 0);
	*line = ft_strdup_opt(buff[fd], 0, 0, 0);
	if (*line && copy)
	{
		free(buff[fd]);
		buff[fd] = ft_strdup_opt(copy, 2, 0, 0);
		free(copy);
		if (!buff)
			return (-1);
		return (1);
	}
	if (copy)
		free(copy);
	if (buff[fd])
	{
		free(buff[fd]);
		buff[fd] = NULL;
	}
	return (-1);
}

int	get_next_line(int fd, char **line)
{
	int			ret;
	static char	*buff[10240];
	char		content[BUFFER_SIZE + 1];

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!buff[fd])
		buff[fd] = ft_strdup_opt("", 1, 0, 0);
	ret = 42;
	while (ret > 0 && buff[fd])
	{
		if (ft_chrlen(buff[fd], '\n') != -1)
		{
			ret = read(fd, content, BUFFER_SIZE);
			if (ret == -1)
				return (handle_error(buff, fd));
			content[ret] = '\0';
			buff[fd] = gnl_strjoin(buff[fd], content, 0, 0);
			if (!buff[fd])
				return (handle_error(buff, fd));
		}
		else
			return (handle_newline(buff, line, fd));
	}
	return (handle_final(buff, line, fd, ret));
}
