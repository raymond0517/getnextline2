/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhsu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:52:49 by rhsu              #+#    #+#             */
/*   Updated: 2023/10/25 17:13:52 by rhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	42
# else
#  if (BUFFER_SIZE <= 0)
#   undef BUFFER_SIZE
#   define BUFFER_SIZE 42
#  endif
# endif
# define MAX_FD			1048576
# define MALLOC_SIZE	130049

char		*get_next_line(int fd);
int			read_fd(char **b, int fd);
long int	findchr(char *s, char c, long len);
void		clear_buff(char **b);
long int	ft_strlen(char *b);
#endif
