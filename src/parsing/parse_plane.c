#include "parser.h"

int	parse_plane(t_scene *scene, char **tokens)
{
	t_plane	plane;
	t_color	color;
	
	if (ft_str_arr_len(tokens) != 4)
		return (parse_error("Plane: wrong format"));
	
	if (!parse_vector(&plane.point, tokens[1], -INFINITY, INFINITY))
		return (parse_error("Plane: invalid point"));
	
	if (!parse_vector(&plane.normal, tokens[2], -1.0, 1.0))
		return (parse_error("Plane: invalid normal"));
	if (!is_normalized(plane.normal))
		return (parse_error("Plane normal must be normalized"));
	
	if (!parse_color(&color, tokens[3]))
		return (parse_error("Plane: invalid color"));
	
	plane.color = color;
	
	if (!add_plane(scene, plane))
		return (parse_error("Memory allocation failed"));
	
	return (1);
}