/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 20:10:40 by hsennane          #+#    #+#             */
/*   Updated: 2026/01/01 15:48:52 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	close_window(t_minirt *data)
{
	clean_scene(data->scene);
	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(0);
	return (0);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	key_hook(int keycode, t_minirt *data)
{
	if (keycode == XK_Escape || keycode == 65307)
		return (close_window(data));
	if (keycode == KEY_C)
	{
		data->checkers_on = !data->checkers_on;
		render_scene(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	}
	return (0);
}

int	init_window(t_minirt *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (parse_error("MiniLibX initialization failed"), 0);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "miniRT");
	if (!data->win)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		return (parse_error("Window creation failed"), 0);
	}
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img.img)
		return (parse_error("Image creation failed"), 0);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	data->img.width = WIDTH;
	data->img.height = HEIGHT;
	mlx_hook(data->win, 2, 1L << 0, key_hook, data);
	mlx_hook(data->win, 17, 0, close_window, data);
	return (1);
}

