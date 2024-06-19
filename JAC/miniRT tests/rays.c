/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djustino <djustino@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 01:12:23 by jaqribei          #+#    #+#             */
/*   Updated: 2024/06/15 00:51:09 by djustino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

t_ray		create_ray(t_tuple origin, t_tuple direction) // create a ray
{
	t_ray	ray;

	ray.origin = create_point(origin.x, origin.y, origin.z);
	ray.direction = create_vector(direction.x, direction.y, direction.z);
	return(ray);
}

t_tuple		position(t_ray ray, double t) // position of the ray at time t
{
	t_tuple	position;

	position = add_tuples(ray.origin, multiply_tuples_scalar(ray.direction, t));
	return(position);
}





t_tuple sphere_to_ray(t_ray ray, t_sphere sphere)
{
	t_tuple	result;

	result = subtract_tuples(ray.origin, sphere.center);
	return(result);
}

t_discriminant	calc_discriminant(t_ray ray, t_sphere sphere)
{
	t_discriminant	discriminant;
	
	discriminant.a = dot_product(ray.direction, ray.direction);
	discriminant.b = 2 * dot_product(ray.direction, sphere_to_ray(ray, sphere));
	discriminant.c = dot_product(sphere_to_ray(ray, sphere), sphere_to_ray(ray, sphere)) - 1;
	discriminant.discriminant = pow(discriminant.b, 2) - (4 * discriminant.a * discriminant.c);
	return(discriminant);
}

t_intersec	intersect(t_ray ray, t_sphere sphere, t_discriminant discriminant)
{
	double				t1;
	double				t2;
	t_intersec			intersec;

	discriminant = calc_discriminant(ray, sphere);
	if (discriminant.discriminant < 0)
		return(intersec);
	t1 = (-1.0 * discriminant.b - sqrt(discriminant.discriminant)) / (2.0 * discriminant.a);
	t2 = (-1.0 * discriminant.b + sqrt(discriminant.discriminant)) / (2.0 * discriminant.a);
	intersec.t[0] = t1;
	intersec.t[1] = t2;
	intersec.count = 2;
	return(intersec);
}

void *create_t_plane(){}
void *create_t_cylinder(){}
void *create_t_cube(){} 
void *create_t_pyramid(){}

t_sphere create_sphere(double x, double y, double z, double w, double radius) {
    t_sphere sphere;

    sphere.center.x = x;
    sphere.center.y = y;
    sphere.center.z = z;
    sphere.center.w = w;
    sphere.radius = radius;
    return(sphere);
}

void* create_t_sphere() {
    t_sphere* sphere = (t_sphere*)malloc(sizeof(t_sphere));
    if (sphere == NULL) {
        fprintf(stderr, "Erro ao alocar memória para t_sphere\n");
        return NULL;
    }
    sphere->center = create_point(0, 0, 0);
    sphere->radius = 1.0;
    return(void*)sphere; // Converte o ponteiro de t_sphere para void*
}

t_intersection* create_intersection(t_obj_type type, int idx) {
    t_intersection* intersection = (t_intersection*)malloc(sizeof(t_intersection));
    if (intersection == NULL) {
        printf("\nErro ao alocar memória para t_intersection\n");
        return NULL;
    }

    // Define o id da intersecção
	intersection->id = idx;

    // Define o tipo de objeto
    intersection->objtype = type;

    // Inicializa o objeto específico com base no tipo
	if(type == CUBE){
		intersection->obj = create_t_cube();
	}else if(type == PYRAMID){
		intersection->obj = create_t_pyramid();
	}else if(type == PLANE){
		intersection->obj = create_t_plane();
	}else if(type == SPHERE){
		intersection->obj = create_t_sphere();
	}else{
		printf("\nTipo de objeto inválido em init_intersection\n");
		free(intersection);
		return NULL;
	}

    // Inicializa outros campos, se houver
    intersection->time = 0.0;
    intersection->next = NULL;
    intersection->before = NULL;

	return intersection;
}

t_intersections* create_intersections() {
    t_intersections* intersections = (t_intersections*)malloc(sizeof(t_intersections));
    if (!intersections)
        return NULL;

    // Inicializa os ponteiros start e end como NULL
    intersections->start = NULL;
    intersections->end = NULL;

    return (intersections);
}

void *get_last_intersected_obj(){

	t_intersections* intersections;

	intersections = get_list_intersections(1);
	return(intersections->end->obj);
}

t_intersection *get_last_intersec(){

	t_intersections* intersections;

	intersections = get_list_intersections(1);
	return(intersections->end);
}

t_intersections* get_list_intersections(int action) {
    static t_intersections* intersections;

    if (action == 0){
		intersections = create_intersections();
		if (!intersections)
			return NULL;
		else
			return intersections;
	}
	if (action > 0)
        return intersections;

    free(intersections);
    intersections = NULL;
    return(NULL);
}

int add_last_intersections(t_intersections *intersections, t_obj_type type, int id, void *obj){
	t_intersection *node;

	if(!obj)
		node = create_intersection(type, id);
	else
		node->obj = obj;

	if(!node){
		printf("\n FALSE - add_last_intersections\n");
		return(FALSE);
	}
	if (intersections->start == NULL) {
        intersections->start = node;
        intersections->end = node;
    } else {
        intersections->end->next = node;
        node->before = intersections->end;
        intersections->end = node;
    }
	return(TRUE);
}


t_discriminant calc_discriminant_danilo(t_tuple position, t_ray ray, t_sphere sphere) {
    t_discriminant discriminant;
    t_tuple sphere_to_position = subtract_tuples(ray.origin, sphere.center);

    discriminant.a = dot_product(ray.direction, ray.direction);
    discriminant.b = 2 * dot_product(ray.direction, sphere_to_position);
    discriminant.c = dot_product(sphere_to_position, sphere_to_position) - (sphere.radius * sphere.radius);
    discriminant.discriminant = pow(discriminant.b, 2) - (4 * discriminant.a * discriminant.c);
    return discriminant;
}


t_intersec	intersect_danilo(double time, t_ray ray, t_intersection *intersection_element){
	double				t1, t2;
	t_intersec			intersec;
	t_discriminant		discriminant;
	t_tuple 			ray_position;
	

	// if(intersection_element->objtype == SPHERE)
		t_sphere sphere = *(t_sphere *)(intersection_element->obj);

	ray_position = position(ray, time);
	discriminant = calc_discriminant_danilo(ray_position, ray, sphere);
	if (discriminant.discriminant < 0)
	{
		intersection_element->hitcontact = NO_HIT;
		return(intersec);
	}
	if(discriminant.discriminant == 0)
		intersection_element->hitcontact = ONE_HIT;
	if(discriminant.discriminant > 0)
		intersection_element->hitcontact = TWO_HIT;

	intersec.t[0] = (-1.0 * discriminant.b - sqrt(discriminant.discriminant)) / (2.0 * discriminant.a);
	intersec.t[1] = (-1.0 * discriminant.b + sqrt(discriminant.discriminant)) / (2.0 * discriminant.a);
	intersec.count = 2;
	return(intersec);
}

void calc_intersection(t_ray ray, t_intersection *intersection_element, double time){
	intersection_element->time = time;
	intersection_element->intersect = intersect_danilo(time, ray, intersection_element);
}


t_intersection *did_hit(t_intersections *intersections){
    t_intersection *loop = intersections->start;
    t_intersection *hitted_obj = NULL;
    double hitted_t = 50000000000000000000000000000000000000000.00;  // Inicializado para o máximo valor de double

    while(loop) {
        if(loop->hitcontact != NO_HIT) {
            double min_t = 50000000000000000000000000000000000000000.00;
            if (loop->hitcontact == ONE_HIT) {
                min_t = loop->intersect.t[0];  // Apenas um hit válido
            } else if (loop->hitcontact == TWO_HIT) {
                min_t = fmin(loop->intersect.t[0], loop->intersect.t[1]);  // Dois hits válidos
            }
            if(min_t >= 0 && min_t < hitted_t) {
                hitted_obj = loop;
                hitted_t = min_t;
            }
        }
        loop = loop->next;
    }

    return hitted_obj;  // Retorna NULL se nenhum objeto foi atualizado
}


// Função que recebe dois arrays e uma função como argumentos
// t_ray *transform(t_ray *ray, t_matrix matrix, char *action) {

// 	t_ray *transformation;

// 	transformation = (t_ray*)malloc(sizeof(t_ray));
// 	if(!transformation)
// 		return(NULL);
	
// 	// Translação
// 	if(ft_strcmp(action, "translate")){
// 		transformation->origin = multiply_matrix_by_tuple(matrix, transformation->origin);
// 		transformation->direction = multiply_matrix_by_tuple(matrix, transformation->direction);
// 	}

// 	return(transformation);
// }


// Função que recebe dois arrays e uma função como argumentos
t_ray *transform_ray_do_matrix_in(t_ray *ray, t_tuple matrizdata, double *extravalues, e_actiontransform action) {

	t_ray *transformation;
	t_matrix matrix;

	matrix = create_matrix_identity(4);
	transformation = create_ray_pointer(create_blanktuple(), create_blanktuple());
	if(!transformation)
		return(NULL);

	if(action == TRANSLATION){
		matrix = create_translation_matrix(matrizdata.x, matrizdata.y, matrizdata.z);
	}else if(action == SCALING){
		matrix = create_scaling_matrix(matrizdata.x, matrizdata.y, matrizdata.z);
		transformation->direction = transform_formula_danilo(ray->direction, matrix);
	}else if(action == ROTATATE_X){
		matrix = create_rotation_matrix_x(extravalues[0]);
	}else if(action == ROTATATE_Y){
		matrix = create_rotation_matrix_y(extravalues[0]);
	}else if(action == ROTATATE_Z){
		matrix = create_rotation_matrix_z(extravalues[0]);
	}else if(action == SHEARING){
		matrix = create_shearing_matrix(extravalues);
	}else{
		return(free(transformation), NULL);
	}

	transformation->origin = transform_formula_danilo(ray->origin, matrix);
	return(transformation);
}

t_ray *transform_ray_do_matrix_out(t_ray *ray, t_matrix matrix, e_actiontransform action) {

	t_ray *transformation;
	transformation = create_ray_pointer(create_blanktuple(), create_blanktuple());

	if(!transformation)
		return(NULL);
	if(action == SCALING)
		transformation->direction = transform_formula_danilo(ray->direction, matrix);
	transformation->origin = transform_formula_danilo(ray->origin, matrix);
	return(transformation);
}

t_tuple transform_formula_danilo(t_tuple t, t_matrix m) {
    t_tuple result;
	result.x = t.x * m.grid[0][0] + t.y * m.grid[0][1] + t.z * m.grid[0][2] + m.grid[0][3];
    result.y = t.x * m.grid[1][0] + t.y * m.grid[1][1] + t.z * m.grid[1][2] + m.grid[1][3];
    result.z = t.x * m.grid[2][0] + t.y * m.grid[2][1] + t.z * m.grid[2][2] + m.grid[2][3];
	result.w = t.w;
    return result;
}


t_tuple create_blanktuple(){
	
	t_tuple retur;

	retur.x = 0;
	retur.y = 0;
	retur.z = 0;
	retur.w = 0;

	return(retur);
}

t_ray *create_ray_pointer(t_tuple origin, t_tuple direction) // create a ray
{
	t_ray	*ray;

	ray = (t_ray*)malloc(sizeof(t_ray));
    if (!ray)
		return(NULL);
	ray->origin = create_point(origin.x, origin.y, origin.z);
	ray->direction = create_vector(direction.x, direction.y, direction.z);
	return(ray);
}


int add_last_intersection_object(t_intersections *intersections, t_obj_type type, void *obj, int id){
	t_intersection *node;

	node = create_intersection(type, id);

	if(!node){
		printf("\n FALSE - add_last_intersections\n");
		return(FALSE);
	}
	if (intersections->start == NULL) {
        intersections->start = node;
        intersections->end = node;
    } else {
        intersections->end->next = node;
        node->before = intersections->end;
        intersections->end = node;
    }
	return(TRUE);
}



t_sphere *create_t_sphere (t_sphere *obj){
	t_sphere	*sphere;
	
	sphere = (t_sphere*)malloc(sizeof(t_sphere));
	if(!sphere)
		return(NULL);

	sphere->center.x = obj->center.x;
	sphere->center.y = obj->center.y;
	sphere->center.z = obj->center.z;
	sphere->center.w = obj->center.w;
	sphere->radius = obj->radius;
	sphere->id = obj->id;
	return(sphere);
}

