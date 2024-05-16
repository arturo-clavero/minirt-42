/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:50:23 by arturo            #+#    #+#             */
/*   Updated: 2024/05/16 23:12:10 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	update_closest_hit(t_intersect **closest, t_intersect *new)
{
	if (new->dist < 0)
		return ;
	if (*closest == NULL)
		*closest = new;
	else if (new->dist < (*closest)->dist)
		*closest = new;
}

void	add_intersection_to_ray(float d, t_intersect **hit, \
t_intersect **closest, t_obj sph)
{
	t_intersect	*ne;
	t_intersect	*prev;

	ne = (t_intersect *)malloc(sizeof(t_intersect));
	if (!ne)
		return ;
	ne->dist = d;
	ne->object = sph;
	ne->next = NULL;
	if (*hit == NULL)
		*hit = ne;
	else
	{
		prev = *hit;
		while (prev->next)
			prev = prev->next;
		prev->next = ne;
	}
	update_closest_hit(closest, ne);
}

int	intersects_sphere(t_ray *ray, t_obj sph)
{
	t_vec		sph_to_ray;
	t_vec		quadratic;
	float		hit;

	ray->hit = NULL;
	ray->closest = NULL;
	clear_negative_zeros_t_vec(&ray->dir);
	substract(ray->og, sph.og, &sph_to_ray);
	quadratic[A] = dot_product(ray->dir, ray->dir);
	quadratic[B] = 2 * (dot_product(ray->dir, sph_to_ray));
	quadratic[C] = dot_product(sph_to_ray, sph_to_ray) - 1;
	quadratic[DISCRIMINANT] = (quadratic[B] * quadratic[B]) \
	- (4 * quadratic[A] * quadratic[C]);
	if (quadratic[DISCRIMINANT] < 0)
		return (EXIT_FAILURE);
	hit = (-quadratic[B] - (sqrtf(quadratic[DISCRIMINANT]))) \
	/ (2 * quadratic[A]);
	add_intersection_to_ray(hit, &ray->hit, &ray->closest, sph);
	hit = (-quadratic[B] + (sqrtf(quadratic[DISCRIMINANT]))) \
	/ (2 * quadratic[A]);
	add_intersection_to_ray(hit, &ray->hit, &ray->closest, sph);
	return (EXIT_SUCCESS);
}

//void	chain_transform(t_mtrx mt[MAX_TRANSF], t_vec *vec, int total)
void	copy_ray(t_ray *dst, t_ray *src)
{
	dst->closest = NULL;
	dst->hit = NULL;
	copy_t_vec(&dst->dir, src->dir);
	copy_t_vec(&dst->og, src->og);
}
/*
void	transform_object(t_mtrx mt[MAX_TRANSF], int total, \
t_obj obj, t_ray *new_ray)
{
	t_mtrx	inv_obj;
	t_vec	temp;

	if (obj.is_transformed == TRUE)
	{
		copy_matrix(&mt[total], obj.mt_trans, 4);
		total++;
	}
	chain_transform(mt, &obj.mt_trans, total);
	obj.is_transformed = TRUE;
	invert_matrix(obj.mt_trans, &inv_obj, 4);
	matrix_by_t_vec(inv_obj, new_ray->dir, &temp, 4);
	copy_t_vec(&new_ray->dir, temp);
	matrix_by_t_vec(inv_obj, new_ray->og, &temp, 4);
	copy_t_vec(&new_ray->og, temp);
}
*/