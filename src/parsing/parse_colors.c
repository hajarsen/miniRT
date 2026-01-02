/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:43:49 by hsennane          #+#    #+#             */
/*   Updated: 2026/01/02 04:01:35 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	ft_parse_rgb(const char *str, double *value)
{
	*value = 0;
	if (!str || *str == '\0')
		return (false);
	while (*str >= '0' && *str <= '9')
	{
		*value = *value * 10 + (*str - '0');
		if (*value > 255)
			return (false);
		str++;
	}
	if (*str != '\0')
		return (false);
	return (true);
}

bool	parse_color(t_color *color, char *str)
{
	char	**components;
	double	r;
	double	g;
	double	b;

	if (!color || !str)
		return (false);
	components = ft_split(str, ',');
	if (!components || ft_str_arr_len(components) != 3)
	{
		if (components)
			free_str_array(components);
		return (false);
	}
	if (!ft_parse_rgb(components[0], &r) || !ft_parse_rgb(components[1], &g)
		|| !ft_parse_rgb(components[2], &b))
	{
		free_str_array(components);
		return (false);
	}
	color->x = r / 255.0;
	color->y = g / 255.0;
	color->z = b / 255.0;
	free_str_array(components);
	return (true);
}
