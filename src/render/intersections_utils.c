/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 03:12:39 by hrhilane          #+#    #+#             */
/*   Updated: 2026/01/02 20:45:16 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_face_normal(t_hit_record *rec, t_ray ray, t_vector outward_normal)
{
	rec->front_face = (vec_dot(ray.direction, outward_normal) < 0);
	if (rec->front_face)
		rec->normal = outward_normal;
	else
		rec->normal = vec_scal(outward_normal, -1.0);
}

int	is_within_height(t_cylinder *cy, t_point3 p)
{
	t_vector	cp;
	double		projection;
	double		half_height;

	cp = vec_sub(p, cy->center);
	projection = vec_dot(cp, cy->axis);
	half_height = cy->height * 0.5;
	return (projection >= -half_height && projection <= half_height);
}

t_vector	get_body_normal(t_cylinder *cy, t_point3 p)
{
	t_vector	cp;
	t_vector	axis_component;
	t_vector	radial;

	cp = vec_sub(p, cy->center);
	axis_component = vec_scal(cy->axis, vec_dot(cp, cy->axis));
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

int	solve_cy(t_vector oc, t_ray ray, t_cylinder *cy, double *t)
{
	t_vector	d_perp;
	t_vector	oc_perp;
	t_eq		eq;

	d_perp = vec_sub(ray.direction, vec_scal(cy->axis, vec_dot(ray.direction,
					cy->axis)));
	oc_perp = vec_sub(oc, vec_scal(cy->axis, vec_dot(oc, cy->axis)));
	eq.a = vec_dot(d_perp, d_perp);
	eq.b = 2.0 * vec_dot(oc_perp, d_perp);
	eq.c = vec_dot(oc_perp, oc_perp) - pow(cy->diameter / 2.0, 2);
	eq.discriminant = eq.b * eq.b - 4 * eq.a * eq.c;
	if (eq.discriminant < 0)
		return (0);
	eq.sqrtd = sqrt(eq.discriminant);
	t[0] = (-eq.b - eq.sqrtd) / (2.0 * eq.a);
	t[1] = (-eq.b + eq.sqrtd) / (2.0 * eq.a);
	return (1);
}
