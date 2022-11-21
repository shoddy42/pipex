/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 20:13:59 by wkonings      #+#    #+#                 */
/*   Updated: 2022/11/21 14:44:43 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/wait.h>
# include "libft/libft.h"

typedef struct s_ppx
{
	char	**path;
	char	**envp;
	pid_t	pid;
	int		fd_in;
	int		fd_out;
	int		old_read;
	int		cmd_count;

	int		hd_tunnel[2];
	int		here_doc;

	int		infile_fd;
	int		outfile_fd;

	int		exit_status;
	bool	cancel_first;
	bool	cancel_final;
}				t_ppx;

typedef enum e_pipe
{
	READ,
	WRITE
}	t_pipe;

typedef enum e_process
{
	CHILD,
	PARENT
}	t_process;

typedef enum e_error
{
	P_ERROR,
	WR_ERROR,
}	t_error;

		/* pipex specific functions */
char	*pipex_pathjoin(char const *path, char const *cmd);
void	pipex_error(char *error_message, int mode, bool terminate);
int		pipex_heredoc(char *av, t_ppx *pipex);
void	pipex_open(int ac, char **av, t_ppx *pipex);
void	split_path(char **env, t_ppx *pipex);
int		get_fd_in(int tunnel, t_ppx *pipex, int command_num);
int		get_fd_out(int tunnel, t_ppx *pipex, int command_num);

int		get_next_line(int fd, char **line);

#endif
