/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_cylinder.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhilane <hrhilane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 03:14:50 by hrhilane          #+#    #+#             */
/*   Updated: 2025/12/30 03:15:11 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	solve_cy(t_vector oc, t_ray ray, t_cylinder *cy, double *t)
{
	t_vector	d_perp;
	t_vector	oc_perp;
	t_eq		eq;

	d_perp = vec_sub(ray.direction, vec_mult(cy->axis, vec_dot(ray.direction,
					cy->axis)));
	oc_perp = vec_sub(oc, vec_mult(cy->axis, vec_dot(oc, cy->axis)));
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

static int	hit_body(t_cylinder *cy, t_ray ray, t_range range,
		t_hit_record *rec)
{
	double		t[2];
	t_point3	p;

	if (!solve_cy(vec_sub(ray.origin, cy->center), ray, cy, t))
		return (0);
	if ((t[0] > range.t_min && t[0] < range.t_max) || (t[1] > range.t_min
			&& t[1] < range.t_max))
	{
		if (t[0] > range.t_min && t[0] < range.t_max)
			rec->t = t[0];
		else
			rec->t = t[1];
		p = ray_at(ray, rec->t);
		if (is_within_height(cy, p))
		{
			rec->p = p;
			set_face_normal(rec, ray, get_body_normal(cy, p));
			rec->color = cy->color;
			return (1);
		}
	}
	return (0);
}

static int	check_cap_hit(t_point3 center, t_vector norm, t_cylinder *cy,
		t_hit_record *rec)
{
	double		denom;
	double		t;
	t_vector	p0;
	t_point3	p;

	denom = vec_dot(rec->normal, norm);
	if (fabs(denom) < 1e-8)
		return (0);
	p0 = vec_sub(center, rec->p);
	t = vec_dot(p0, norm) / denom;
	if (t < rec->t || t > rec->color.x)
		return (0);
	p = ray_at((t_ray){rec->p, rec->normal}, t);
	if (!is_in_circle(p, center, cy->diameter / 2.0))
		return (0);
	rec->t = t;
	set_face_normal(rec, (t_ray){rec->p, rec->normal}, norm);
	return (1);
}

static int	hit_caps(t_cylinder *cy, t_ray ray, t_range range,
		t_hit_record *rec)
{
	t_hit_record	ctx;
	int				hit;

	hit = 0;
	ctx.p = ray.origin;
	ctx.normal = ray.direction;
	ctx.t = range.t_min;
	ctx.color.x = range.t_max;
	if (check_cap_hit(cy->center, vec_mult(cy->axis, -1), cy, &ctx))
	{
		hit = 1;
		*rec = ctx;
		rec->p = ray_at(ray, rec->t);
		rec->color = cy->color;
		ctx.color.x = rec->t;
	}
	if (check_cap_hit(vec_add(cy->center, vec_mult(cy->axis, cy->height)),
			cy->axis, cy, &ctx))
	{
		hit = 1;
		*rec = ctx;
		rec->p = ray_at(ray, rec->t);
		rec->color = cy->color;
	}
	return (hit);
}

int	hit_cylinder(t_cylinder *cy, t_ray ray, t_range range, t_hit_record *rec)
{
	int		hit;
	double	closest;

	hit = 0;
	closest = range.t_max;
	if (hit_body(cy, ray, range, rec))
	{
		hit = 1;
		closest = rec->t;
	}
	if (hit_caps(cy, ray, (t_range){range.t_min, closest}, rec))
		hit = 1;
	return (hit);
}
