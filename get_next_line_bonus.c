/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhsu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:07:44 by rhsu              #+#    #+#             */
/*   Updated: 2023/10/24 14:51:56 by rhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	clear_buff(char **b)
{
	if (*b != NULL)
	{
		free (*b);
		*b = NULL;
	}
}

static char	*lastline_or_nothing(char **b)
{
	char	*r;
	long	len;

	if (*b != NULL)
	{
		len = ft_strlen(*b);
		r = malloc(sizeof(char) * (len + 1));
		if (r != NULL)
		{
			r[len] = '\0';
			while (--len >= 0)
				r[len] = (*b)[len];
		}
		free (*b);
		*b = NULL;
	}
	else
		r = NULL;
	return (r);
}

/* after left shift, it could have only '\0' shifted to b[0] with no data */
static void	copyline_and_leftshiftbuff(char *r, char **b, long pos)
{
	long	i;
	long	len;

	i = 0;
	while (i <= pos)
	{
		r[i] = (*b)[i];
		i++;
	}
	r[i] = '\0';
	len = ft_strlen(*b);
	while (i < len)
	{
		(*b)[i - (pos + 1)] = (*b)[i];
		i++;
	}
	(*b)[i - (pos + 1)] = '\0';
	if (ft_strlen(*b) == 0)
	{
		free(*b);
		*b = NULL;
	}
}

/* find c in s, within len, if found, return loc, else -1 */
long	findchr(char *s, char c, long len)
{
	long int	i;

	if (s == NULL)
		return (-1);
	i = 0;
	while (i < len)
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

/* readstatus = -1 error reading file or error malloc, 0 - EOF encountered
	> 0 n bytes being read, so we assume can read some bytes by setting it to 1
	when exiting while loop, it is either EOF, error in reading fd or malloc, or 
	\n is in b[fd].b
	if not error in reading fd or malloc,
		will search for \n in b[fd].b, 
		if found, will return the line include \n and '\0'
			this is done by strlen to \n char + 1 for null terminator
			then malloc, 
			if error, free b[fd].b, set b[fd].b = NULL, b[fd].sz = 0
				return NULL
			else
				copy till \n + NULL terminator to new malloc
				b[fd].b , shift remaining chars to b[fd].b[0], 
				b[fd].sz set to remaining chars + '\0'
		if \n not found,
//fflush(stdout);
			b[fd].b will be returned, b[fd].b = NULL, b[fd].sz = 0
*/
char	*get_next_line(int fd)
{
	static char	*b[MAX_FD];
	int			readstatus;
	long		pos;
	char		*r;

	readstatus = 1;
	while ((readstatus >= 1) && (findchr(b[fd], '\n', ft_strlen(b[fd])) == -1))
		readstatus = read_fd(&(b[fd]), fd);
	if (readstatus < 0)
		return (NULL);
	else
	{
		pos = findchr(b[fd], '\n', ft_strlen(b[fd]));
		if (pos == -1)
			r = lastline_or_nothing(&(b[fd]));
		else
		{
			r = malloc(sizeof(char) * (pos + 2));
			if (r == NULL)
				clear_buff(&(b[fd]));
			else
				copyline_and_leftshiftbuff(r, &(b[fd]), pos);
		}
	}
	return (r);
}
