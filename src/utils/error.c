/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:50:50 by hsennane          #+#    #+#             */
/*   Updated: 2026/01/06 03:36:47 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_error(const char *msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (msg)
		ft_putstr_fd((char *)msg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (0);
}

int	handle_parse_error(t_scene *scene, char *line, int fd)
{
	if (line)
		free(line);
	cleanup_gnl(fd);
	close(fd);
	clean_scene(scene);
	return (0);
}
