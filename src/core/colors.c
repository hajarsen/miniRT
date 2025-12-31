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

static t_color	get_ambient(t_scene *s, t_hit_record *rec)
{
	t_color	a;

	a = vec_mult(s->ambient.color, s->ambient.ratio);
	return ((t_color){
		a.x * rec->color.x,
		a.y * rec->color.y,
		a.z * rec->color.z
	});
}

static t_color	get_diffuse(t_scene *s, t_hit_record *rec,
		t_vector light_dir)
{
	double	diff;
	t_color	d;

	diff = fmax(vec_dot(rec->normal, light_dir), 0.0);
	d = vec_mult(s->light.color, diff * s->light.brightness);
	return ((t_color){
		d.x * rec->color.x,
		d.y * rec->color.y,
		d.z * rec->color.z
	});
}

static t_color	get_specular(t_scene *s, t_hit_record *rec,
		t_vector light_dir)
{
	t_vector	view_dir;
	t_vector	reflect_dir;
	double		spec;

	view_dir = vec_unit(vec_sub(s->camera.viewpoint, rec->p));
	reflect_dir = reflect_vect(vec_mult(light_dir, -1), rec->normal);
	spec = pow(fmax(vec_dot(view_dir, reflect_dir), 0.0), 64.0);
	return (vec_mult(s->light.color, spec * 0.5 * s->light.brightness));
}

static	t_color	get_checkerboard(t_hit_record *rec)
{
	double	size;
	int		checker;

	size = 5.0;
	checker = (int)(floor(rec->p.x / size + EPSILON)
			+ floor(rec->p.y / size + EPSILON)
			+ floor(rec->p.z / size + EPSILON));
	if (checker % 2 != 0)
		return ((t_color){0, 0, 0});
	return (rec->color);
}

t_color	calculate_color(t_minirt *data, t_hit_record *rec)
{
	t_scene		*s;
	t_vector	light_dir;
	t_color		result;

	s = data->scene;
	if (rec->is_checker && data->checkers_on)
		rec->color = get_checkerboard(rec);
	result = get_ambient(s, rec);
	if (is_in_shadow(s, rec, &s->light))
		return (result);
	light_dir = vec_unit(vec_sub(s->light.position, rec->p));
	result = vec_add(result, get_diffuse(s, rec, light_dir));
	result = vec_add(result, get_specular(s, rec, light_dir));
	return ((t_color){
		fmin(1.0, result.x),
		fmin(1.0, result.y),
		fmin(1.0, result.z)
	});
}
