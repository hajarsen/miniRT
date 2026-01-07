/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:51:06 by hsennane          #+#    #+#             */
/*   Updated: 2026/01/07 02:12:21 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_char_type(char c, int *d, int *dot)
{
	if (isdigit(c))
	{
		(*d)++;
		return (1);
	}
	if (c == '.')
	{
		if (*dot)
			return (0);
		*dot = 1;
		return (1);
	}
	return (0);
}

static int	check_str_valid(const char *s)
{
	int	i;
	int	d;
	int	dot;

	i = 0;
	d = 0;
	dot = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i] && i < 30)
	{
		if (!check_char_type(s[i], &d, &dot))
			return (0);
		i++;
		if (d > 15)
			return (0);
	}
	if (s[i] != '\0')
		return (0);
	if (d == 0)
		return (0);
	return (1);
}

static int	process_decimal(const char **s, double *r)
{
	const char	*tmp;

	if (**s != '.')
		return (1);
	(*s)++;
	if (!isdigit(**s))
		return (0);
	tmp = parse_fractional_part(*s, r);
	if (!tmp)
		return (0);
	*s = tmp;
	return (1);
}

static int	check_final_value(double r)
{
	if (r > 1e9 || r < -1e9)
		return (0);
	if (r != 0.0 && fabs(r) < 1e-9)
		return (0);
	return (1);
}

int	parse_float(double *out, const char *str)
{
	double		res;
	int			sign;
	const char	*tmp;

	res = 0;
	if (!str || !*str || !check_str_valid(str))
		return (0);
	sign = get_sign(&str);
	if (!isdigit(*str))
		return (0);
	tmp = parse_integer_part(str, &res);
	if (!tmp)
		return (0);
	str = tmp;
	if (!process_decimal(&str, &res))
		return (0);
	if (*str != '\0')
		return (0);
	res *= sign;
	if (!check_final_value(res))
		return (0);
	*out = res;
	return (1);
}
