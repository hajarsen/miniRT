/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 20:21:51 by hsennane          #+#    #+#             */
/*   Updated: 2025/12/30 03:43:17 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	calculate_color(t_minirt *data, t_hit_record *rec)
{
	t_scene		*s;
	t_vector	light_dir;
	t_color		result;

	s = data->scene;
	if (rec->obj_type == OBJ_PLANE && data->check_planes)
		rec->color = get_plane_checkerboard(rec);
	else if (rec->obj_type == OBJ_CYLINDER && data->check_cylinders)
		rec->color = get_cylinder_checkerboard(rec, s);
	else if (rec->obj_type == OBJ_SPHERE && data->check_spheres)
		rec->color = get_sphere_checkerboard(rec);
	result = get_ambient(s, rec);
	if (is_in_shadow(s, rec, &s->light))
		return (result);
	light_dir = vec_unit(vec_sub(s->light.position, rec->p));
	result = vec_add(result, get_diffuse(s, rec, light_dir));
	result = vec_add(result, get_specular(s, rec, light_dir));
	return ((t_color){fmin(1.0, result.x), fmin(1.0, result.y), fmin(1.0,
			result.z)});
}
