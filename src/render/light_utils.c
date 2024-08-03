/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:50:01 by arturo            #+#    #+#             */
/*   Updated: 2024/08/04 05:36:00 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	calc_sph_normal(t_light *light, t_intersect *closest)
{
	t_vec	child_point;
	t_vec	child_normal;
	t_vec	zero;
	t_mtrx	back_to_parent;

	matrix_by_t_vec(closest->object->inv_trans, light->point, &child_point, 4);
	substract(child_point, closest->object->og, &child_normal);
	transpose(closest->object->inv_trans, &back_to_parent, 4);
	matrix_by_t_vec(back_to_parent, child_normal, &light->normal, 4);
	light->normal[TYPE] = VECTOR;
	normalize(light->normal, &light->normal);
	if (dot_product(light->normal, light->eye) < 0)
	{
		create_vector(&zero, 0, 0, 0);
		substract(zero, light->normal, &light->normal);
	}
}

void	calc_cyl_normal(t_light *light, t_intersect *closest)
{
	float	hit;
	t_vec	point;
	t_mtrx	back_to_parent;
	t_vec	temp;

	copy_t_vec(&point, light->point);
	matrix_by_t_vec(closest->object->inv_trans, light->point, &point, 4);
	hit = (point[X] * point[X]) + (point[Z] * point[Z]);
	if (hit < 1 && point[Y] >= closest->object->max - EPSILON)
		create_vector(&light->normal, 0, 1, 0);
	else if (hit < 1 && point[Y] <= closest->object->min + EPSILON)
		create_vector(&light->normal, 0, -1, 0);
	else
		create_vector(&light->normal, point[X], 0, point[Z]);
	transpose(closest->object->inv_trans, &back_to_parent, 4);
	matrix_by_t_vec(back_to_parent, light->normal, &temp, 4);
	copy_t_vec(&light->normal, temp);
	light->normal[TYPE] = VECTOR;
	normalize(light->normal, &temp);
	copy_t_vec(&light->normal, temp);
}

void	calc_plane_normal(t_light *light, t_intersect *closest)
{
	t_vec	temp;

	create_vector(&temp, 0, 1, 0);
	matrix_by_t_vec(closest->object->inv_trans, temp, &light->normal, 4);
}

void	is_point_in_shadow(t_light *light, t_mlx *mlx)
{
	t_ray	shadow_ray;
	float	light_to_point_dist;
	t_vec	temp;

	light->is_shadow = FALSE;
	shadow_ray.hit = NULL;
	shadow_ray.closest = NULL;
	substract(light->og, light->point, &temp);
	light_to_point_dist = sqrtf(dot_product(temp, temp));
	normalize(temp, &shadow_ray.dir);
	scalar_mult(light->normal, EPSILON * 2, &temp);
	add(light->point, temp, &shadow_ray.og);
	if (find_intersection(&shadow_ray, mlx) != -1
		&& shadow_ray.closest->dist < light_to_point_dist - EPSILON)
		light->is_shadow = TRUE;
	clean_ray(&shadow_ray);
}
