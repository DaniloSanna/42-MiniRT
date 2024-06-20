
#include "minirt.h"

int	are_equals(double one, double two)
{
	if (fabs(one - two) < EPSILON)
		return (1);
	return (0);
}

int	are_equals_tuples(t_tuple one, t_tuple two)
{
	if(are_equals(one.x, two.x) && are_equals(one.y, two.y) \
		&& are_equals(one.z, two.z) && are_equals(one.w, two.w))
		return (1);
	return (0);
}
