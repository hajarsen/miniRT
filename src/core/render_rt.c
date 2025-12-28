#include "parser.h"
//render_rt.c

t_ray	get_ray(t_camera *cam, double u, double v)
{
	t_ray		ray;
	t_point3	viewport_point;

	ray.origin = cam->viewpoint;
	viewport_point = cam->pixel00_loc;
	viewport_point = vec_add(viewport_point, vec_mult(cam->horizontal, u));
	viewport_point = vec_add(viewport_point, vec_mult(cam->vertical, v));
	ray.direction = vec_sub(viewport_point, ray.origin);
	ray.direction = vec_unit(ray.direction);
	return (ray);
}

int	is_in_shadow(t_scene *scene, t_hit_record *rec, t_light *light)
{
	t_ray			shadow_ray;
	t_vector		light_dir;
	double			light_dist;
	t_hit_record	temp_rec;

	light_dir = vec_sub(light->position, rec->p);
	light_dist = vec_length(light_dir);
	shadow_ray.direction = vec_unit(light_dir);
	shadow_ray.origin = vec_add(rec->p, vec_mult(rec->normal, EPSILON_SHADOW));// Increased from 0.001. Not the final value
	if (hit_anything(scene, shadow_ray, (t_range){EPSILON_SHADOW, light_dist - EPSILON_SHADOW}, &temp_rec))
		return (1);
	return (0);
}

t_color	calculate_color(t_minirt *data, t_hit_record *rec)
{
	t_color		ambient;
	t_color		diffuse;
	t_vector	light_dir;
	double		diffuse_strength;
	
	// If colors are ALREADY normalized (0-1), use them directly
	ambient = vec_mult(data->scene->ambient.color, data->scene->ambient.ratio);
	ambient = (t_color){rec->color.x * ambient.x,
					   rec->color.y * ambient.y,
					   rec->color.z * ambient.z};
	
	if (is_in_shadow(data->scene, rec, &data->scene->light))
		return ambient;
	
	// light_dir = vec_unit(vec_sub(data->scene->light.position, rec->p)); // Check later which one is correct
	light_dir = vec_unit(vec_sub(rec->p, data->scene->light.position));
	light_dir = vec_mult(light_dir, -1.0);
	diffuse_strength = fmax(0.0, vec_dot(rec->normal, light_dir));
	
	diffuse = vec_mult((t_color){diffuse_strength, diffuse_strength,
								diffuse_strength}, data->scene->light.brightness);
	diffuse = (t_color){rec->color.x * diffuse.x,
					   rec->color.y * diffuse.y,
					   rec->color.z * diffuse.z};
	
	return vec_add(ambient, diffuse);
}
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
