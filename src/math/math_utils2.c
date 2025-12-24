#include "parser.h"

float distance(t_vector v, t_vector w)
{
    t_vector res;

    res.x = w.x - v.x;
    res.y = w.y - v.y;
    res.z = w.z - v.z;

    return (sqrt(ft_power(res.x, 2) + ft_power(res.y, 2) + ft_power(res.z, 2)));
}

t_vector    reflect_vect(t_vector v, t_vector n)
{
    t_vector res;

    res = vect_sub(v, vect_scal(n, 2 * dot_product(v, n)));
    return res;
}

t_vector   refract_vect(t_vector v, t_vector n, float eta)
{
    float cos_inc;
    float cos_refr;
    t_vector res;
    
    cos_inc = dot_product(v, n);
    cos_refr = sqrt(1 - ft_power(eta, 2) * (1 - ft_power(cos_inc, 2)));
    res = vect_add(vect_scal(v, eta), vect_scal(n, (eta * cos_inc - cos_refr)));
    return (normalize(res));

}
