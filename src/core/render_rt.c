#include "parser.h"

static int	color_to_int(t_color color)
{
	int	r;
	int	g;
	int	b;

	r = (int)(255.999 * fmin(1.0, color.x));
	g = (int)(255.999 * fmin(1.0, color.y));
	b = (int)(255.999 * fmin(1.0, color.z));
	return (r << 16 | g << 8 | b);
}

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
			u = (double)(data->img.width - 1 - x) / (data->img.width - 1);
			v = (double)(data->img.height - 1 - y) / (data->img.height - 1);
			color = trace_pixel(data, u, v);
			put_pixel(&data->img, x, y, color);
			x++;
		}
		y++;
	}
}
