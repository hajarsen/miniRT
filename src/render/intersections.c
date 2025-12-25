#include "parser.h"
// intersections.c

// int	hit_sphere(t_sphere *sphere, t_ray ray, t_range range, t_hit_record *rec)
// {
// 	t_vector	oc;
// 	double		radius;
// 	double		a;
// 	double		b;
// 	double		c;
// 	double		discriminant;
// 	double		t1;
// 	double		t2;
// 	double		t_hit;
// 	t_vector	outward_normal;

// 	oc = vec_sub(ray.origin, sphere->center);
// 	radius = sphere->diameter / 2.0;

// 	a = vec_dot(ray.direction, ray.direction);
// 	b = 2.0 * vec_dot(oc, ray.direction);
// 	c = vec_dot(oc, oc) - radius * radius;
// 	discriminant = b * b - 4 * a * c;

// 	if (discriminant < 0)
// 		return (0);

// 	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
// 	t2 = (-b + sqrt(discriminant)) / (2.0 * a);

// 	t_hit = -1.0;
// 	if (t1 > range.t_min && t1 < range.t_max)
// 		t_hit = t1;
// 	else if (t2 > range.t_min && t2 < range.t_max)
// 		t_hit = t2;

// 	if (t_hit == -1.0)
// 		return (0);

// 	rec->t = t_hit;
// 	rec->p = ray_at(ray, rec->t);
// 	outward_normal = vec_unit(vec_sub(rec->p, sphere->center));
// 	rec->front_face = (vec_dot(ray.direction, outward_normal) < 0);

// 	if (rec->front_face)
// 		rec->normal = outward_normal;
// 	else
// 		rec->normal = vec_mult(outward_normal, -1);

// 	rec->color = sphere->color;
// 	return (1);
// }
// intersections.c - hit_sphere (just the normal calculation part)
int hit_sphere(t_sphere *sphere, t_ray ray, t_range range, t_hit_record *rec)
{
	t_vector oc;
	double radius;
	double a;
	double half_b; // Changed from b
	double c;
	double discriminant;
	double sqrtd;
	double t_hit;
	t_vector outward_normal;

	oc = vec_sub(ray.origin, sphere->center);
	radius = sphere->diameter / 2.0;

	a = vec_dot(ray.direction, ray.direction);
	half_b = vec_dot(oc, ray.direction); // Changed: removed the 2.0
	c = vec_dot(oc, oc) - radius * radius;
	discriminant = half_b * half_b - a * c; // Changed formula

	if (discriminant < 0)
		return (0);

	sqrtd = sqrt(discriminant);
	t_hit = (-half_b - sqrtd) / a; // Changed formula

	if (t_hit < range.t_min || t_hit > range.t_max)
	{
		t_hit = (-half_b + sqrtd) / a; // Changed formula
		if (t_hit < range.t_min || t_hit > range.t_max)
			return (0);
	}
	rec->t = t_hit;
	rec->p = ray_at(ray, rec->t);
	outward_normal = vect_div(vec_sub(rec->p, sphere->center), radius);
	rec->front_face = (vec_dot(ray.direction, outward_normal) < 0);
	if (rec->front_face)
		rec->normal = outward_normal;
	else
		rec->normal = vec_mult(outward_normal, -1);
	rec->color = sphere->color;
	return (1);
}

// int	hit_plane(t_plane *plane, t_ray ray, t_range range, t_hit_record *rec)
// {
// 	double	denom;
// 	double	t;
// 	t_vector	p0_minus_origin;

// 	denom = vec_dot(ray.direction, plane->normal);
// 	if (fabs(denom) < 1e-8)
// 		return (0);

// 	p0_minus_origin = vec_sub(plane->point, ray.origin);
// 	t = vec_dot(p0_minus_origin, plane->normal) / denom;

// 	if (t < range.t_min || t > range.t_max)
// 		return (0);

// 	rec->t = t;
// 	rec->p = ray_at(ray, t);
// 	rec->color = plane->color;
// 	rec->front_face = (denom < 0);

// 	if (rec->front_face)
// 		rec->normal = plane->normal;
// 	else
// 		rec->normal = vec_mult(plane->normal, -1);

// 	return (1);
// }
// intersections.c - hit_plane function
// intersections.c - hit_plane function
int	hit_plane(t_plane *plane, t_ray ray, t_range range, t_hit_record *rec)
{
	double		denom;
	double		t;
	t_vector	p0_minus_origin;
	t_vector	outward_normal;

	denom = vec_dot(ray.direction, plane->normal);
	
	// If ray is parallel to plane
	if (fabs(denom) < 1e-8)
		return (0);
	
	p0_minus_origin = vec_sub(plane->point, ray.origin);
	t = vec_dot(p0_minus_origin, plane->normal) / denom;
	
	if (t < range.t_min || t > range.t_max)
		return (0);
	
	rec->t = t;
	rec->p = ray_at(ray, t);
	rec->color = plane->color;
	
	// CRITICAL: Use the plane's normal as outward normal
	outward_normal = plane->normal;
	
	// Determine which side of plane we hit
	rec->front_face = (denom < 0);
	
	// Always orient normal toward the ray origin (viewer)
	if (rec->front_face)
		rec->normal = outward_normal;
	else
		rec->normal = vec_mult(outward_normal, -1);
	
	return (1);
}

static int is_within_height(t_cylinder *cy, t_point3 p)
{
	t_vector cp;
	double projection;

	cp = vec_sub(p, cy->center);
	projection = vec_dot(cp, cy->axis);
	return (projection >= 0 && projection <= cy->height);
}

// static t_vector	get_body_normal(t_cylinder *cy, t_point3 p)
// {
// 	t_vector	cp;
// 	t_vector	axis_component;

// 	cp = vec_sub(p, cy->center);
// 	axis_component = vec_mult(cy->axis, vec_dot(cp, cy->axis));
// 	return (vec_unit(vec_sub(cp, axis_component)));
// }
// intersections.c - get_body_normal function
static t_vector get_body_normal(t_cylinder *cy, t_point3 p)
{
	t_vector cp;
	t_vector axis_component;
	t_vector radial;

	cp = vec_sub(p, cy->center);
	axis_component = vec_mult(cy->axis, vec_dot(cp, cy->axis));
	radial = vec_sub(cp, axis_component);

	// CRITICAL: Normalize before returning
	return (vec_unit(radial));
}

static int solve_body_quadratic(t_vector oc_perp, t_vector d_perp,
								double radius, double *t)
{
	double a;
	double b;
	double c;
	double disc;
	double sqrt_disc;

	a = vec_dot(d_perp, d_perp);
	b = 2.0 * vec_dot(oc_perp, d_perp);
	c = vec_dot(oc_perp, oc_perp) - radius * radius;
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (0);
	sqrt_disc = sqrt(disc);
	t[0] = (-b - sqrt_disc) / (2.0 * a);
	t[1] = (-b + sqrt_disc) / (2.0 * a);
	return (1);
}

static int hit_body(t_cylinder *cy, t_ray ray, t_range range,
					t_hit_record *rec)
{
	t_vector oc;
	t_vector d_perp;
	t_vector oc_perp;
	double t[2];
	t_point3 p;
	int i;

	oc = vec_sub(ray.origin, cy->center);
	d_perp = vec_sub(ray.direction, vec_mult(cy->axis, vec_dot(ray.direction, cy->axis)));
	oc_perp = vec_sub(oc, vec_mult(cy->axis, vec_dot(oc, cy->axis)));

	if (!solve_body_quadratic(oc_perp, d_perp, cy->diameter / 2.0, t))
		return (0);

	i = -1;
	while (++i < 2)
	{
		if (t[i] > range.t_min && t[i] < range.t_max)
		{
			p = ray_at(ray, t[i]);
			if (is_within_height(cy, p))
			{
				rec->t = t[i];
				rec->p = p;
				// rec->normal = get_body_normal(cy, p);
				// rec->front_face = (vec_dot(ray.direction, rec->normal) < 0);
				// if (!rec->front_face)
				// 	rec->normal = vec_mult(rec->normal, -1);
				t_vector outward_normal = get_body_normal(cy, p);
				rec->front_face = (vec_dot(ray.direction, outward_normal) < 0);
				if (rec->front_face)
					rec->normal = outward_normal;
				else
					rec->normal = vec_mult(outward_normal, -1);
				rec->color = cy->color;
				return (1);
			}
		}
	}
	return (0);
}

static int is_in_circle(t_point3 p, t_point3 cap_center, double radius)
{
	t_vector to_p;
	double dist_sq;

	to_p = vec_sub(p, cap_center);
	dist_sq = vec_dot(to_p, to_p);
	return (dist_sq <= radius * radius);
}

static int hit_cap(t_point3 cap_center, t_vector normal, double radius,
				   t_ray ray, t_range range, t_hit_record *rec)
{
	double denom;
	double t;
	t_vector p0_minus_o;
	t_point3 p;

	denom = vec_dot(ray.direction, normal);
	if (fabs(denom) < 1e-8)
		return (0);

	p0_minus_o = vec_sub(cap_center, ray.origin);
	t = vec_dot(p0_minus_o, normal) / denom;

	if (t < range.t_min || t > range.t_max)
		return (0);

	p = ray_at(ray, t);
	if (!is_in_circle(p, cap_center, radius))
		return (0);

	rec->t = t;
	rec->p = p;
	rec->front_face = (denom < 0);

	if (rec->front_face)
		rec->normal = normal;
	else
		rec->normal = vec_mult(normal, -1);

	return (1);
}

int hit_cylinder(t_cylinder *cy, t_ray ray, t_range range, t_hit_record *rec)
{
	t_hit_record temp;
	int hit;
	double closest;
	t_point3 top_center;
	double radius;

	hit = 0;
	closest = range.t_max;
	radius = cy->diameter / 2.0;

	if (hit_body(cy, ray, (t_range){range.t_min, closest}, rec))
	{
		hit = 1;
		closest = rec->t;
	}

	if (hit_cap(cy->center, vec_mult(cy->axis, -1), radius,
				ray, (t_range){range.t_min, closest}, &temp))
	{
		*rec = temp;
		rec->color = cy->color;
		hit = 1;
		closest = rec->t;
	}

	top_center = vec_add(cy->center, vec_mult(cy->axis, cy->height));
	if (hit_cap(top_center, cy->axis, radius,
				ray, (t_range){range.t_min, closest}, &temp))
	{
		*rec = temp;
		rec->color = cy->color;
		hit = 1;
	}

	return (hit);
}

int hit_anything(t_scene *scene, t_ray ray, t_range range, t_hit_record *rec)
{
	t_hit_record temp_rec;
	int has_hit_anything;
	double closest_so_far;
	int i;

	has_hit_anything = 0;
	closest_so_far = range.t_max;

	i = 0;
	while (i < scene->sphere_count)
	{
		if (hit_sphere(&scene->spheres[i], ray,
					   (t_range){range.t_min, closest_so_far}, &temp_rec) == 1)
		{
			has_hit_anything = 1;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
		}
		i++;
	}
	i = 0;
	while (i < scene->plane_count)
	{
		if (hit_plane(&scene->planes[i], ray,
					  (t_range){range.t_min, closest_so_far}, &temp_rec) == 1)
		{
			has_hit_anything = 1;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
		}
		i++;
	}

	i = 0;
	while (i < scene->cylinder_count)
	{
		if (hit_cylinder(&scene->cylinders[i], ray,
						 (t_range){range.t_min, closest_so_far}, &temp_rec) == 1)
		{
			has_hit_anything = 1;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
		}
		i++;
	}

	return (has_hit_anything);
}