/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:40:30 by hsennane          #+#    #+#             */
/*   Updated: 2026/01/05 16:26:04 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	reflect_vect(t_vector v, t_vector n)
{
	t_vector	res;

	res = vec_sub(v, vec_scal(n, 2 * vec_dot(v, n)));
	return (res);
}

t_vector	refract_vect(t_vector v, t_vector n, float eta)
{
	float		cos_inc;
	float		cos_refr;
	t_vector	res;

	cos_inc = vec_dot(v, n);
	cos_refr = sqrt(1 - ft_power(eta, 2) * (1 - ft_power(cos_inc, 2)));
	res = vec_add(vec_scal(v, eta), vec_scal(n, (eta * cos_inc - cos_refr)));
	return (vec_unit(res));
}

t_vector	vec_invert(t_vector v)
{
	t_vector	res;

	res.x = -v.x;
	res.y = -v.y;
	res.z = -v.z;
	return (res);
}
