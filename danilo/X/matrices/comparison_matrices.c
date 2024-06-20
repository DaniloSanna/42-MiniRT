
#include "minirt.h"

int	matrix_length(double **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

int	are_equals_matrices(double **one, double **two)
{
	int	i;
	int	j;
	int	size;

	if (matrix_length(one) != matrix_length(two))
		return (0);
	size = matrix_length(one);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (!are_equals(one[i][j], two[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
