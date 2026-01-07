/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 01:36:33 by hajar             #+#    #+#             */
/*   Updated: 2026/01/07 02:12:54 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cleanup_gnl(int fd)
{
	char	*line;

	if (fd >= 0)
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			free(line);
			line = get_next_line(fd);
		}
	}
	get_next_line(-1);
}

int	get_sign(const char **s)
{
	int	sign;

	sign = 1;
	if (**s == '+' || **s == '-')
	{
		if (**s == '-')
			sign = -1;
		(*s)++;
	}
	return (sign);
}
