/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 03:12:39 by hrhilane          #+#    #+#             */
/*   Updated: 2025/12/30 03:42:59 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_face_normal(t_hit_record *rec, t_ray ray, t_vector outward_normal)
{
	rec->front_face = (vec_dot(ray.direction, outward_normal) < 0);
	if (rec->front_face)
		rec->normal = outward_normal;
	else
		rec->normal = vec_mult(outward_normal, -1.0);
}

int	is_within_height(t_cylinder *cy, t_point3 p)
{
	t_vector	cp;
	double		projection;

	cp = vec_sub(p, cy->center);
	projection = vec_dot(cp, cy->axis);
	return (projection >= 0 && projection <= cy->height);
}

t_vector	get_body_normal(t_cylinder *cy, t_point3 p)
{
	t_vector	cp;
	t_vector	axis_component;
	t_vector	radial;

	cp = vec_sub(p, cy->center);
	axis_component = vec_mult(cy->axis, vec_dot(cp, cy->axis));
	radial = vec_sub(cp, axis_component);
	return (vec_unit(radial));
}

int	is_in_circle(t_point3 p, t_point3 cap_center, double radius)
{
	t_vector	to_p;
	double		dist_sq;

	to_p = vec_sub(p, cap_center);
	dist_sq = vec_dot(to_p, to_p);
	return (dist_sq <= radius * radius);
}
