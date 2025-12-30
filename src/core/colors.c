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
	t_color		ambient;
	t_color		diffuse;
	t_vector	light_dir;
	double		diffuse_strength;

	ambient = vec_mult(data->scene->ambient.color, data->scene->ambient.ratio);
	ambient = (t_color){rec->color.x * ambient.x, rec->color.y * ambient.y,
		rec->color.z * ambient.z};
	if (is_in_shadow(data->scene, rec, &data->scene->light))
		return (ambient);
	light_dir = vec_unit(vec_sub(rec->p, data->scene->light.position));
	light_dir = vec_mult(light_dir, -1.0);
	diffuse_strength = fmax(0.0, vec_dot(rec->normal, light_dir));
	diffuse = vec_mult((t_color){diffuse_strength, diffuse_strength,
			diffuse_strength}, data->scene->light.brightness);
	diffuse = (t_color){rec->color.x * diffuse.x, rec->color.y * diffuse.y,
		rec->color.z * diffuse.z};
	return (vec_add(ambient, diffuse));
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
