#include "minirt.h"

t_color	get_ambient(t_scene *s, t_hit_record *rec)
{
	t_color	a;

	a = vec_scal(s->ambient.color, s->ambient.ratio);
	return ((t_color){
		a.x * rec->color.x,
		a.y * rec->color.y,
		a.z * rec->color.z
	});
}

t_color	get_diffuse(t_scene *s, t_hit_record *rec,
		t_vector light_dir)
{
	double	diff;
	t_color	d;

	diff = fmax(vec_dot(rec->normal, light_dir), 0.0);
	d = vec_scal(s->light.color, diff * s->light.brightness);
	return ((t_color){
		d.x * rec->color.x,
		d.y * rec->color.y,
		d.z * rec->color.z
	});
}

t_color	get_specular(t_scene *s, t_hit_record *rec,
		t_vector light_dir)
{
	t_vector	view_dir;
	t_vector	reflect_dir;
	double		spec;

	view_dir = vec_unit(vec_sub(s->camera.viewpoint, rec->p));
	reflect_dir = reflect_vect(vec_scal(light_dir, -1), rec->normal);
	spec = pow(fmax(vec_dot(view_dir, reflect_dir), 0.0), 64.0);
	return (vec_scal(s->light.color, spec * 0.5 * s->light.brightness));
}
