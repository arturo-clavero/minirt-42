/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:50:23 by arturo            #+#    #+#             */
/*   Updated: 2024/05/27 16:09:59 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	clean_ray(t_ray *ray)
{
	t_intersect	*temp;

	if (ray->hit == NULL)
		return ;
	while (ray->hit)
	{
		temp = ray->hit->next;
		free(ray->hit);
		ray->hit = temp;
	}
}

void	copy_ray(t_ray *dst, t_ray *src)
{
	dst->closest = NULL;
	dst->hit = NULL;
	copy_t_vec(&dst->dir, src->dir);
	copy_t_vec(&dst->og, src->og);
}

void	transform_ray(t_ray *parent, t_ray *child, t_obj obj)
{
	t_vec	temp;

	copy_ray(child, parent);
	if (obj.is_transformed == FALSE)
		return ;
	matrix_by_t_vec(obj.inv_trans, child->dir, &temp, 4);
	copy_t_vec(&child->dir, temp);
	matrix_by_t_vec(obj.inv_trans, child->og, &temp, 4);
	copy_t_vec(&child->og, temp);
}

void	new_parent_ray(t_camera cam, t_ray *ray, float pixel[2])
{
	float	offset[2];
	t_vec	target;
	t_vec	temp;

	ray->hit = NULL;
	ray->closest = NULL;
	offset[X] = (pixel[X] + 0.5) * cam.pixel_size;
	offset[Y] = (pixel[Y] + 0.5) * cam.pixel_size;
	target[X] = -cam.half_canvas[X] + offset[X];
	target[Y] = cam.half_canvas[Y] - offset[Y];
	target[Z] = 1;
	create_tupple(&ray->og, 0, 0, 0);
	substract(target, ray->og, &ray->dir);
	if (cam.default_orient == FALSE)
	{
		matrix_by_t_vec(cam.inv_trans, ray->og, &temp, 4);
		copy_t_vec(&ray->og, temp);
		matrix_by_t_vec(cam.inv_trans, ray->dir, &temp, 4);
		copy_t_vec(&ray->dir, temp);
	}
	normalize(ray->dir, &ray->dir);
}
