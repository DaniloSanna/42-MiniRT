
#include "minirt.h"

t_tuple	add_tuples(t_tuple one, t_tuple two)
{
	t_tuple add;

	add.x = one.x + two.x;
	add.y = one.y + two.y;
	add.z = one.z + two.z;
	add.w = one.w + two.w;
	return (add);
}

t_tuple	subtract_tuples(t_tuple one, t_tuple two)
{
	t_tuple sub;

	sub.x = one.x - two.x;
	sub.y = one.y - two.y;
	sub.z = one.z - two.z;
	sub.w = one.w - two.w;
	return (sub);
}

t_tuple	negate_tuple(t_tuple one)
{
	t_tuple neg;

	neg.x = one.x * (-1);
	neg.y = one.y * (-1);
	neg.z = one.z * (-1);
	neg.w = one.w * (-1);
	return (neg);
}

t_tuple	multiply_tuple(double scalar, t_tuple one)
{
	t_tuple mult;

	mult.x = one.x * scalar;
	mult.y = one.y * scalar;
	mult.z = one.z * scalar;
	mult.w = one.w * scalar;
	return (mult);
}

t_tuple	divide_tuple(double scalar, t_tuple one)
{
	t_tuple div;

	div.x = one.x / scalar;
	div.y = one.y / scalar;
	div.z = one.z / scalar;
	div.w = one.w / scalar;
	return (div);
}
