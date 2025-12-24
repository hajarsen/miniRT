#include "parser.h"

double ft_min(double a, double b)
{
    if (a < b) 
        return a;
    return b;
}

double ft_max(double a, double b)
{
    if (a > b)
        return a;
    return b;
}

double ft_abs(double x)
{
    if (x >= 0)
        return (x);
    return (-x);
}
double ft_power(double base, int exp)
{
    double result;

    if (exp < 0)
        return 0;

    if (exp == 0)
        return 1;
    result = 1;
    while (exp > 0)
    {
        result *= base;
        exp--;
    }
    return result;
}

double vector_length(t_vector v)
{
    double vec_len;

    vec_len = sqrt(ft_power(v.x, 2) + ft_power(v.y, 2) + ft_power(v.z, 2));
    return vec_len;
}

bool	float_eq(double a, double b)
{
	double	diff;
	double	max_abs;

	diff = ft_abs(a - b);
	max_abs = ft_max(ft_abs(a), ft_abs(b));
	return (diff < EPSILON * max_abs);
}

bool in_interval(double value, double min_val, double max_val)
{
    return (value >= min_val && value <= max_val);
}


bool is_normalized(t_vector v)
{
    return float_eq(vector_length(v), 1.0);
}
