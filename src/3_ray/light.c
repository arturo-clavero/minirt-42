/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:04:22 by arturo            #+#    #+#             */
/*   Updated: 2024/05/16 14:06:20 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	calc_light_attributes(t_light *light, t_obj obj, t_ray *ray, t_vec *result)
{
	float	angle_light_normal;
	float	angle_reflect_eye;
	float	specular_factor;
	t_vec	temp;

	//vector ray color = 
	blend_colors(obj.color, light->color, &ray->color);
	//vec ambient = vector ray_color * float ambient light
	scalar_mult(ray->color, light->ambient, result);
	angle_light_normal = dot_product(light->dir, light->normal);
	if (angle_light_normal < 0) // light opp side aka SHADE
		return ;
	//diffuse color v = effect_color v * diffuse float * light_dot_normal
	scalar_mult(ray->color, (angle_light_normal * light->diffuse), &temp);
	add(*result, temp, result); //add difuse comp[onenet to final result]
	angle_reflect_eye = dot_product(light->reflect, light->eye);
	if (angle_reflect_eye <= 0) //no light back to eye vector->NO SPECULAR
		return ;
	specular_factor = pow(angle_reflect_eye, light->shine);
	//specular color v = light color v * float specular * float factor
	scalar_mult(light->color, (light->specular * specular_factor), &temp);
	add(*result, temp, result);
}

void	calc_light_values(t_light *light, t_obj obj, t_ray *ray)
{
	t_vec	temp;

	copy_t_vec(&light->point, ray->target); //P
	substract(light->point, obj.og, &light->normal); //N
	negate(ray->dir, &light->eye);//E
	substract(light->og, light->point, &light->dir);//L
	normalize(light->dir, &temp);//unsure
	copy_t_vec(&light->dir, temp);
	scalar_mult(light->normal, 2 * dot_product(ray->dir, light->normal), &temp);
	substract(ray->dir, temp, &light->reflect);
	clear_negative_zeros_t_vec(&light->reflect);
	printf("hey\n");
	calc_light_attributes(light, obj, ray, &temp);
	copy_t_vec(&ray->color, temp);
	print_t_vec(ray->color);
}
