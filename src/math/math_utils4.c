/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:40:53 by hsennane          #+#    #+#             */
/*   Updated: 2026/01/01 13:58:22 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	normalize(t_vector v)
{
	float		length;
	t_vector	res;

	length = vector_length(v);
	if (length == 0)
		return (v);
	res.x = v.x / length;
	res.y = v.y / length;
	res.z = v.z / length;
	return (res);
}

t_vector	vect_scal(t_vector v, float scal)
{
	t_vector	res;

	res.x = v.x * scal;
	res.y = v.y * scal;
	res.z = v.z * scal;
	return (res);
}

double	vector_length(t_vector v)
{
	double	vec_len;

	vec_len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return (vec_len);
}

float	distance(t_vector v, t_vector w)
{
	t_vector	res;

	res.x = w.x - v.x;
	res.y = w.y - v.y;
	res.z = w.z - v.z;
	return (sqrt(res.x * res.x + res.y * res.y + res.z * res.z));
}
