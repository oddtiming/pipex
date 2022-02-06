/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 13:10:14 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/06 01:14:26 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif
#define FREE -3

/*	Reads to the static char *remain until a nl is found, or until
 *	the EOF has been reached. If read() reaches EOF (returns nbyte < BUFF_SIZE)
 *	or attempts an invalid read () (returns -1) and remain[fd] doesn't
 *	end with \n, get_line_len() returns 0.
 */
static long	get_line_len(char **remain, int fd)
{
	long	read_status;
	char	*read_buf;

	while (!(*remain) || !strlen_c(*remain, '\n'))
	{
		read_buf = malloc(BUFFER_SIZE + 1);
		read_status = read(fd, read_buf, BUFFER_SIZE);
		if (read_status <= 0)
		{
			free (read_buf);
			return (read_status);
		}
		read_buf[read_status] = 0;
		*remain = ft_strjoin_free(*remain, read_buf);
		free(read_buf);
	}
	return (strlen_c(*remain, '\n'));
}

/*	get_next_line is used to return the string content of a single input 
 *	stream (fd) line by line. Every function call returns a line including
 *	the \n character.
 *	It uses static char *remain to store the excess buffer from the read()
 *	function (i.e. everything after \n). The second if checks if remain[fd] is
 *	empty. The last if is merely to ensure that free() happens as soon as the
 *	last line is hit. (could be removed to save 7 lines of code)
 */
char	*get_next_line(int fd)
{
	char		*current_line;
	long		line_len;
	static char	*remain = NULL;

	line_len = get_line_len(&remain, fd);
	if (line_len <= 0)
		line_len = strlen_c(remain, 0);
	if (!line_len)
	{
		free (remain);
		remain = (NULL);
		return (NULL);
	}
	current_line = malloc(line_len + 1);
	ft_strncpy(current_line, remain, line_len);
	if (!strlen_c(remain, '\n') || fd == FREE)
	{
		free (remain);
		remain = (NULL);
	}
	else
		ft_strncpy(remain, &remain[line_len], \
			strlen_c(remain, 0) - line_len + 1);
	return (current_line);
}
