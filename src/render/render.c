#include "parser.h"


void	render_test_pattern(t_minirt *data)
{
	int	x, y, color;
	
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			int	r = (x * 255) / WIDTH;
			int	g = (y * 255) / HEIGHT;
			int	b = 128;
			
			int	dx = x - WIDTH / 2;
			int	dy = y - HEIGHT / 2;
			int	distance = sqrt(dx * dx + dy * dy);
			
			if (distance < 100)
				color = 0xFFFFFF;
			else
				color = (r << 16) | (g << 8) | b;
			
			put_pixel(&data->img, x, y, color);
			x++;
		}
		y++;
	}
}


int	render(t_minirt *data)
{
	ft_bzero(data->img.addr, WIDTH * HEIGHT * (data->img.bits_per_pixel / 8));
	
	if (data->scene->sphere_count == 0 && 
		data->scene->plane_count == 0 && 
		data->scene->cylinder_count == 0)
	{
		printf("⚠️  No objects in scene. Using test pattern.\n");
		render_test_pattern(data);
	}
	else
	{
		printf("🎨 Ray tracing %d objects...\n",
			data->scene->sphere_count + data->scene->plane_count + 
			data->scene->cylinder_count);
		render_scene(data); 
	}
	
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	
	mlx_string_put(data->mlx, data->win, 10, 20, 0xFFFFFF,
		"miniRT - Ray Tracing - Press ESC to exit");
	
	return (0);
}