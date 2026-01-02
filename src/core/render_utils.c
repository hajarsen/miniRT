/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 03:16:35 by hsennane          #+#    #+#             */
/*   Updated: 2026/01/02 20:37:50 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	get_ray(t_camera *cam, double u, double v)
{
	t_ray		ray;
	t_point3	viewport_point;

	ray.origin = cam->viewpoint;
	viewport_point = cam->pixel00_loc;
	viewport_point = vec_add(viewport_point, vec_scal(cam->horizontal, u));
	viewport_point = vec_add(viewport_point, vec_scal(cam->vertical, v));
	ray.direction = vec_sub(viewport_point, ray.origin);
	ray.direction = vec_unit(ray.direction);
	return (ray);
}

int	is_in_shadow(t_scene *scene, t_hit_record *rec, t_light *light)
{
	t_ray			shadow_ray;
	t_vector		light_dir;
	double			light_dist;
	t_hit_record	tmp;

	light_dir = vec_sub(light->position, rec->p);
	light_dist = vec_length(light_dir);
	light_dir = vec_unit(light_dir);
	shadow_ray.origin = vec_add(rec->p,
			vec_scal(rec->normal, EPSILON_SHADOW));
	shadow_ray.direction = light_dir;
	if (hit_anything(scene, shadow_ray,
			(t_range){EPSILON_SHADOW, light_dist - EPSILON_SHADOW}, &tmp))
		return (1);
	return (0);
}

int	color_to_int(t_color color)
{
	int	r;
	int	g;
	int	b;

	r = (int)(255.999 * fmin(1.0, color.x));
	g = (int)(255.999 * fmin(1.0, color.y));
	b = (int)(255.999 * fmin(1.0, color.z));
	return (r << 16 | g << 8 | b);
}

void	get_cylinder_uv(t_hit_record *rec, t_cylinder *cy)
{
	t_vector	p_local;
	t_vector	radial;
	double		radial_len;

	p_local = vec_sub(rec->p, cy->center);
	rec->v = vec_dot(p_local, cy->axis) / cy->height + 0.5;
	radial = get_cylinder_radial(p_local, cy->axis);
	radial_len = vec_length(radial);
	if (radial_len < 1e-8)
	{
		rec->u = 0.0;
		return ;
	}
	radial = vec_unit(radial);
	calculate_cylinder_u(rec, cy, radial);
}

void	calculate_cylinder_u(t_hit_record *rec, t_cylinder *cy,
		t_vector radial)
{
	t_vector	guide;
	t_vector	u_ref;
	t_vector	v_ref;

	guide = (t_vector){0, 1, 0};
	if (fabs(cy->axis.y) > 0.9)
		guide = (t_vector){1, 0, 0};
	u_ref = vec_unit(vec_cross(guide, cy->axis));
	v_ref = vec_unit(vec_cross(cy->axis, u_ref));
	rec->u = (atan2(vec_dot(radial, v_ref), vec_dot(radial, u_ref)) + M_PI)
		/ (2.0 * M_PI);
}
