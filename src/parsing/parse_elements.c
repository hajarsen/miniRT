#include "parser.h"
// parse_4.c
int     parse_camera(t_scene *scene, char **tokens)
{
        if (scene->has_camera)
                return (parse_error("Camera already defined"));
        if (ft_str_arr_len(tokens) != 4)
                return (parse_error("Camera: wrong format"));

        if (!parse_vector(&scene->camera.viewpoint, tokens[1], -INFINITY, INFINITY))
                return (parse_error("Camera: invalid viewpoint"));

        if (!parse_vector(&scene->camera.orientation, tokens[2], -1.0, 1.0))
                return (parse_error("Camera: invalid orientation"));
        // if (!is_normalized(scene->camera.orientation))
        //         return (parse_error("Camera orientation must be normalized"));

        if (!parse_float(&scene->camera.fov, tokens[3]))
                return (parse_error("Camera: invalid FOV"));
        if (!in_interval(scene->camera.fov, 0.0, 180.0))
                return (parse_error("Camera FOV must be [0,180]"));

        scene->has_camera = 1;
        return (1);
}