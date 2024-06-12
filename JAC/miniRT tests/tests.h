/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djustino <djustino@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:48:14 by jaqribei          #+#    #+#             */
/*   Updated: 2024/06/10 22:26:39 by djustino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include <stdlib.h>
# include <assert.h>
# include "libassert.h"

# define EPSILON 0.00001

# define TRUE 1
# define ALMOST 0
# define FALSE -1

typedef struct	s_tuple
{
	double		x;
	double		y;
	double		z;
	double		w;
}				t_tuple;

typedef struct	s_matrix
{
	int			size;
	double		grid[4][4];
}				t_matrix;

typedef struct	s_ray
{
	t_tuple		origin;
	t_tuple		direction;
}				t_ray;

typedef struct	s_sphere
{
	t_tuple		center;
	double		radius;
	int			id;
}				t_sphere;
typedef struct	s_discriminant
{
	double		a;
	double		b;
	double		c;
	double		discriminant;
}				t_discriminant;
typedef struct	s_intersec
{
	int			count;
	double		t[2];
}				t_intersec;



typedef struct	s_rt
{
	t_ray			ray;
	t_sphere		sphere;
	t_intersec		intersec;
	t_discriminant	discriminant;
}					t_rt;

/**
 * @brief Create a tuple
 * 
 * @param x cordinate of vector
 * @param y cordinate of vector
 * @param z cordinate of vector
 * @param w cordinate of vector
 * @return t_tuple 
 **/	
t_tuple		create_tuple(double x, double y, double z, double w);
t_tuple		create_point(double x, double y, double z);
t_tuple		create_vector(double x, double y, double z);
t_tuple		add_tuples(t_tuple a, t_tuple b);
t_tuple		subtract_tuples(t_tuple a, t_tuple b);
t_tuple		deny_tuples(t_tuple a);
t_tuple		multiply_tuples_scalar(t_tuple a, double number);
t_tuple		divide_tuple_scalar(t_tuple a, double number);
int			check_tuple_equality(t_tuple a, t_tuple b);
double		vector_magnitude(t_tuple a);
t_tuple		vector_norm(t_tuple a);
double		dot_product(t_tuple a, t_tuple b);
t_tuple		cross_product(t_tuple a, t_tuple b);
t_matrix	create_matrix(int size, double numbers[]);
void		free_matrix(t_matrix m);
int			matrix_equality(t_matrix a, t_matrix b);
t_matrix	multiply_matrices(t_matrix a, t_matrix b);
t_tuple		multiply_matrix_by_tuple(t_matrix m, t_tuple p);
t_matrix	create_matrix_identity(int size);
t_tuple		multiply_matrix_id_by_tuple(t_tuple p);
t_matrix	transpose_matrix(t_matrix m);
t_matrix	create_submatrix(t_matrix m, int row, int col);
double		calc_determinant(int size, t_matrix m);
double		calc_minor(int size, t_matrix m, int row, int col);
double		cofactor(int size, t_matrix m, int row, int col);
t_matrix	calc_inverse_matrix(t_matrix m);
t_matrix	create_translation_matrix(double x, double y, double z);
t_matrix	create_scaling_matrix(double x, double y, double z);
t_matrix	create_rotation_matrix_x(double rad);
t_matrix	create_rotation_matrix_y(double rad);
t_matrix	create_rotation_matrix_z(double rad);
t_matrix	create_shearing_matrix(double proportion[6]);
t_ray		create_ray(t_tuple origin, t_tuple direction);
t_tuple		position(t_ray ray, double t);
t_sphere	create_sphere();
t_intersec	intersect(t_ray ray, t_sphere sphere, t_discriminant discriminant);
t_discriminant	calc_discriminant(t_ray ray, t_sphere sphere);

t_tuple sphere_to_ray(t_ray ray, t_sphere sphere);

// DANILO

#define FALSE 0
#define TRUE 1

//OBJETOS
typedef struct {int x;} t_plane;
typedef struct {int x;} t_cylinder;
typedef struct {int x;} t_cube;
typedef struct {int x;} t_pyramid;

// Define a enumeração para verificar se houve hit
typedef enum {
    NO_HIT = -1,
    ONE_HIT,
    TWO_HIT
} t_did_hit;

// Define a enumeração para identificar o tipo de objeto
typedef enum {
    SPHERE,
    CUBE,
    PYRAMID,
    PLANE
} t_obj_type;

typedef struct s_intersection
{
	// DADOS DO OBJETO
	t_obj_type 				objtype;
	void					*obj;


	// DADOS DO CONTATO/INTERSECÇÃO
	t_intersec				intersect;
	double					time;
	int						hitcontact;


	// NAVEGAÇÃO PELA EXTRUTURA
	struct s_intersection	*next;
	struct s_intersection	*before;
} t_intersection;

typedef struct s_intersections
{
	struct s_intersection *start;
	struct s_intersection *end;

} t_intersections;


void *create_t_plane();
void *create_t_cylinder();
void *create_t_cube(); 
void *create_t_pyramid();
void *create_t_sphere();

t_intersection* create_intersection(t_obj_type type);
t_intersections* create_intersections();
t_intersections* get_list_intersections(int action);
int add_last_intersections(t_intersections *intersections, t_obj_type type);
t_intersection *get_last_intersec();
void *get_last_intersected_obj();

t_intersec	intersect_danilo(double time, t_ray ray, t_intersection *intersection_element);
void calc_intersection(t_ray ray, t_intersection *intersection_element, double time);
t_intersection *did_hit(t_intersections *intersections);


typedef int (*transform_operations)(double, double);
t_ray *transform(t_ray ray, t_matrix matrix, char *action);


// DELETAR
#include <string.h>

# endif