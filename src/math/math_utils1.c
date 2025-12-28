/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:40:21 by hsennane          #+#    #+#             */
/*   Updated: 2025/12/28 18:40:23 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_vector	create_vect(float x, float y, float z)
{
	t_vector	vect;

	vect.x = x;
	vect.y = y;
	vect.z = z;
	return (vect);
}

t_vector	vect_add(t_vector v, t_vector w)
{
	t_vector	res;

	res.x = v.x + w.x;
	res.y = v.y + w.y;
	res.z = v.z + w.z;
	return (res);
}

t_vector	vect_sub(t_vector v, t_vector w)
{
	t_vector	res;

	res.x = v.x - w.x;
	res.y = v.y - w.y;
	res.z = v.z - w.z;
	return (res);
}

t_vector	cross_product(t_vector v, t_vector w)
{
	t_vector	res;

	res.x = v.y * w.z - v.z * w.y;
	res.y = v.z * w.x - v.x * w.z;
	res.z = v.x * w.y - v.y * w.x;
	return (res);
}

float	dot_product(t_vector v, t_vector w)
{
	float	res;

	res = v.x * w.x + v.y * w.y + v.z * w.z;
	return (res);
}
