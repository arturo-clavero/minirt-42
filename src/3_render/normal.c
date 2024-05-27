/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:27:32 by arturo            #+#    #+#             */
/*   Updated: 2024/05/27 16:30:11 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	calc_sph_normal(t_light *light, t_intersect *closest)
{
	t_vec	child_point;
	t_vec	child_normal;
	t_vec	zero;
	t_mtrx	back_to_parent;

	if (closest->object.is_transformed == FALSE)
		substract(light->point, closest->object.og, &light->normal);
	else
	{
		matrix_by_t_vec(closest->object.inv_trans, \
		light->point, &child_point, 4);
		substract(child_point, closest->object.og, &child_normal);
		transpose(closest->object.inv_trans, &back_to_parent, 4);
		matrix_by_t_vec(back_to_parent, child_normal, &light->normal, 4);
		light->normal[TYPE] = VECTOR;
	}
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
	if (closest->object.is_transformed == TRUE)
		matrix_by_t_vec(closest->object.inv_trans, light->point, &point, 4);
	hit = (point[X] * point[X]) + (point[Z] * point[Z]);
	if (hit < 1 && point[Y] >= closest->object.max - EPSILON)
		create_vector(&light->normal, 0, 1, 0);
	else if (hit < 1 && point[Y] <= closest->object.min + EPSILON)
		create_vector(&light->normal, 0, -1, 0);
	else
		create_vector(&light->normal, point[X], 0, point[Z]);
	if (closest->object.is_transformed == TRUE)
	{
		transpose(closest->object.inv_trans, &back_to_parent, 4);
		matrix_by_t_vec(back_to_parent, light->normal, &temp, 4);
		copy_t_vec(&light->normal, temp);
		light->normal[TYPE] = VECTOR;
	}
	normalize(light->normal, &temp);
	copy_t_vec(&light->normal, temp);
}

void	calc_plane_normal(t_light *light, t_intersect *closest)
{
	t_vec	temp;

	create_vector(&light->normal, 0, 1, 0);
	if (closest->object.is_transformed == TRUE)
	{
		matrix_by_t_vec(closest->object.inv_trans, light->normal, &temp, 4);
		copy_t_vec(&light->normal, temp);
		normalize(light->normal, &temp);
		copy_t_vec(&light->normal, temp);
	}
}
