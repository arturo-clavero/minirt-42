/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:53:55 by arturo            #+#    #+#             */
/*   Updated: 2024/05/19 18:52:35 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	new_ray(t_ray *ray, float pixel[2], t_mlx *mlx)
{
	ray->closest = NULL;
	create_tupple(&ray->og, 0, 0, -5);
	ray->og[X] = mlx->vp_min[X] + (mlx->pixel_size * pixel[X]);
	ray->og[Y] = mlx->vp_min[Y] - (mlx->pixel_size * pixel[Y]);
	create_vector(&ray->dir, 0, 0, 1);
}

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

void	get_pixel_color(t_mlx *mlx, float pixel[2])
{
	t_objlist	*obj;

	obj = mlx->obj_list;
	while (obj)
	{
		transform_ray(mlx->ray, obj->obj.ray, obj->obj);
		intersects_sphere(mlx->ray, obj->obj.ray, obj->obj);
		obj = obj->next;
	}
	if (mlx->ray->closest)
	{
		calc_light_vectors(mlx->light, *(mlx->ray->closest->object.ray), \
		mlx->ray->closest);
		compute_final_color(*(mlx->light), mlx->ray->closest->object, \
		mlx->ray->closest->object.ray);
		ft_mlx_pixel_put(&mlx->image, (int)pixel[X], (int)pixel[Y], \
		mlx->ray->closest->object.ray->color);
	}
}

void	init_scene(t_mlx *mlx)
{
	float		pixel[2];

	pixel[X] = -1;
	while (++pixel[X] < mlx->win_size[X])
	{
		pixel[Y] = -1;
		while (++pixel[Y] < mlx->win_size[Y])
		{
			new_ray(mlx->ray, pixel, mlx);
			get_pixel_color(mlx, pixel);
			clean_ray(mlx->ray);
		}
	}
}
