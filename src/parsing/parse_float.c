/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:51:06 by hsennane          #+#    #+#             */
/*   Updated: 2025/12/28 18:51:09 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

const char	*parse_integer_part(const char *str, double *result)
{
	while (isdigit(*str))
	{
		if (*result > DBL_MAX / 10.0 || (*result == DBL_MAX / 10.0 && (*str
					- '0') > fmod(DBL_MAX, 10.0)))
			return (NULL);
		*result = *result * 10 + (*str - '0');
		str++;
	}
	return (str);
}

const char	*parse_fractional_part(const char *str, double *result)
{
	double	divisor;

	divisor = 0.1;
	while (isdigit(*str))
	{
		if (DBL_MAX - (*result) < (*str - '0') * divisor)
			return (NULL);
		*result += (*str - '0') * divisor;
		divisor *= 0.1;
		str++;
	}
	return (str);
}

static int	ft_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

int	parse_float(double *out, const char *str)
{
	double	result;
	int		sign;

	result = 0;
	if (!str || *str == '\0')
		return (0);
	sign = ft_sign(&str);
	if (!isdigit(*str))
		return (0);
	str = parse_integer_part(str, &result);
	if (!str)
		return (0);
	if (*str == '.')
	{
		str++;
		if (!isdigit(*str))
			return (0);
		str = parse_fractional_part(str, &result);
		if (!str)
			return (0);
	}
	if (*str != '\0')
		return (0);
	*out = result * sign;
	return (1);
}
