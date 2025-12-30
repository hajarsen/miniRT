/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:50:40 by hsennane          #+#    #+#             */
/*   Updated: 2025/12/30 03:41:58 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_camera(t_scene *scene, char **tokens)
{
	if (scene->has_camera)
		return (parse_error("Camera already defined"));
	if (ft_str_arr_len(tokens) != 4)
		return (parse_error("Camera: wrong format"));
	if (!parse_vector(&scene->camera.viewpoint, tokens[1], -INFINITY, INFINITY))
		return (parse_error("Camera: invalid viewpoint"));
	if (!parse_vector(&scene->camera.orientation, tokens[2], -1.0, 1.0))
		return (parse_error("Camera: invalid orientation"));
	if (!is_normalized(scene->camera.orientation))
		return (parse_error("Camera orientation must be normalized"));
	if (!parse_float(&scene->camera.fov, tokens[3]))
		return (parse_error("Camera: invalid FOV"));
	if (!in_interval(scene->camera.fov, 0.0, 180.0))
		return (parse_error("Camera FOV must be [0,180]"));
	scene->has_camera = 1;
	return (1);
}

int	parse_ambient(t_scene *scene, char **tokens)
{
	t_color	color;

	if (scene->has_ambient)
		return (parse_error("Ambient light already defined"));
	if (ft_str_arr_len(tokens) != 3)
		return (parse_error("Ambient: wrong format"));
	if (!parse_float(&scene->ambient.ratio, tokens[1]))
		return (parse_error("Ambient: invalid ratio"));
	if (!in_interval(scene->ambient.ratio, 0.0, 1.0))
		return (parse_error("Ambient ratio must be [0.0,1.0]"));
	if (!parse_color(&color, tokens[2]))
		return (parse_error("Ambient: invalid color"));
	scene->ambient.color = color;
	scene->has_ambient = 1;
	return (1);
}

int	parse_light(t_scene *scene, char **tokens)
{
	t_color	color;

	if (scene->has_light)
		return (parse_error("Light already defined"));
	if (ft_str_arr_len(tokens) != 4)
		return (parse_error("Light: wrong format"));
	if (!parse_vector(&scene->light.position, tokens[1], -INFINITY, INFINITY))
		return (parse_error("Light: invalid position"));
	if (!parse_float(&scene->light.brightness, tokens[2]))
		return (parse_error("Light: invalid brightness"));
	if (!in_interval(scene->light.brightness, 0.0, 1.0))
		return (parse_error("Light brightness must be [0.0,1.0]"));
	if (!parse_color(&color, tokens[3]))
		return (parse_error("Light: invalid color"));
	scene->light.color = color;
	scene->has_light = 1;
	return (1);
}
