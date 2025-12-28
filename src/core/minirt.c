/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 20:10:30 by hsennane          #+#    #+#             */
/*   Updated: 2025/12/28 20:10:33 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	main(int argc, char **argv)
{
	t_scene		scene;
	t_minirt	minirt;

	if (argc != 2)
		return (parse_error("Usage: ./miniRT <scene.rt>"), 1);
	if (!parse_rt_file(&scene, argv[1]))
		return (1);
	printf("✅ Scene parsed successfully!\n");
	printf("   Ambient: ratio=%.2f\n", scene.ambient.ratio);
	printf("   Camera: pos=(%.1f,%.1f,%.1f) fov=%.1f\n",
		scene.camera.viewpoint.x, scene.camera.viewpoint.y,
		scene.camera.viewpoint.z, scene.camera.fov);
	printf("   Light: pos=(%.1f,%.1f,%.1f) brightness=%.2f\n",
		scene.light.position.x, scene.light.position.y, scene.light.position.z,
		scene.light.brightness);
	printf("   Objects: %d spheres, %d planes, %d cylinders\n",
		scene.sphere_count, scene.plane_count, scene.cylinder_count);
	ft_bzero(&minirt, sizeof(t_minirt));
	minirt.scene = &scene;
	if (!init_window(&minirt))
	{
		clean_scene(&scene);
		return (1);
	}
	render_scene(&minirt);
	mlx_put_image_to_window(minirt.mlx, minirt.win, minirt.img.img, 0, 0);
	mlx_string_put(minirt.mlx, minirt.win, 10, 20, 0xFFFFFF, "miniRT
		- Ray Tracing - Press ESC to exit");
	mlx_string_put(minirt.mlx, minirt.win, 10, 40, 0xFFFFFF,
		"Use .rt files with A, C, L, sp, pl, cy");
	mlx_loop(minirt.mlx);
	clean_scene(&scene);
	return (0);
}
