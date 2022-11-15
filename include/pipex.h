/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 20:13:59 by wkonings      #+#    #+#                 */
/*   Updated: 2022/11/15 13:42:19 by wkonings      ########   odam.nl         */
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

	int		prev_read;
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
void	pipex_error(char *error_message, int mode);
int		pipex_heredoc(char *av, t_ppx *pipex);
void	pipex_open(int ac, char **av, t_ppx *pipex);
int		split_path(char *env[], t_ppx *pipex);
int		get_fd_in(int current_fd, t_ppx *pipex, int mode);

		/* libft funtions */
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(char const *s1, char const *s2);
int		get_next_line(int fd, char **line);

#endif
