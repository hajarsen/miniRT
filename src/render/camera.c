#include "parser.h"

static void	viewport_dimensions(t_camera *cam, double aspect_ratio,
		double *vp_width, double *vp_height)
{
	double	theta;
	double	h;
	double	focal_length;

	focal_length = 1.0;
	theta = cam->fov * M_PI / 180.0;
	h = tan(theta / 2.0);
	*vp_height = 2.0 * h * focal_length;
	*vp_width = *vp_height * aspect_ratio;
}

static void	build_camera_basis(t_camera *cam, t_vector *u, t_vector *v,
		t_vector *w)
{
	t_vector	world_up;

	*w = vec_unit(vec_mult(cam->orientation, -1.0));
	world_up = (t_vector){0, 1, 0};
	if (fabs(w->y) > 0.999)
		world_up = (t_vector){1, 0, 0};
	*u = vec_unit(vec_cross(world_up, *w));
	*v = vec_cross(*w, *u);
}

static void	calculate_pixel00_location(t_camera *cam, double focal_length)
{
	t_point3	viewport_upper_left;

	viewport_upper_left = vec_add(cam->viewpoint, vec_mult(cam->orientation,
				focal_length));
	viewport_upper_left = vec_sub(viewport_upper_left, vect_div(cam->horizontal,
				2.0));
	viewport_upper_left = vec_sub(viewport_upper_left, vect_div(cam->vertical,
				2.0));
	cam->pixel00_loc = vec_add(viewport_upper_left,
			vec_mult(vec_add(cam->pixel_delta_u, cam->pixel_delta_v), 0.5));
}

static void	set_camera_vectors(t_camera *cam, double vp_w, double vp_h)
{
	t_vector	u;
	t_vector	v;
	t_vector	w;

	build_camera_basis(cam, &u, &v, &w);
	cam->horizontal = vec_mult(u, -1 * vp_w);
	cam->vertical = vec_mult(v, vp_h);
}

void	setup_camera(t_camera *cam, int img_width, int img_height)
{
	double	viewport_width;
	double	viewport_height;
	double	aspect_ratio;

	aspect_ratio = (double)img_width / (double)img_height;
	viewport_dimensions(cam, aspect_ratio, &viewport_width, &viewport_height);
	set_camera_vectors(cam, viewport_width, viewport_height);
	calculate_pixel00_location(cam, 1.0);
}
