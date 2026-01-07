/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_float_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 01:45:19 by hajar             #+#    #+#             */
/*   Updated: 2026/01/07 02:11:52 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

const char	*parse_integer_part(const char *s, double *r)
{
	double	d;

	while (isdigit(*s))
	{
		d = (*s - '0');
		if (*r > DBL_MAX / 10.0)
			return (NULL);
		if (*r * 10.0 > DBL_MAX - d)
			return (NULL);
		*r = *r * 10.0 + d;
		s++;
	}
	return (s);
}

const char	*parse_fractional_part(const char *s, double *r)
{
	double	div;
	double	val;

	div = 0.1;
	while (isdigit(*s) && div >= 1e-15)
	{
		val = (*s - '0') * div;
		if (val > DBL_MAX - *r)
			return (NULL);
		*r += val;
		div *= 0.1;
		s++;
	}
	while (isdigit(*s))
		s++;
	return (s);
}
