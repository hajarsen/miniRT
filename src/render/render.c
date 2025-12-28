/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 23:55:56 by hsennane          #+#    #+#             */
/*   Updated: 2025/12/29 00:08:55 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	test_pattern_color(int x, int y)
{
	int	r;
	int	g;
	int	b;

	r = (x * 255) / WIDTH;
	g = (y * 255) / HEIGHT;
	b = 128;
	return ((r << 16) | (g << 8) | b);
}

static int	is_center_circle(int x, int y)
{
	int	dx;
	int	dy;

	dx = x - WIDTH / 2;
	dy = y - HEIGHT / 2;
	return (sqrt(dx * dx + dy * dy) < 100);
}

void	render_test_pattern(t_minirt *data)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (is_center_circle(x, y))
				color = 0xFFFFFF;
			else
				color = test_pattern_color(x, y);
			put_pixel(&data->img, x, y, color);
			x++;
		}
		y++;
	}
}

int	render(t_minirt *data)
{
	ft_bzero(data->img.addr, WIDTH * HEIGHT * (data->img.bits_per_pixel / 8));
	if (data->scene->sphere_count == 0 && data->scene->plane_count == 0
		&& data->scene->cylinder_count == 0)
	{
		printf("No objects in scene. Using test pattern.\n");
		render_test_pattern(data);
	}
	else
	{
		printf("Ray tracing %d objects...\n", data->scene->sphere_count
			+ data->scene->plane_count + data->scene->cylinder_count);
		render_scene(data);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	mlx_string_put(data->mlx, data->win, 10, 20, 0xFFFFFF,
		"miniRT - Ray Tracing - Press ESC to exit");
	return (0);
}
