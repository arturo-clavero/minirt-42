/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:04:22 by arturo            #+#    #+#             */
/*   Updated: 2024/08/04 05:36:43 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	calc_light_vectors(t_light *light, t_ray ray, t_intersect *closest)
{
	t_vec	temp;

	scalar_mult(ray.dir, closest->dist, &temp);
	add(ray.og, temp, &light->point);
	negate(ray.dir, &light->eye);
	normalize(light->eye, &light->eye);
	if (closest->object->type == SPHERE)
		calc_sph_normal(light, closest);
	else if (closest->object->type == PLANE)
		calc_plane_normal(light, closest);
	else if (closest->object->type == CYLINDER)
		calc_cyl_normal(light, closest);
}

void	calc_light_reflection(t_vec in, t_vec normal, t_vec *result)
{
	t_vec	temp;

	scalar_mult(normal, (2 * dot_product(in, normal)), &temp);
	substract(temp, in, result);
	normalize(*result, &temp);
	copy_t_vec(result, temp);
}

void	compute_final_color(t_light light, t_obj *obj, t_ray *ray)
{
	t_vec	base_color;
	t_vec	temp;
	float	dot;

	blend_colors(light.color, obj->color, &base_color);
	scalar_mult(base_color, light.ambient, &ray->color);
	if (light.has_diffuse == FALSE)
		return ;
	substract(light.og, light.point, &light.dir);
	normalize(light.dir, &light.dir);
	dot = dot_product(light.dir, light.normal);
	if ((dot < 0 || light.is_shadow == TRUE) && light.has_ambient == TRUE)
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
