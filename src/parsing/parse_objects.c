/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:51:16 by hsennane          #+#    #+#             */
/*   Updated: 2025/12/30 03:42:17 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_cylinder(t_scene *scene, char **tokens)
{
	t_cylinder	cylinder;
	t_color		color;

	if (ft_str_arr_len(tokens) != 6)
		return (parse_error("Cylinder: wrong format"));
	if (!parse_vector(&cylinder.center, tokens[1], -INFINITY, INFINITY))
		return (parse_error("Cylinder: invalid center"));
	if (!parse_vector(&cylinder.axis, tokens[2], -1.0, 1.0))
		return (parse_error("Cylinder: invalid axis"));
	if (!is_normalized(cylinder.axis))
		return (parse_error("Cylinder axis must be normalized"));
	if (!parse_float(&cylinder.diameter, tokens[3]))
		return (parse_error("Cylinder: invalid diameter"));
	if (cylinder.diameter <= 0)
		return (parse_error("Cylinder diameter must be > 0"));
	if (!parse_float(&cylinder.height, tokens[4]))
		return (parse_error("Cylinder: invalid height"));
	if (cylinder.height <= 0)
		return (parse_error("Cylinder height must be > 0"));
	if (!parse_color(&color, tokens[5]))
		return (parse_error("Cylinder: invalid color"));
	cylinder.color = color;
	if (!add_cylinder(scene, cylinder))
		return (parse_error("Memory allocation failed"));
	return (1);
}

int	parse_plane(t_scene *scene, char **tokens)
{
	t_plane	plane;
	t_color	color;

	if (ft_str_arr_len(tokens) != 4)
		return (parse_error("Plane: wrong format"));
	if (!parse_vector(&plane.point, tokens[1], -INFINITY, INFINITY))
		return (parse_error("Plane: invalid point"));
	if (!parse_vector(&plane.normal, tokens[2], -1.0, 1.0))
		return (parse_error("Plane: invalid normal"));
	if (!is_normalized(plane.normal))
		return (parse_error("Plane normal must be normalized"));
	if (!parse_color(&color, tokens[3]))
		return (parse_error("Plane: invalid color"));
	plane.color = color;
	if (!add_plane(scene, plane))
		return (parse_error("Memory allocation failed"));
	return (1);
}

int	parse_sphere(t_scene *scene, char **tokens)
{
	t_sphere	sphere;
	t_color		color;

	if (ft_str_arr_len(tokens) != 4)
		return (parse_error("Sphere: wrong format"));
	if (!parse_vector(&sphere.center, tokens[1], -INFINITY, INFINITY))
		return (parse_error("Sphere: invalid center"));
	if (!parse_float(&sphere.diameter, tokens[2]))
		return (parse_error("Sphere: invalid diameter"));
	if (sphere.diameter <= 0)
		return (parse_error("Sphere diameter must be > 0"));
	if (!parse_color(&color, tokens[3]))
		return (parse_error("Sphere: invalid color"));
	sphere.color = color;
	if (!add_sphere(scene, sphere))
		return (parse_error("Memory allocation failed"));
	return (1);
}
