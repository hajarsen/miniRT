/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:52:01 by hsennane          #+#    #+#             */
/*   Updated: 2025/12/28 20:04:48 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*trim_line(char *line)
{
	char	*start;
	char	*end;

	if (!line)
		return (NULL);
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	start = line;
	while (*start && (*start == ' ' || *start == '\t'))
		start++;
	end = start + ft_strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t'))
		*end-- = '\0';
	if (start != line)
		ft_memmove(line, start, ft_strlen(start) + 1);
	return (line);
}

static int	parse_line_util(t_scene *scene, char **tokens)
{
	int	result;

	if (ft_strncmp(tokens[0], "A", 2) == 0)
		result = parse_ambient(scene, tokens);
	else if (ft_strncmp(tokens[0], "C", 2) == 0)
		result = parse_camera(scene, tokens);
	else if (ft_strncmp(tokens[0], "L", 2) == 0)
		result = parse_light(scene, tokens);
	else if (ft_strncmp(tokens[0], "sp", 3) == 0)
		result = parse_sphere(scene, tokens);
	else if (ft_strncmp(tokens[0], "pl", 3) == 0)
		result = parse_plane(scene, tokens);
	else if (ft_strncmp(tokens[0], "cy", 3) == 0)
		result = parse_cylinder(scene, tokens);
	else
		result = parse_error("Unknown identifier");
	return (result);
}

int	parse_line(t_scene *scene, char *line)
{
	char	**tokens;
	int		result;
	char	*comment;

	if (!line || *line == '\0')
		return (1);
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	comment = ft_strchr(line, '#');
	if (comment)
		*comment = '\0';
	trim_line(line);
	if (*line == '\0')
		return (1);
	tokens = ft_split(line, ' ');
	if (!tokens)
		return (parse_error("Memory allocation failed"));
	result = parse_line_util(scene, tokens);
	free_str_array(tokens);
	return (result);
}

static int	parse_rt_file_util(t_scene *scene, const char *filename)
{
	int		fd;
	char	*line;
	int		line_num;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (parse_error("Cannot open file"));
	init_scene(scene);
	line_num = 0;
	line = get_next_line(fd);
	while (line)
	{
		line_num++;
		if (!parse_line(scene, line))
		{
			free(line);
			close(fd);
			clean_scene(scene);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

int	parse_rt_file(t_scene *scene, const char *filename)
{
	if (!filename || ft_strlen(filename) < 3 || ft_strncmp(filename
			+ ft_strlen(filename) - 3, ".rt", 3) != 0)
		return (parse_error("File must have .rt extension"));
	if (!parse_rt_file_util(scene, filename))
		return (0);
	if (!scene->has_ambient || !scene->has_camera || !scene->has_light)
	{
		if (!scene->has_ambient)
			parse_error("Missing mandatory element (A)");
		if (!scene->has_camera)
			parse_error("Missing mandatory element (C)");
		if (!scene->has_light)
			parse_error("Missing mandatory element (L)");
		clean_scene(scene);
		return (0);
	}
	if (!scene->sphere_count && !scene->plane_count && !scene->cylinder_count)
	{
		parse_error("Scene must contain at least one object (sp, pl, or cy)");
		clean_scene(scene);
		return (0);
	}
	return (1);
}
