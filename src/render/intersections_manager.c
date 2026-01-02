/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_manager.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 03:11:49 by hrhilane          #+#    #+#             */
/*   Updated: 2025/12/30 03:42:49 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	check_obj(int *hit, t_hit_record *rec, t_range *rng,
	t_hit_record tmp)
{
	*hit = 1;
	rng->t_max = tmp.t;
	*rec = tmp;
}

// int	hit_anything(t_scene *s, t_ray r, t_range rng, t_hit_record *rec)
// {
// 	t_hit_record	tmp;
// 	int				hit;
// 	int				i;

// 	hit = 0;
// 	i = -1;
// 	rec->obj_index = -1;
// 	while (++i < s->sphere_count)
// 	{
// 		if (hit_sphere(&s->spheres[i], r, rng, &tmp))
// 			check_obj(&hit, rec, &rng, tmp);
// 	}
// 	i = -1;
// 	while (++i < s->plane_count)
// 	{
// 		if (hit_plane(&s->planes[i], r, rng, &tmp))
// 			check_obj(&hit, rec, &rng, tmp);
// 	}
// 	i = -1;
// 	while (++i < s->cylinder_count)
// 	{
// 		if (hit_cylinder(&s->cylinders[i], r, rng, &tmp))
// 		{
// 			check_obj(&hit, rec, &rng, tmp);
// 			rec->obj_index = i;
// 		}
// 	}
// 	return (hit);
// }

static int	check_spheres(t_scene *s, t_ray r, t_range *rng,
				t_hit_record *rec)
{
	t_hit_record	tmp;
	int				i;
	int				hit;

	hit = 0;
	i = -1;
	while (++i < s->sphere_count)
	{
		if (hit_sphere(&s->spheres[i], r, *rng, &tmp))
		{
			check_obj(&hit, rec, rng, tmp);
		}
	}
	return (hit);
}

static int	check_planes(t_scene *s, t_ray r, t_range *rng,
				t_hit_record *rec)
{
	t_hit_record	tmp;
	int				i;
	int				hit;

	hit = 0;
	i = -1;
	while (++i < s->plane_count)
	{
		if (hit_plane(&s->planes[i], r, *rng, &tmp))
		{
			check_obj(&hit, rec, rng, tmp);
		}
	}
	return (hit);
}

static int	check_cylinders(t_scene *s, t_ray r, t_range *rng,
				t_hit_record *rec)
{
	t_hit_record	tmp;
	int				i;
	int				hit;

	hit = 0;
	i = -1;
	while (++i < s->cylinder_count)
	{
		if (hit_cylinder(&s->cylinders[i], r, *rng, &tmp))
		{
			check_obj(&hit, rec, rng, tmp);
			rec->obj_index = i;
		}
	}
	return (hit);
}

int	hit_anything(t_scene *s, t_ray r, t_range rng, t_hit_record *rec)
{
	int	hit;

	hit = 0;
	rec->obj_index = -1;
	hit |= check_spheres(s, r, &rng, rec);
	hit |= check_planes(s, r, &rng, rec);
	hit |= check_cylinders(s, r, &rng, rec);
	return (hit);
}
