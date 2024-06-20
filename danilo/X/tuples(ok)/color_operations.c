
#include "minirt.h"

t_color	add_colors(t_color one, t_color two)
{
	t_color color;

	color.red = one.red + two.red;
	color.green = one.green + two.green;
	color.blue = one.blue + two.blue;
	if (color.red > 255)
		color.red = 255;
	if (color.green > 255)
		color.green = 255;
	if (color.blue > 255)
		color.blue = 255;
	return (color);
}

t_color	subtract_colors(t_color one, t_color two)
{
	t_color color;

	color.red = one.red - two.red;
	color.green = one.green - two.green;
	color.blue = one.blue - two.blue;

	if (color.red < 0)
		color.red = 0;
	if (color.green < 0)
		color.green = 0;
	if (color.blue < 0)
		color.blue = 0;
	return (color);
}

t_color	multiply_color_by_scalar(double scalar, t_color one)
{
	t_color color;

	if (scalar > 1)
		scalar = 1;
	if (scalar < 0)
		scalar = 0;
	color.red = one.red * scalar;
	color.green = one.green * scalar;
	color.blue = one.blue * scalar;
	return (color);
}

t_color	multiply_colors(t_color one, t_color two)
{
	t_color color;
	int	red;
	int	green;
	int	blue;

	color.red = one.red * two.red / 255;
	color.green = one.green * two.green / 255;
	color.blue = one.blue * two.blue / 255;
	return (color);
}
