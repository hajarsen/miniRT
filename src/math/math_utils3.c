/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:40:45 by hsennane          #+#    #+#             */
/*   Updated: 2026/01/02 04:24:25 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	vect_div(t_vector v, double t)
{
	t_vector	res;

	if (t == 0)
		return (v);
	res.x = v.x / t;
	res.y = v.y / t;
	res.z = v.z / t;
	return (res);
}

t_point3	ray_at(t_ray ray, double t)
{
	return (vec_add(ray.origin, vec_mult(ray.direction, t)));
}

t_vector	vec_scale(t_vector v, double s)
{
	return (vect_scal(v, s));
}

bool	in_interval(double value, double min_val, double max_val)
{
	return (value >= min_val && value <= max_val);
}

bool	is_normalized(t_vector v)
{
	double	len;

	len = vector_length(v);
	return (fabs(len - 1.0) < 1e-3);
}
