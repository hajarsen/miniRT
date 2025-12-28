#include "parser.h"
// parse_1.c
int	parse_ambient(t_scene *scene, char **tokens)
{
	t_color	color;
	
	if (scene->has_ambient)
		return (parse_error("Ambient light already defined"));
	if (ft_str_arr_len(tokens) != 3)
		return (parse_error("Ambient: wrong format"));
	
	if (!parse_float(&scene->ambient.ratio, tokens[1]))
		return (parse_error("Ambient: invalid ratio"));
	if (!in_interval(scene->ambient.ratio, 0.0, 1.0))
		return (parse_error("Ambient ratio must be [0.0,1.0]"));
	
	if (!parse_color(&color, tokens[2]))
		return (parse_error("Ambient: invalid color"));
	
	scene->ambient.color = color;
	scene->has_ambient = 1;
	return (1);
}