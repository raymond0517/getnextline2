/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhsu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:35:31 by rhsu              #+#    #+#             */
/*   Updated: 2023/10/24 14:40:28 by rhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

long int	ft_strlen(char *b)
{
	long	i;

	if (b == NULL)
		return (0);
	i = 0;
	while (b[i])
		i++;
	return (i);
}

/* c is the count of bytes to be copied from r buffer, c should > 0 */
static long int	append_to_existing_buff(char **b, char *r, long c)
{
	long	len;
	long	i;
	long	j;
	char	*nb;

	len = ft_strlen(*b);
	nb = malloc(sizeof(char) * (len + c + 1));
	if (nb == NULL)
		return (-1L);
	i = -1;
	while (++i < (len))
		nb[i] = (*b)[i];
	j = 0;
	while (j < c)
	{
		nb[i + j] = r[j];
		j++;
	}
	nb[i + j] = '\0';
	free (*b);
	*b = nb;
	return (c);
}

/* c is the count of bytes to be copied from r buffer, c should > 0 
   it return c, which is 1 less from malloc size c+1 */
static long int	create_buff(char **b, char *r, long c)
{
	long	i;
	char	*nb;

	nb = malloc(sizeof(char) * (c + 1));
	if (nb == NULL)
		return (-1L);
	i = 0;
	while (i < c)
	{
		nb[i] = r[i];
		i++;
	}
	nb[i] = '\0';
	*b = nb;
	return (c);
}

/* ptr is initialized to 0, and updated only during multiple read,
   so, to determine if any bytes read in to bf[], check ptr > 0
*/
static long	read_fd_and_updt_b(char **b, char *bf, int fd, int malloc_sz)
{
	long	c;
	long	ptr;

	ptr = 0;
	while ((ptr + BUFFER_SIZE) <= malloc_sz)
	{
		c = read(fd, &(bf[ptr]), BUFFER_SIZE);
		if (c > 0)
			ptr += c;
		if ((findchr(&(bf[ptr - c]), '\n', c) != -1) || (c < BUFFER_SIZE))
			break ;
	}
	if (ptr > 0)
	{
		if (ft_strlen(*b) > 0)
			c = (append_to_existing_buff(b, bf, ptr));
		else
			c = (create_buff(b, bf, ptr));
	}
	return (c);
}

/* MALLOC_SIZE determines the min size of malloc , if BUFFER_SIZE smaller
   than MALLOC_SIZE , will malloc using MALLOC_SIZE.                
   if malloc is successful,                                             
      if BUFFER_SIZE is smaller than MALLOC_SIZE
         will repeat read from fd using BUFFER_SIZE
	     until existing ptr to malloc + another read of BUFFER_SIZE will be 
	        >= MALLOC_SIZE, to prevent overflow                           
		    or that last read of fd contains newline char
		    or last read of fd has less than BUFFER_SIZE read indicates EOF
            or last read has fail due to device error, c is -1
		       if none of these 4 conditions will updt ptr with num of bytes
		          read from last read                                       
	   else when BUFFER_SIZE is greater than MALLOC_SIZE, the read is efficient
	      such that no need to repeat read of BUFFER_SIZE, one read is enough
dd
       Now, check that last read has some bytes read in,(not device err)
       will updt ptr with last read num of char
       if b.b already has data
          will append to end of the data
       else
          will create data in b.b
	   in the process will use malloc
       in case of malloc err, will free any b.b existing data
   if malloc not successful, will free any b.b existing data.
*/
int	read_fd(char **b, int fd)
{
	char	*bf;
	int		r;
	int		malloc_sz;

	if (BUFFER_SIZE < MALLOC_SIZE)
		malloc_sz = (MALLOC_SIZE / BUFFER_SIZE) * BUFFER_SIZE;
	else
		malloc_sz = BUFFER_SIZE;
	bf = malloc(sizeof(char) * malloc_sz);
	if (bf != NULL)
	{
		r = read_fd_and_updt_b(b, bf, fd, malloc_sz);
		if (r < 0)
			clear_buff(b);
		free(bf);
		return (r);
	}
	else
	{
		clear_buff(b);
		return (-1);
	}
}
