/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:51:38 by hsennane          #+#    #+#             */
/*   Updated: 2026/01/01 14:00:21 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	parse_vector(t_vector *vec, char *str, double min_val, double max_val)
{
	char	**components;

	if (!vec || !str)
		return (false);
	components = ft_split(str, ',');
	if (!components)
		return (false);
	if (ft_str_arr_len(components) != 3)
	{
		free_str_array(components);
		return (false);
	}
	if (!parse_float(&vec->x, components[0]) || !in_interval(vec->x, min_val,
			max_val) || !parse_float(&vec->y, components[1])
		|| !in_interval(vec->y, min_val, max_val) || !parse_float(&vec->z,
			components[2]) || !in_interval(vec->z, min_val, max_val))
	{
		free_str_array(components);
		return (false);
	}
	free_str_array(components);
	return (true);
}
