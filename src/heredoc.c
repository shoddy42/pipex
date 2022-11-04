/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/04 15:49:50 by wkonings      #+#    #+#                 */
/*   Updated: 2022/11/04 19:20:01 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	read_heredoc(char *av, t_ppx *pipex)
{
	char	*limiter;
	char	*line;
	int		gnl;

	limiter = ft_strdup(av);
	close(pipex->hd_tunnel[READ]);
	write(2, "> ", 2);
	gnl = get_next_line(STDIN_FILENO, &line);
	while (gnl)
	{
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			free(limiter);
			exit(0);
		}
		write(pipex->hd_tunnel[WRITE], line, ft_strlen(line));
		write(pipex->hd_tunnel[WRITE], "\n", 1);
		write(2, "> ", 2);
		free(line);
		gnl = get_next_line(STDIN_FILENO, &line);
	}
	free(line);
	free(limiter);
}

int	pipex_heredoc(char *av, t_ppx *pipex)
{
	pid_t	pid;

	pipex->here_doc = 1;
	pipe(pipex->hd_tunnel);
	pid = fork();
	if (pid > 0)
	{
		close(pipex->hd_tunnel[1]);
		dup2(pipex->hd_tunnel[0], STDIN_FILENO);
		close(pipex->hd_tunnel[0]);
		waitpid(pid, NULL, 0);
	}
	else
		read_heredoc(av, pipex);
	return (0);
}
