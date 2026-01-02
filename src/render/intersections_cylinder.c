/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_cylinder.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 03:14:50 by hrhilane          #+#    #+#             */
/*   Updated: 2026/01/02 04:11:51 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
			rec->obj_type = OBJ_CYLINDER;
			get_cylinder_uv(rec, cy);
			return (1);
		}
	}
	return (0);
}

static int	hit_bottom_cap(t_cylinder *cy, t_ray ray, t_range range,
		t_hit_record *rec)
{
	double		t;
	t_point3	p;
	t_point3	bottom;
	double		denom;

	denom = vec_dot(ray.direction, cy->axis);
	if (fabs(denom) < 1e-8)
		return (0);
	bottom = vec_sub(cy->center, vec_mult(cy->axis, cy->height * 0.5));
	t = vec_dot(vec_sub(bottom, ray.origin), cy->axis) / denom;
	if (t <= range.t_min || t >= range.t_max)
		return (0);
	p = ray_at(ray, t);
	if (!is_in_circle(p, bottom, cy->diameter * 0.5))
		return (0);
	rec->t = t;
	rec->p = p;
	rec->color = cy->color;
	set_face_normal(rec, ray, vec_mult(cy->axis, -1));
	return (1);
}

static int	hit_top_cap(t_cylinder *cy, t_ray ray, t_range range,
		t_hit_record *rec)
{
	double		t;
	t_point3	p;
	t_point3	top;
	double		denom;

	denom = vec_dot(ray.direction, cy->axis);
	if (fabs(denom) < 1e-8)
		return (0);
	top = vec_add(cy->center, vec_mult(cy->axis, cy->height * 0.5));
	t = vec_dot(vec_sub(top, ray.origin), cy->axis) / denom;
	if (t <= range.t_min || t >= range.t_max)
		return (0);
	p = ray_at(ray, t);
	if (!is_in_circle(p, top, cy->diameter * 0.5))
		return (0);
	rec->t = t;
	rec->p = p;
	rec->color = cy->color;
	set_face_normal(rec, ray, cy->axis);
	return (1);
}

static int	hit_caps(t_cylinder *cy, t_ray ray, t_range range,
		t_hit_record *rec)
{
	t_hit_record	tmp;
	int				hit;

	hit = 0;
	ft_bzero(&tmp, sizeof(t_hit_record));
	if (hit_bottom_cap(cy, ray, range, &tmp))
	{
		*rec = tmp;
		range.t_max = tmp.t;
		hit = 1;
	}
	if (hit_top_cap(cy, ray, range, &tmp))
	{
		*rec = tmp;
		hit = 1;
	}
	rec->obj_type = OBJ_CYLINDER;
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
