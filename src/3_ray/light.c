/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:04:22 by arturo            #+#    #+#             */
/*   Updated: 2024/05/16 17:22:55 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	calc_light_attributes(t_light light, t_obj obj, t_ray ray, t_vec *result)
{
	float	angle_light_normal;
	float	angle_reflect_eye;
	float	specular_factor;
	t_vec	temp;

	//vector ray color = 
	blend_colors(obj.color, light.color, &ray.color);
	//printf("BASE COLOR (light and obj): \n");
	//print_t_vec(ray.color);
	//printf("\n");
	//vec ambient = vector ray_color * float ambient light
	scalar_mult(ray.color, light.ambient, result);
	//printf("multiply blended colro by ambient ration of %.2f\n", light.ambient);
	//print_t_vec(*result);
	//printf("\n");
	angle_light_normal = dot_product(light.normal, light.dir);
	//printf("angle_light_dir and _normal: %f\n", angle_light_normal);
	if (angle_light_normal < 0.0) // light opp side aka SHADE
		return ;
	//diffuse color v = effect_color v * diffuse float * light_dot_normal
	//printf("multiply BASE COLOR * (angle_light_normal * diffuse fact)\n");
	scalar_mult(ray.color, (angle_light_normal * light.diffuse), &temp);
	//print_t_vec(temp);
	//printf("\n");
	add(*result, temp, result); //add difuse comp[onenet to final result]
	angle_reflect_eye = dot_product(light.reflect, light.eye);
	if (angle_reflect_eye <= 0) //no light back to eye vector->NO SPECULAR
		return ;
	specular_factor = pow(angle_reflect_eye, light.shine);
	//specular color v = light color v * float specular * float factor
	scalar_mult(light.color, (light.specular * specular_factor), &temp);
	add(*result, temp, result);
}

void	calc_light_values(t_light *light, t_obj obj, t_ray *ray)
{
	t_vec	temp;

	copy_t_vec(&light->point, ray->target); //P
	substract(light->point, obj.og, &light->normal); //N
	normalize(light->normal, &temp);
	copy_t_vec(&light->normal, temp);
	negate(ray->dir, &light->eye);//E
	substract(light->point, light->og, &light->dir);//L
	normalize(light->dir, &temp);
	copy_t_vec(&light->dir, temp);
	scalar_mult(light->normal, 2 * dot_product(light->dir, light->normal), &temp);
	substract(light->dir, temp, &light->reflect);
	clear_negative_zeros_t_vec(&light->reflect);
	/*TESTING DELETE
	create_vector(&light->point, 0, 0, 0);
	create_vector(&light->eye, 0, 0, -1);
	create_vector(&light->normal, 0, 0, -1);
	create_vector(&light->og, 0, 0, -10);
	create_vector(&light->color, 1, 1, 1);
	substract(light->og, light->point, &light->dir);//L
	normalize(light->dir, &light->dir);
	negate(light->eye, &ray->dir);
	scalar_mult(light->normal, 2 * dot_product(ray->dir, light->normal), &temp);
	substract(ray->dir, temp, &light->reflect);
	clear_negative_zeros_t_vec(&light->reflect);
	printf("light dir:");
	print_t_vec(light->dir);
	printf("eye: ");
	print_t_vec(light->eye);
	printf("ray dir: ");
	print_t_vec(ray->dir);
	printf("reflect: ");
	print_t_vec(light->reflect);
	printf("normal: ");
	print_t_vec(light->normal);
	printf("point: ");
	print_t_vec(light->point);
	//normalize(light->dir, &light->dir);
	//END DELETE
	light->ambient = 0.1;
	light->specular = 0.9;
	light->diffuse = 0.9;
	light->shine = 200;*/
	calc_light_attributes(*light, obj, *ray, &temp);
	copy_t_vec(&ray->color, temp);
//	print_t_vec(ray->color);
}
