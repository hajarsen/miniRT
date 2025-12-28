#include "parser.h"
// math2.c
t_vector	create_vect(float x, float y, float z)
{
	t_vector	vect;
	
	vect.x = x;
	vect.y = y;
	vect.z = z;

	return vect;
}

t_vector vect_add(t_vector v, t_vector w)
{
    t_vector res;

    res.x = v.x + w.x;
    res.y = v.y + w.y;
    res.z = v.z + w.z;

    return res;
}

t_vector	vect_sub(t_vector v, t_vector w)
{
    t_vector	res;

    res.x = v.x - w.x;
    res.y = v.y - w.y;
    res.z = v.z - w.z;

    return res;
}

t_vector    cross_product(t_vector v, t_vector w)
{
    t_vector res;

    res.x = v.y * w.z - v.z * w.y;
    res.y = v.z * w.x - v.x * w.z;
    res.z = v.x * w.y - v.y * w.x;

    return res;
}

float dot_product(t_vector v, t_vector w)
{
    float res;
    
    res = v.x * w.x + v.y * w.y + v.z * w.z;
    return res;
}

t_vector vect_invert(t_vector v)
{
    t_vector res;

    res.x = -v.x;
    res.y = -v.y;
    res.z = -v.z;

    return res;
}

t_vector    normalize(t_vector v)
{
    float   length;
    t_vector res;
    

    length = vector_length(v);
    if (length == 0)
        return v;
    res.x = v.x / length;
    res.y = v.y / length;
    res.z = v.z / length;

    return res;
}

t_vector	vect_scal(t_vector v, float scal)
{
	t_vector res;

	res.x = v.x * scal;
	res.y = v.y * scal;
	res.z = v.z * scal;

	return res;
}
