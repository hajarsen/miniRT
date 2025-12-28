/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajar <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:27:03 by hajar             #+#    #+#             */
/*   Updated: 2025/12/28 18:29:07 by hajar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

double	ft_min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

double	ft_max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double	ft_abs(double x)
{
	if (x >= 0)
		return (x);
	return (-x);
}

double	ft_power(double base, int exp)
{
	double	result;

	if (exp < 0)
		return (0);
	if (exp == 0)
		return (1);
	result = 1;
	while (exp > 0)
	{
		result *= base;
		exp--;
	}
	return (result);
}

bool	float_eq(double a, double b)
{
	double	diff;
	double	max_abs;

	diff = ft_abs(a - b);
	max_abs = ft_max(ft_abs(a), ft_abs(b));
	return (diff < EPSILON * max_abs);
}
