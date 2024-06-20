

#include "minirt.h"

double	calculate_vector_magnitude(t_tuple one)
{
	double mag;
	double x;
	double y;
	double z;
	double w;

	x = pow(one.x, 2);
	y = pow(one.y, 2);
	z = pow(one.z, 2);
	w = pow(one.w, 2);

	mag = sqrt(x + y + z + w);
	return (mag);
}

t_tuple	normalize_vector(t_tuple one)
{
	double mag;
	t_tuple normalizer;

	mag = calculate_vector_magnitude(one);
	normalizer = divide_tuple(mag, one);
	return (normalizer);
}

double	calculate_dot_product(t_tuple one, t_tuple two)
{
	double dot;
	double x;
	double y;
	double z;
	double w;

	x = one.x * two.x;
	y = one.y * two.y;
	z = one.z * two.z;
	w = one.w * two.w;
	dot = (x + y + z + w);
	return (dot);
}

t_tuple	calculate_cross_product(t_tuple one, t_tuple two)
{
	t_tuple cross;

	cross.x = one.y * two.z - one.z * two.y;
	cross.y = one.z * two.x - one.x * two.z;
	cross.z = one.x * two.y - one.y * two.x;
	cross.w = 0;
	return (cross);
}
