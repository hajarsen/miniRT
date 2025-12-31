/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_rt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 20:10:21 by hsennane          #+#    #+#             */
/*   Updated: 2025/12/30 03:43:27 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	trace_pixel(t_minirt *data, double u, double v)
{
	t_ray			ray;
	t_hit_record	rec;
	t_color			color;

	ray = get_ray(&data->scene->camera, u, v);
	if (hit_anything(data->scene, ray, (t_range){0.0001, INFINITY}, &rec))
	{
		color = calculate_color(data, &rec);
		return (color_to_int(color));
	}
	return (0x000000);
}

void	render_scene(t_minirt *data)
{
	int		x;
	int		y;
	double	u;
	double	v;
	int		color;

	setup_camera(&data->scene->camera, data->img.width, data->img.height);
	y = 0;
	while (y < data->img.height)
	{
		x = 0;
		while (x < data->img.width)
		{
			u = (double)x / (data->img.width - 1);
			v = (double)(data->img.height - 1 - y) / (data->img.height - 1);
			color = trace_pixel(data, u, v);
			put_pixel(&data->img, x, y, color);
			x++;
		}
		y++;
	}
}
