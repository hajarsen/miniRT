/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_cylinder_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 21:12:14 by hajar             #+#    #+#             */
/*   Updated: 2026/01/06 03:42:36 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	fill_body_record(t_hit_record *rec, t_body_data data)
{
	rec->t = data.t_val;
	rec->p = data.p;
	set_face_normal(rec, data.ray, get_body_normal(data.cy, data.p));
	rec->color = data.cy->color;
	rec->obj_type = OBJ_CYLINDER;
	get_cylinder_uv(rec, data.cy);
	return (1);
}
