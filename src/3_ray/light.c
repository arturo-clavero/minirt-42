/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:04:22 by arturo            #+#    #+#             */
/*   Updated: 2024/05/16 23:09:07 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	calc_light_vectors(t_light *light, t_ray ray, t_obj obj)
{
	t_vec	temp;

	scalar_mult(ray.dir, ray.closest->dist, &temp);
	add(ray.og, temp, &light->point);
	substract(light->point, obj.og, &light->normal);
	normalize(light->normal, &light->normal);
	negate(ray.dir, &light->eye);
	normalize(light->eye, &light->eye);
}

void	calc_light_reflection(t_vec in, t_vec normal, t_vec *result)
{
	t_vec	temp;

	scalar_mult(normal, (2 * dot_product(in, normal)), &temp);
	substract(temp, in, result);
	clear_negative_zeros_t_vec(result);
	normalize(*result, &temp);
	copy_t_vec(result, temp);
}

void	compute_final_color(t_light light, t_obj obj, t_ray *ray)
{
	t_vec	base_color;
	t_vec	temp;
	float	dot;

	blend_colors(light.color, obj.color, &base_color);
	substract(light.og, light.point, &light.dir);
	normalize(light.dir, &light.dir);
	scalar_mult(base_color, light.ambient, &ray->color);
	dot = dot_product(light.dir, light.normal);
	if (dot < 0)
		return ;
	scalar_mult(base_color, (light.diffuse * dot), &temp);
	add(ray->color, temp, &ray->color);
	calc_light_reflection(light.dir, light.normal, &light.reflect);
	dot = dot_product(light.reflect, light.eye);
	if (dot <= 0)
		return ;
	scalar_mult(light.color, (pow(dot, light.shine) * light.specular), &temp);
	add(ray->color, temp, &ray->color);
}

/*
void	initial_light_values(t_light *light)
{
	create_tupple(&light->og, 0, 0, -10);
	light->ambient = 0.1;
	light->diffuse = 0.5;
	light->specular = 0.5;
	light->shine = 200;
	create_vector(&light->color, 1, 1, 1);
}

void	create_ray(t_ray *ray)
{
	create_tupple(&ray->og, 0, 0, -5);
	create_tupple(&ray->target, 0, 0, 0);
	substract(ray->target, ray->og, &ray->dir);
	//normalize(ray->dir, &ray->dir);
}

void	create_sphere(t_obj *sph)
{
	sph->type = SPHERE;
	create_tupple(&sph->og, 0, 0, 0);
	sph->r = 1;
	sph->is_transformed = FALSE;
	create_vector(&sph->color, 1, 1, 1);
}*/
/*
int	main(void)
{
	t_light	light;
	t_ray	ray;
	t_obj	sph;

	create_ray(&ray);
	create_sphere(&sph);
	initial_light_values(&light);
	calc_light_vectors(&light, ray, sph);
	//TESTING
	light.ambient = 0.1;
	light.diffuse = 0.9;
	light.specular = 0.9;
	light.shine = 200;
	create_tupple(&light.point, 0, 0, 0);
	create_vector(&light.eye, 0, 0, -1);
	create_vector(&light.normal, 0, 0, -1);
	create_vector(&light.og, 0, 0, 10);
	create_vector(&light.color, 1, 1, 1);
	//END TESTING
	compute_final_color(light, sph, &ray);
	print_t_vec(ray.color);
}
*/