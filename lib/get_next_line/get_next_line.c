/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 21:05:24 by hsennane          #+#    #+#             */
/*   Updated: 2026/01/03 03:37:30 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	free_null(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

static char	*join_line(int nl_position, char **buffer)
{
	char	*res;
	char	*tmp;

	if (nl_position <= 0)
	{
		if (!*buffer || **buffer == '\0')
		{
			free_null(buffer);
			return (NULL);
		}
		res = *buffer;
		*buffer = NULL;
		return (res);
	}
	tmp = ft_substr(*buffer, nl_position, ft_strlen(*buffer) - nl_position);
	res = ft_substr(*buffer, 0, nl_position);
	free_null(buffer);
	*buffer = tmp;
	return (res);
}

static char	*read_line(int fd, char **buffer, char *read_return)
{
	ssize_t	bytes_read;
	char	*tmp;
	char	*nl;

	nl = ft_strchr(*buffer, '\n');
	while (nl == NULL)
	{
		bytes_read = read(fd, read_return, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free_null(buffer);
			return (NULL);
		}
		if (bytes_read == 0)
			return (join_line(bytes_read, buffer));
		read_return[bytes_read] = '\0';
		tmp = ft_strjoin(*buffer, read_return);
		free_null(buffer);
		if (!tmp)
			return (NULL);
		*buffer = tmp;
		nl = ft_strchr(*buffer, '\n');
	}
	return (join_line(nl - *buffer + 1, buffer));
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*res;
	char		*read_return;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_return = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!read_return)
		return (NULL);
	if (!buffer)
	{
		buffer = ft_strdup("");
		if (!buffer)
		{
			free(read_return);
			return (NULL);
		}
	}
	res = read_line(fd, &buffer, read_return);
	free(read_return);
	return (res);
}
