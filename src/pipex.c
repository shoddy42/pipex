/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 21:08:54 by wkonings      #+#    #+#                 */
/*   Updated: 2022/11/04 19:20:05 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	pipexec(char *cmd, char *envp[], t_ppx *pipex)
{
	char	**args;
	char	*path;
	int		i;

	args = ft_split(cmd, ' ');
	i = 0;
	if (access(args[0], X_OK) == 0)
		execve(args[0], args, envp);
	while (pipex->path[i])
	{
		path = pipex_pathjoin(pipex->path[i], cmd);
		if (access(path, X_OK) == 0)
		{
			execve(path, args, envp);
			exit (1);
		}
		free(path);
		i++;
	}
	write(2, "pipex: ", 7);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	exit(127);
}

int	get_fd_in(int tunnel, t_ppx *pipex, int command_num)
{
	if (command_num == 1 && pipex->here_doc == 1)
		return (pipex->hd_tunnel[READ]);
	if (command_num == 0)
		return (pipex->infile_fd);
	return (tunnel);
}

int	get_fd_out(int tunnel, t_ppx *pipex, int command_num)
{
	if (command_num == pipex->cmd_count - 1)
		return (pipex->outfile_fd);
	return (tunnel);
}

int	forking(char *cmd, t_ppx *pipex, int command_num, int read_tunnel)
{
	int		tunnel[2];
	int		fd_in;
	int		fd_out;

	pipe(tunnel);
	fd_in = get_fd_in(read_tunnel, pipex, command_num);
	fd_out = get_fd_out(tunnel[WRITE], pipex, command_num);
	pipex->pid = fork();
	if (pipex->pid == CHILD)
	{
		close(tunnel[READ]);
		dup2(fd_out, STDOUT_FILENO);
		dup2(fd_in, STDIN_FILENO);
		pipexec(cmd, pipex->envp, pipex);
	}
	else
	{
		close(tunnel[WRITE]);
		if (read_tunnel > 1)
			close(read_tunnel);
	}
	return (tunnel[READ]);
}

int	main(int ac, char **av, char **envp)
{
	int		i;
	t_ppx	pipex;

	if (ac < 5 || (ac < 6 && ft_strcmp("here_doc", av[1]) == 0))
		pipex_error("Not enough arguments.\n", WR_ERROR);
	pipex.cmd_count = ac - 3;
	pipex.envp = envp;
	split_path(envp, &pipex);
	pipex_open(ac, av, &pipex);
	i = 0;
	pipex.old_read = -1;
	if (pipex.here_doc == 1)
		i++;
	while (i++ < pipex.cmd_count)
		pipex.old_read = forking(av[i + 1], &pipex, i - 1, pipex.old_read);
	while (--i > 0)
		waitpid((pid_t)0, NULL, 0);
	exit (0);
}
