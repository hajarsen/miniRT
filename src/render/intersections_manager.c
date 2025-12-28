#include "parser.h"

static void	check_obj(int *hit, t_hit_record *rec, t_range *rng,
	t_hit_record tmp)
{
	*hit = 1;
	rng->t_max = tmp.t;
	*rec = tmp;
}

int	hit_anything(t_scene *s, t_ray r, t_range rng, t_hit_record *rec)
{
	t_hit_record	tmp;
	int				hit;
	int				i;

	hit = 0;
	i = -1;
	while (++i < s->sphere_count)
	{
		if (hit_sphere(&s->spheres[i], r, rng, &tmp))
			check_obj(&hit, rec, &rng, tmp);
	}
	i = -1;
	while (++i < s->plane_count)
	{
		if (hit_plane(&s->planes[i], r, rng, &tmp))
			check_obj(&hit, rec, &rng, tmp);
	}
	i = -1;
	while (++i < s->cylinder_count)
	{
		if (hit_cylinder(&s->cylinders[i], r, rng, &tmp))
			check_obj(&hit, rec, &rng, tmp);
	}
	return (hit);
}
