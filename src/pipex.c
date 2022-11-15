/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 21:08:54 by wkonings      #+#    #+#                 */
/*   Updated: 2022/11/15 16:39:56 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static bool	handle_path(char **args, char **envp)
{
	int		i;

	if (!args)
		pipex_error("Splitting of arguments failed.", P_ERROR, true);
	if (access(args[0], X_OK) == 0)
		if (execve(args[0], args, envp) == -1)
			exit (1);
	i = -1;
	while (args[0][++i])
		if (args[0][i] == '/')
			return (true);
	return (false);
}

static int	pipexec(char *cmd, char **envp, t_ppx *pipex)
{
	char	**args;
	char	*path;
	int		i;

	args = ft_split(cmd, ' ');
	if (handle_path(args, envp))
		pipex_error(args[0], P_ERROR, true);
	i = -1;
	while (pipex->path && pipex->path[++i])
	{
		path = pipex_pathjoin(pipex->path[i], cmd);
		if (access(path, X_OK) == 0)
			if (execve(path, args, envp) == -1)
				exit (1);
		free(path);
	}
	path = pipex_pathjoin(".", cmd);
	if (access(path, X_OK) == 0)
		if (execve(path, args, envp) == -1)
			exit (1);
	free(path);
	write(2, "pipex: ", 7);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	exit(127);
}

static void	forking(char *cmd, t_ppx *pipex, int command_num)
{
	int	tunnel[2];

	if (pipe(tunnel) < 0)
		pipex_error("Creating pipe failed.\n", P_ERROR, true);
	pipex->fd_in = get_fd_in(pipex->old_read, pipex, command_num);
	pipex->fd_out = get_fd_out(tunnel[WRITE], pipex, command_num);
	pipex->pid = fork();
	if (pipex->pid < 0)
		pipex_error("Creation of child process failed.\n", P_ERROR, true);
	if (pipex->pid == CHILD)
	{
		close(tunnel[READ]);
		dup2(pipex->fd_out, STDOUT_FILENO);
		dup2(pipex->fd_in, STDIN_FILENO);
		if (command_num == 0 && pipex->cancel_first)
			exit(1);
		if (command_num + 1 == pipex->cmd_count && pipex->cancel_final)
			exit(1);
		pipexec(cmd, pipex->envp, pipex);
	}
	close(tunnel[WRITE]);
	if (pipex->old_read > 2)
		close(pipex->old_read);
	pipex->old_read = tunnel[READ];
}

static void	init_pipex(t_ppx *pipex, int ac, char **av, char **envp)
{
	if (ac < 5 || (ac < 6 && ft_strcmp("here_doc", av[1]) == 0))
		pipex_error("Not enough arguments.\n", WR_ERROR, true);
	ft_bzero(pipex, sizeof(t_ppx));
	pipex->cmd_count = ac - 3;
	pipex->envp = envp;
	split_path(envp, pipex);
}

int	main(int ac, char **av, char **envp)
{
	int		i;
	t_ppx	pipex;

	init_pipex(&pipex, ac, av, envp);
	pipex_open(ac, av, &pipex);
	i = 0;
	if (pipex.here_doc == 1)
		i++;
	while (i++ < pipex.cmd_count)
		forking(av[i + 1], &pipex, i - 1);
	while (--i > 0)
		waitpid((pid_t)0, NULL, 0);
	exit (EXIT_SUCCESS);
}
