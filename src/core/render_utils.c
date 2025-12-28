#include "parser.h"

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
	shadow_ray.origin = vec_add(rec->p, vec_mult(rec->normal, EPSILON_SHADOW));
	if (hit_anything(scene, shadow_ray, (t_range){EPSILON_SHADOW, light_dist
			- EPSILON_SHADOW}, &temp_rec))
		return (1);
	return (0);
}

t_color	calculate_color(t_minirt *data, t_hit_record *rec)
{
	t_color		ambient;
	t_color		diffuse;
	t_vector	light_dir;
	double		diffuse_strength;

	ambient = vec_mult(data->scene->ambient.color, data->scene->ambient.ratio);
	ambient = (t_color){rec->color.x * ambient.x, rec->color.y * ambient.y,
		rec->color.z * ambient.z};
	if (is_in_shadow(data->scene, rec, &data->scene->light))
		return (ambient);
	light_dir = vec_unit(vec_sub(rec->p, data->scene->light.position));
	light_dir = vec_mult(light_dir, -1.0);
	diffuse_strength = fmax(0.0, vec_dot(rec->normal, light_dir));
	diffuse = vec_mult((t_color){diffuse_strength, diffuse_strength,
			diffuse_strength}, data->scene->light.brightness);
	diffuse = (t_color){rec->color.x * diffuse.x, rec->color.y * diffuse.y,
		rec->color.z * diffuse.z};
	return (vec_add(ambient, diffuse));
}
