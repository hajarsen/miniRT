#include "parser.h"
// maths.4
t_vector vect_div(t_vector v, double t)
{
	t_vector res;
	
	if (t == 0)
		return v;
	res.x = v.x / t;
	res.y = v.y / t;
	res.z = v.z / t;
	return res;
}

t_point3 ray_at(t_ray ray, double t)
{
	return (vec_add(ray.origin, vec_mult(ray.direction, t)));
}

t_vector vec_scale(t_vector v, double s)
{
	return (vect_scal(v, s));
}