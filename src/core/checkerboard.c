#include "minirt.h"

t_color	get_plane_checkerboard(t_hit_record *rec)
{
	double	size;
	int		checker;

	size = 2.5;
	checker = (int)(floor(rec->p.x / size + EPSILON) + floor(rec->p.y / size
				+ EPSILON) + floor(rec->p.z / size + EPSILON));
	if (checker % 2 != 0)
		return ((t_color){0, 0, 0});
	return (rec->color);
}

t_color	get_sphere_checkerboard(t_hit_record *rec)
{
	double	theta;
	double	phi;
	double	u;
	double	v;
	int		checker;

	theta = atan2(rec->normal.z, rec->normal.x);
	phi = acos(rec->normal.y);
	u = 1.0 - (theta / (2.0 * M_PI) + 0.5);
	v = 1.0 - phi / M_PI;
	checker = (int)(floor(u * 20.0) + floor(v * 10.0));
	if (checker % 2 != 0)
		return ((t_color){0, 0, 0});
	return (rec->color);
}

t_vector	get_cylinder_radial(t_vector p_local, t_vector axis)
{
	t_vector	proj;
	t_vector	radial;

	proj = vec_mult(axis, vec_dot(p_local, axis));
	radial = vec_sub(p_local, proj);
	return (radial);
}

t_color	get_cylinder_checkerboard(t_hit_record *rec, t_scene *s)
{
	t_cylinder	*cy;
	double		pattern;

	if (rec->obj_index < 0 || rec->obj_index >= s->cylinder_count)
		return (rec->color);
	cy = &s->cylinders[rec->obj_index];
	if (fabs(vec_dot(rec->normal, cy->axis)) > 0.98)
		return (get_plane_checkerboard(rec));
	pattern = sin(rec->u * M_PI * 10.0) * sin(rec->v * M_PI * 10.0);
	if (pattern > 0)
		return ((t_color){0, 0, 0});
	return (rec->color);
}
