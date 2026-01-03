/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 03:16:15 by hsennane          #+#    #+#             */
/*   Updated: 2025/12/30 03:43:22 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_and_init(t_scene *scene, t_minirt *minirt, char *filename)
{
	if (!parse_rt_file(scene, filename))
		return (0);
	ft_bzero(minirt, sizeof(t_minirt));
	minirt->scene = scene;
	minirt->check_planes = 0;
	minirt->check_spheres = 0;
	minirt->check_cylinders = 0;
	if (!init_window(minirt))
	{
		clean_scene(scene);
		return (0);
	}
	return (1);
}

static void	print_scene_info(t_scene *scene)
{
	printf("   Scene parsed successfully!\n");
	printf("   Ambient: ratio=%.2f\n", scene->ambient.ratio);
	printf("   Camera: pos=(%.1f,%.1f,%.1f) fov=%.1f\n",
		scene->camera.viewpoint.x, scene->camera.viewpoint.y,
		scene->camera.viewpoint.z, scene->camera.fov);
	printf("   Light: pos=(%.1f,%.1f,%.1f) brightness=%.2f\n",
		scene->light.position.x, scene->light.position.y,
		scene->light.position.z, scene->light.brightness);
	printf("   Objects: %d spheres, %d planes, %d cylinders\n",
		scene->sphere_count, scene->plane_count, scene->cylinder_count);
}

static void	setup_display(t_minirt *minirt)
{
	render_scene(minirt);
	mlx_put_image_to_window(minirt->mlx, minirt->win,
		minirt->img.img, 0, 0);
	mlx_string_put(minirt->mlx, minirt->win, 10, 20,
		0xFFFFFF, "miniRT: Press ESC to exit");
	mlx_string_put(minirt->mlx, minirt->win, 10, 40,
		0xFFFFFF, "Use .rt files with A, C, L, sp, pl, cy");
}

int	main(int argc, char **argv)
{
	t_scene		scene;
	t_minirt	minirt;

	if (argc != 2)
	{
		parse_error("Usage: ./miniRT <scene.rt>");
		return (1);
	}
	if (!parse_and_init(&scene, &minirt, argv[1]))
		return (1);
	print_scene_info(&scene);
	setup_display(&minirt);
	mlx_loop(minirt.mlx);
	clean_scene(&scene);
	return (0);
}
