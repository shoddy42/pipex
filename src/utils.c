/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/15 18:18:54 by wkonings      #+#    #+#                 */
/*   Updated: 2022/11/21 14:38:34 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	pipex_error(char *error_message, int mode, bool terminate)
{
	write (STDERR_FILENO, "pipex: ", 8);
	if (mode == WR_ERROR)
		write (STDERR_FILENO, error_message, ft_strlen(error_message));
	if (mode == P_ERROR)
		perror (error_message);
	if (terminate == true)
		exit(1);
}

char	*pipex_pathjoin(char const *path, char const *cmd)
{
	char	*ret;
	size_t	i;
	size_t	j;

	if (!path || !cmd)
		return (NULL);
	ret = malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(cmd) + 2));
	if (!ret)
		return (NULL);
	i = -1;
	j = -1;
	while (path[++i])
		ret[i] = path[i];
	while (cmd[++j] && cmd[j] != ' ')
		ret[i + j + 1] = cmd[j];
	ret[i] = '/';
	ret[i + j + 1] = '\0';
	return (ret);
}

void	pipex_open(int ac, char **av, t_ppx *pipex)
{
	if (ft_strncmp("here_doc", av[1], 8) == 0)
	{
		pipex->outfile_fd = open(av[ac - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
		if (pipex->outfile_fd < 0)
		{
			perror(av[ac - 1]);
			pipex->cancel_final = true;
		}
		pipex_heredoc(av[2], pipex);
	}
	else
	{
		pipex->infile_fd = open(av[1], O_RDONLY, 0644);
		if (pipex->infile_fd < 0)
		{
			perror(av[1]);
			pipex->cancel_first = true;
		}
		pipex->outfile_fd = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (pipex->outfile_fd < 0)
		{
			perror(av[ac - 1]);
			pipex->cancel_final = true;
		}
	}
}

void	split_path(char **envp, t_ppx *pipex)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			pipex->path = ft_split(envp[i] + 6, ':');
}
