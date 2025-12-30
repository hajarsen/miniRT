/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 03:16:35 by hsennane          #+#    #+#             */
/*   Updated: 2025/12/30 03:43:31 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	get_ray(t_camera *cam, double u, double v)
{
	t_ray		ray;
	t_point3	viewport_point;

	ray.origin = cam->viewpoint;
	viewport_point = cam->pixel00_loc;
	viewport_point = vec_add(viewport_point, vec_mult(cam->horizontal, u));
	viewport_point = vec_add(viewport_point, vec_mult(cam->vertical, v));
	ray.direction = vec_sub(viewport_point, ray.origin);
	ray.direction = vec_unit(ray.direction);
	return (ray);
}

int	is_in_shadow(t_scene *scene, t_hit_record *rec, t_light *light)
{
	t_ray			shadow_ray;
	t_vector		light_dir;
	double			light_dist;
	t_hit_record	temp_rec;

	light_dir = vec_sub(light->position, rec->p);
	light_dist = vec_length(light_dir);
	shadow_ray.direction = vec_unit(light_dir);
	shadow_ray.origin = vec_add(rec->p, vec_mult(rec->normal, EPSILON_SHADOW));
	if (hit_anything(scene, shadow_ray, (t_range){EPSILON_SHADOW, light_dist
			- EPSILON_SHADOW}, &temp_rec))
		return (1);
	return (0);
}
