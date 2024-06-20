
#include "minirt.h"

t_tuple	create_point(double x, double y, double z)
{
	t_tuple t;

	t.x = x;
	t.y = y;
	t.z = z;
	t.w = 1;
	return (t);
}

t_tuple	create_vector(double x, double y, double z)
{
	t_tuple t;

	t.x = x;
	t.y = y;
	t.z = z;
	t.w = 0;
	return (t);
}
