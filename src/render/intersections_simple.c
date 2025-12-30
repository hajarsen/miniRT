/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_simple.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhilane <hrhilane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 03:13:19 by hrhilane          #+#    #+#             */
/*   Updated: 2025/12/30 03:13:39 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	hit_sphere(t_sphere *sp, t_ray ray, t_range range, t_hit_record *rec)
{
	t_vector	oc;
	t_eq		eq;

	oc = vec_sub(ray.origin, sp->center);
	eq.a = vec_dot(ray.direction, ray.direction);
	eq.half_b = vec_dot(oc, ray.direction);
	eq.c = vec_dot(oc, oc) - (sp->diameter * 0.5) * (sp->diameter * 0.5);
	eq.discriminant = eq.half_b * eq.half_b - eq.a * eq.c;
	if (eq.discriminant < 0)
		return (0);
	eq.sqrtd = sqrt(eq.discriminant);
	rec->t = (-eq.half_b - eq.sqrtd) / eq.a;
	if (rec->t < range.t_min || rec->t > range.t_max)
	{
		rec->t = (-eq.half_b + eq.sqrtd) / eq.a;
		if (rec->t < range.t_min || rec->t > range.t_max)
			return (0);
	}
	rec->p = ray_at(ray, rec->t);
	set_face_normal(rec, ray, vect_div(vec_sub(rec->p, sp->center),
			sp->diameter * 0.5));
	rec->color = sp->color;
	return (1);
}

int	hit_plane(t_plane *plane, t_ray ray, t_range range, t_hit_record *rec)
{
	double		denom;
	t_vector	p0;

	denom = vec_dot(ray.direction, plane->normal);
	if (fabs(denom) < 1e-8)
		return (0);
	p0 = vec_sub(plane->point, ray.origin);
	rec->t = vec_dot(p0, plane->normal) / denom;
	if (rec->t < range.t_min || rec->t > range.t_max)
		return (0);
	rec->p = ray_at(ray, rec->t);
	rec->color = plane->color;
	set_face_normal(rec, ray, plane->normal);
	return (1);
}
