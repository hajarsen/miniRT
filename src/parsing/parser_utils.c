/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:52:26 by hsennane          #+#    #+#             */
/*   Updated: 2025/12/28 18:52:28 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_scene(t_scene *scene)
{
	ft_bzero(scene, sizeof(t_scene));
}

void	clean_scene(t_scene *scene)
{
	if (!scene)
		return ;
	free(scene->spheres);
	free(scene->planes);
	free(scene->cylinders);
	ft_bzero(scene, sizeof(t_scene));
}

int	add_sphere(t_scene *scene, t_sphere sphere)
{
	t_sphere	*new;
	int			i;

	new = malloc(sizeof(t_sphere) * (scene->sphere_count + 1));
	if (!new)
		return (0);
	i = 0;
	while (i < scene->sphere_count)
	{
		new[i] = scene->spheres[i];
		i++;
	}
	new[scene->sphere_count] = sphere;
	free(scene->spheres);
	scene->spheres = new;
	scene->sphere_count++;
	return (1);
}

int	add_plane(t_scene *scene, t_plane plane)
{
	t_plane	*new;
	int		i;

	new = malloc(sizeof(t_plane) * (scene->plane_count + 1));
	if (!new)
		return (0);
	i = 0;
	while (i < scene->plane_count)
	{
		new[i] = scene->planes[i];
		i++;
	}
	new[scene->plane_count] = plane;
	free(scene->planes);
	scene->planes = new;
	scene->plane_count++;
	return (1);
}

int	add_cylinder(t_scene *scene, t_cylinder cylinder)
{
	t_cylinder	*new;
	int			i;

	new = malloc(sizeof(t_cylinder) * (scene->cylinder_count + 1));
	if (!new)
		return (0);
	i = 0;
	while (i < scene->cylinder_count)
	{
		new[i] = scene->cylinders[i];
		i++;
	}
	new[scene->cylinder_count] = cylinder;
	free(scene->cylinders);
	scene->cylinders = new;
	scene->cylinder_count++;
	return (1);
}
