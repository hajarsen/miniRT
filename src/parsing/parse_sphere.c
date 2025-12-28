#include "parser.h"
// parse_9.c
int	parse_sphere(t_scene *scene, char **tokens)
{
	t_sphere	sphere;
	t_color		color;
	
	if (ft_str_arr_len(tokens) != 4)
		return (parse_error("Sphere: wrong format"));
	
	if (!parse_vector(&sphere.center, tokens[1], -INFINITY, INFINITY))
		return (parse_error("Sphere: invalid center"));
	
	if (!parse_float(&sphere.diameter, tokens[2]))
		return (parse_error("Sphere: invalid diameter"));
	if (sphere.diameter <= 0)
		return (parse_error("Sphere diameter must be > 0"));
	
	if (!parse_color(&color, tokens[3]))
		return (parse_error("Sphere: invalid color"));
	
	sphere.color = color;
	
	if (!add_sphere(scene, sphere))
		return (parse_error("Memory allocation failed"));
	
	return (1);
}