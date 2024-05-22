/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:53:55 by arturo            #+#    #+#             */
/*   Updated: 2024/05/22 12:55:07 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	new_ray(t_ray *ray, float pixel[2], t_mlx *mlx)
{
	t_vec	target;

	ray->hit = NULL;
	ray->closest = NULL;
	create_tupple(&ray->og, 0, 0, -5);
	target[X] = mlx->vp_min[X] + (mlx->pixel_size * pixel[X]);
	target[Y] = mlx->vp_min[Y] - (mlx->pixel_size * pixel[Y]);
	target[Z] = mlx->vp_wall;
	target[TYPE] = POINT;
	substract(target, ray->og, &ray->dir);
	normalize(ray->dir, &ray->dir);
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

void	intersect_all(t_ray *parent_ray, t_ray *child_ray, t_obj obj)
{
	if (obj.type == SPHERE)
		intersects_sphere(parent_ray, child_ray, obj);
}

void	is_point_in_shadow(t_light *light, t_mlx *mlx)
{
	t_ray		shadow_ray;
	t_ray		child;
	float		light_ray_len;
	t_objlist	*objlist;

	light->is_shadow = FALSE;
	shadow_ray.closest = NULL;
	shadow_ray.hit = NULL;
	copy_t_vec(&shadow_ray.og, light->point);
	substract(light->og, shadow_ray.og, &shadow_ray.dir);
	light_ray_len = sqrtf(dot_product(shadow_ray.dir, shadow_ray.dir));
	objlist = mlx->obj_list;
	while (objlist)
	{
		transform_ray(&shadow_ray, &child, objlist->obj);
		intersect_all(&shadow_ray, &child, objlist->obj);
		objlist = objlist->next;
	}
	if (shadow_ray.closest && shadow_ray.closest->dist < light_ray_len)
		light->is_shadow = TRUE;
	clean_ray(&shadow_ray);
}

void	get_pixel_color(t_mlx *mlx, float pixel[2])
{
	t_objlist	*obj;

	obj = mlx->obj_list;
	while (obj)
	{
		transform_ray(mlx->ray, obj->obj.ray, obj->obj);
		intersect_all(mlx->ray, obj->obj.ray, obj->obj);
		obj = obj->next;
	}
	if (mlx->ray->closest)
	{
		calc_light_vectors(mlx->light, *(mlx->ray->closest->object.ray), \
		mlx->ray->closest, mlx->cam);
		is_point_in_shadow(mlx->light, mlx);
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
			//pixel[X] = mlx->win_size[X] / 2;
			//pixel[Y] = mlx->win_size[Y] / 2;
			new_parent_ray(mlx->cam, mlx->ray, pixel);
			get_pixel_color(mlx, pixel);
			clean_ray(mlx->ray);
		}
	}
}
