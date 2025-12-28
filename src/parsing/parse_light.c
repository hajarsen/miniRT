#include "parser.h"
// parse_7.c
int	parse_light(t_scene *scene, char **tokens)
{
	t_color	color;
	
	if (scene->has_light)
		return (parse_error("Light already defined"));
	if (ft_str_arr_len(tokens) != 4)
		return (parse_error("Light: wrong format"));
	
	if (!parse_vector(&scene->light.position, tokens[1], -INFINITY, INFINITY))
		return (parse_error("Light: invalid position"));
	
	if (!parse_float(&scene->light.brightness, tokens[2]))
		return (parse_error("Light: invalid brightness"));
	if (!in_interval(scene->light.brightness, 0.0, 1.0))
		return (parse_error("Light brightness must be [0.0,1.0]"));
	
	if (!parse_color(&color, tokens[3]))
		return (parse_error("Light: invalid color"));
	
	scene->light.color = color;
	scene->has_light = 1;
	return (1);
}