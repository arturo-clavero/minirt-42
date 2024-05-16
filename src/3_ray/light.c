/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:04:22 by arturo            #+#    #+#             */
/*   Updated: 2024/05/16 22:09:36 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
}

void	calc_light_dir(t_light *light, t_ray ray)
{
	(void)ray;
	//create_tupple(&light->point, 0, 0, 0);
	//create_vector(&light->dir, 0, 0, 20);
	substract(light->og, light->point, &light->dir);
	normalize(light->dir, &light->dir);
}

void	calc_light_normal(t_light *light, t_obj sph)
{
	(void)sph;
	//create_vector(&light->normal, 0, 0, 1);
	substract(light->point, sph.og, &light->normal);
	normalize(light->normal, &light->normal);
}

void	calc_light_eye(t_light *light, t_ray ray)
{
	(void)ray;
	//create_vec(&light->eye, 0, 0, 1);
	negate(ray.dir, &light->eye);
}

void	calc_light_reflection(t_vec in, t_vec normal, t_vec *result)
{
	(void)in;
	(void)normal;
	t_vec	temp;

	print_t_vec(in);
	print_t_vec(normal);
	printf("dot_product ref: %f\n", dot_product(in, normal));
	scalar_mult(normal, (2 * dot_product(in, normal)), &temp);
	printf("temp: \n");
	print_t_vec(temp);
	substract(temp, in, result);
	clear_negative_zeros_t_vec(result);
	normalize(*result, &temp);
	copy_t_vec(result, temp);
	printf("reflection: \n");
	print_t_vec(*result);
	printf("\n");
	return ;
}

void	calc_light_vectors(t_light *light, t_ray ray, t_obj obj)
{
	copy_t_vec(&light->point, ray.target);
	calc_light_normal(light, obj);
	calc_light_eye(light, ray);
}

void	compute_final_color(t_light light, t_obj obj, t_ray *ray)
{
	t_vec	base_color;
	t_mtrx	color;
	float	dot;
	//t_vec	temp;

	blend_colors(light.color, obj.color, &base_color);
	calc_light_dir(&light, *ray);
	scalar_mult(base_color, light.ambient, &color[AMBIENT]);
	printf("ambient: \n");
	print_t_vec(color[AMBIENT]);
	printf("\n");
	dot = dot_product(light.dir, light.normal);
	if (dot < 0)
	{
		create_vector(&color[DIFFUSE], 0, 0, 0);
		create_vector(&color[SPECULAR], 0, 0, 0);
	}
	else
	{
		scalar_mult(base_color, (light.diffuse * dot), &color[DIFFUSE]);
		printf("diffuse: \n");
		print_t_vec(color[DIFFUSE]);
		printf("\n");
		calc_light_reflection(light.dir, light.normal, &light.reflect);
		dot = dot_product(light.reflect, light.eye);
		if (dot <= 0)
			create_vector(&color[SPECULAR], 0, 0, 0);
		else
		{
			printf("dot: %f\n", dot);
			printf("pow: %f\n", pow(dot, light.shine));
			scalar_mult(light.color, (pow(dot, light.shine) \
			* light.specular), &color[SPECULAR]);
			printf("specular: \n");
			print_t_vec(color[SPECULAR]);
			printf("\n");
		}
	}
	print_matrix(color, 4);
	add(color[AMBIENT], color[DIFFUSE], &ray->color);
	add(ray->color, color[SPECULAR], &ray->color);
	printf("final color:\n");
	print_t_vec(ray->color);
}

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
}
