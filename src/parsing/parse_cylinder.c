#include "parser.h"
// parse_3.c
int	parse_cylinder(t_scene *scene, char **tokens)
{
	t_cylinder	cylinder;
	t_color		color;
	
	if (ft_str_arr_len(tokens) != 6)
		return (parse_error("Cylinder: wrong format"));
	
	if (!parse_vector(&cylinder.center, tokens[1], -INFINITY, INFINITY))
		return (parse_error("Cylinder: invalid center"));
	
	if (!parse_vector(&cylinder.axis, tokens[2], -1.0, 1.0))
		return (parse_error("Cylinder: invalid axis"));
	if (!is_normalized(cylinder.axis))
		return (parse_error("Cylinder axis must be normalized"));
	
	if (!parse_float(&cylinder.diameter, tokens[3]))
		return (parse_error("Cylinder: invalid diameter"));
	if (cylinder.diameter <= 0)
		return (parse_error("Cylinder diameter must be > 0"));
	
	if (!parse_float(&cylinder.height, tokens[4]))
		return (parse_error("Cylinder: invalid height"));
	if (cylinder.height <= 0)
		return (parse_error("Cylinder height must be > 0"));
	
	if (!parse_color(&color, tokens[5]))
		return (parse_error("Cylinder: invalid color"));
	
	cylinder.color = color;
	
	if (!add_cylinder(scene, cylinder))
		return (parse_error("Memory allocation failed"));
	
	return (1);
}