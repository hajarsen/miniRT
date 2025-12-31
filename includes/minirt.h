#ifndef MINIRT_H
# define MINIRT_H

#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <limits.h>
#include <float.h>
#include "../minilibx-linux/mlx.h"
#include <X11/keysym.h> 
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "../lib/libft/libft.h"
#include "../lib/get_next_line/get_next_line.h"

#define EPSILON 1e-6
#define WIDTH 1200
#define HEIGHT 1000
#define EPSILON_SHADOW 0.0001
#define KEY_C 99
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif


typedef struct s_vector
{
    double  x;
    double  y;
    double  z;
} t_vector;

typedef t_vector t_point3;
typedef t_vector t_color;

typedef struct s_ray
{
    t_point3    origin;
    t_vector    direction;
} t_ray;

typedef struct s_hit_record
{
    t_point3    p;
    t_vector    normal;
    double      t;
    t_color     color;
    int         front_face;
    int         is_checker;
} t_hit_record;

typedef struct s_range
{
    double  t_min;
    double  t_max;
} t_range;

typedef struct s_sphere
{
    t_point3    center;
    double      diameter;
    t_color     color;
} t_sphere;

typedef struct s_plane
{
    t_point3    point;
    t_vector    normal;
    t_color     color;
} t_plane;

typedef struct s_cylinder
{
    t_point3    center;
    t_vector    axis;
    double      diameter;
    double      height;
    t_color     color;
} t_cylinder;

typedef struct s_ambient
{
    double      ratio;
    t_color     color;
} t_ambient;

typedef struct s_camera
{
    t_point3    viewpoint;
    t_vector    orientation;
    double      fov;
    t_vector    horizontal;
    t_vector    vertical;
    t_point3    pixel00_loc;
    t_vector    pixel_delta_u;
    t_vector    pixel_delta_v;
} t_camera;

typedef struct s_light
{
    t_point3    position;
    double      brightness;
    t_color     color;
} t_light;

typedef struct s_scene
{
    t_ambient   ambient;
    int         has_ambient;
    t_camera    camera;
    int         has_camera;
    t_light     light;
    int         has_light;
    t_sphere    *spheres;
    int         sphere_count;
    t_plane     *planes;
    int         plane_count;
    t_cylinder  *cylinders;
    int         cylinder_count;
} t_scene;

typedef struct s_eq
{
    double  a;
    double  b;
    double  half_b;
    double  c;
    double  discriminant;
    double  sqrtd;
}   t_eq;

typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;
    int     height;
} t_img;

typedef struct s_minirt
{
    void    *mlx;
    void    *win;
    t_img   img;
    t_scene *scene;
    int     checkers_on;
} t_minirt;


double      ft_min(double a, double b);
double      ft_max(double a, double b);
double      ft_abs(double x);
double      ft_power(double base, int exp);
double      vector_length(t_vector v);
bool        float_eq(double a, double b);
bool        in_interval(double value, double min_val, double max_val);
bool        is_normalized(t_vector v);

t_vector    create_vect(float x, float y, float z);
t_vector    vect_add(t_vector v, t_vector w);
t_vector    vect_sub(t_vector v, t_vector w);
t_vector    cross_product(t_vector v, t_vector w);
float       dot_product(t_vector v, t_vector w);
t_vector    normalize(t_vector v);
t_vector    vect_invert(t_vector v);
t_vector    vect_scal(t_vector v, float scal);

float       distance(t_vector v, t_vector w);
t_vector    reflect_vect(t_vector v, t_vector n);
t_vector    refract_vect(t_vector v, t_vector n, float eta);

#define vec_add vect_add
#define vec_sub vect_sub
#define vec_mult vect_scal
#define vec_dot dot_product
#define vec_cross cross_product
#define vec_length vector_length
#define vec_unit normalize

t_vector    vect_div(t_vector v, double t);
t_point3    ray_at(t_ray ray, double t);
t_ray       get_ray(t_camera *cam, double u, double v);


int         parse_rt_file(t_scene *scene, const char *filename);
char        *trim_line(char *line);
int         parse_line(t_scene *scene, char *line);
int         parse_error(const char *msg);


int         parse_sphere(t_scene *scene, char **tokens);
int         parse_plane(t_scene *scene, char **tokens);
int         parse_cylinder(t_scene *scene, char **tokens);
int         parse_ambient(t_scene *scene, char **tokens);
int         parse_camera(t_scene *scene, char **tokens);
int         parse_light(t_scene *scene, char **tokens);


bool        parse_color(t_color *color, char *str);
bool        parse_vector(t_vector *vec, char *str, double min_val, double max_val);
int         parse_float(double *out, const char *str);


void        init_scene(t_scene *scene);
void        clean_scene(t_scene *scene);
int         add_sphere(t_scene *scene, t_sphere sphere);
int         add_plane(t_scene *scene, t_plane plane);
int         add_cylinder(t_scene *scene, t_cylinder cylinder);


int         ft_str_arr_len(char **arr);
void        free_str_array(char **arr);

int         hit_sphere(t_sphere *sphere, t_ray ray, t_range range, t_hit_record *rec);
int         hit_plane(t_plane *plane, t_ray ray, t_range range, t_hit_record *rec);
int         hit_cylinder(t_cylinder *cy, t_ray ray, t_range range, t_hit_record *rec);
int         hit_anything(t_scene *scene, t_ray ray, t_range range, t_hit_record *rec);

void        setup_camera(t_camera *cam, int img_width, int img_height);
t_vector    calculate_color(t_minirt *data, t_hit_record *rec);
int         is_in_shadow(t_scene *scene, t_hit_record *rec, t_light *light);
void        render_scene(t_minirt *data);
int         is_within_height(t_cylinder *cy, t_point3 p);
t_vector    get_body_normal(t_cylinder *cy, t_point3 p);
int         is_in_circle(t_point3 p, t_point3 cap_center, double radius);
void        set_face_normal(t_hit_record *rec, t_ray ray, t_vector outward_normal);
int         color_to_int(t_color color);
int	        solve_cy(t_vector oc, t_ray ray, t_cylinder *cy, double *t);


int         init_window(t_minirt *data);
int         close_window(t_minirt *data);
int         key_hook(int keycode, t_minirt *data);
void        put_pixel(t_img *img, int x, int y, int color);
int         rgb_into_int(int r, int g, int b);

#endif