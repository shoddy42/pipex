/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/08 11:59:59 by wkonings      #+#    #+#                 */
/*   Updated: 2022/11/04 19:19:17 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

int				get_next_line(int fd, char **line);
int				ft_chrlen(const char *str, char c);
char			*gnl_strjoin(char *s1, char const *s2, size_t i, size_t j);
char			*ft_strdup_opt(const char *str, int opt, size_t i, size_t j);
char			*clean_buff(char *buff);

#endif
