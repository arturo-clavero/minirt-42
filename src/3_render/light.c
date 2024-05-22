/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:04:22 by arturo            #+#    #+#             */
/*   Updated: 2024/05/22 15:09:12 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

//TODO!
void	calc_light_normal(t_camera cam, t_light *light, t_intersect *closest)
{
	
//	t_vec	obj_point;
//	t_vec	obj_normal;
//	t_mtrx	back_to_world;

	//if (closest->object.is_transformed == FALSE)
//	t_vec temp;
	(void)cam;
//	matrix_by_t_vec(closest->object.inv_trans, closest->object.og, &temp, 4);
//	copy_t_vec(&closest->object.og, temp);
	//printf("sphere og>\n");
	//print_t_vec(closest->object.og);
//	matrix_by_t_vec(closest->object.inv_trans, light->point, &temp, 4);
//	copy_t_vec(&light->point, temp);
	//printf("point hit \n");
	//print_t_vec(light->point);
	substract(light->point, closest->object.og, &light->normal);
	
	/*matrix_by_t_vec(closest->object.inv_trans, light->normal, &temp, 4);
	copy_t_vec(&light->normal, temp);
	matrix_by_t_vec(cam.inv_trans, light->normal, &temp, 4);
	copy_t_vec(&light->normal, temp);*/
	//printf("before normalize> \n");
	//print_t_vec(light->normal);
	/*else
	{
		matrix_by_t_vec(closest->object.inv_trans, light->point, &obj_point, 4);
		substract(obj_point, closest->object.og, &obj_normal);
		transpose(closest->object.inv_trans, &back_to_world, 4);
		matrix_by_t_vec(back_to_world, obj_normal, &light->normal, 4);
		light->normal[TYPE] = VECTOR;
		print_t_vec(light->normal);
		printf("\n");
	}*/
	normalize(light->normal, &light->normal);
//	printf("after normalize> \n");
//	print_t_vec(light->normal);
//	/*if (dot_product(light->normal, light->eye) < 0) //if inside a sphere
	//{
	//	substract(closest->object.og, light->normal, &light->normal);
	//	light->normal[TYPE] = VECTOR;
	//}*/
}

void	calc_light_vectors(t_light *light, t_ray ray, t_intersect *closest, t_camera cam)
{
	t_vec	temp;

	scalar_mult(ray.dir, closest->dist, &temp);
	add(ray.og, temp, &light->point);
	negate(ray.dir, &light->eye);
	normalize(light->eye, &light->eye);
	calc_light_normal(cam, light, closest);
	//adding an offset to avoid shadow acne
	scalar_mult(light->normal, EPSILON, &temp);
	add(light->point, temp, &light->point);
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
	if (dot < 0 || light.is_shadow == TRUE)
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
