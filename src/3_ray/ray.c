/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:50:23 by arturo            #+#    #+#             */
/*   Updated: 2024/05/17 13:30:52 by arturo           ###   ########.fr       */
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

int	intersects_sphere(t_ray *parent_ray, t_ray *child_ray, t_obj sph)
{
	t_vec		sph_to_ray;
	t_vec		quadratic;
	float		hit;

	clear_negative_zeros_t_vec(&child_ray->dir);
	substract(child_ray->og, sph.og, &sph_to_ray);
	quadratic[A] = dot_product(child_ray->dir, child_ray->dir);
	quadratic[B] = 2 * (dot_product(child_ray->dir, sph_to_ray));
	quadratic[C] = dot_product(sph_to_ray, sph_to_ray) - 1;
	quadratic[DISCRIMINANT] = (quadratic[B] * quadratic[B]) \
	- (4 * quadratic[A] * quadratic[C]);
	if (quadratic[DISCRIMINANT] < 0)
		return (EXIT_FAILURE);
	hit = (-quadratic[B] - (sqrtf(quadratic[DISCRIMINANT]))) \
	/ (2 * quadratic[A]);
	add_intersection_to_ray(hit, &parent_ray->hit, &parent_ray->closest, sph);
	hit = (-quadratic[B] + (sqrtf(quadratic[DISCRIMINANT]))) \
	/ (2 * quadratic[A]);
	add_intersection_to_ray(hit, &parent_ray->hit, &parent_ray->closest, sph);
	return (EXIT_SUCCESS);
}

//void	chain_transform(t_mtrx mt[MAX_TRANSF], t_vec *vec, int total)
void	copy_ray(t_ray *dst, t_ray *src)
{
	dst->closest = NULL;
	dst->hit = NULL;
	copy_t_vec(&dst->dir, src->dir);
	copy_t_vec(&dst->og, src->og);
	copy_t_vec(&dst->target, src->target);
}

void	transform_object(t_mtrx mt[MAX_TRANSF], int total, \
t_obj *obj)
{
	t_mtrx	temp_mt;
	t_mtrx	new_trans;

	chain_transform(mt, &new_trans, total);
	if (obj->is_transformed == TRUE)
	{
		matrix_by_matrix(new_trans, obj->mt_trans, &temp_mt, 4);
		copy_matrix(&new_trans, temp_mt, 4);
	}
	copy_matrix(&obj->mt_trans, new_trans, 4);
	obj->is_transformed = TRUE;
	invert_matrix(obj->mt_trans, &obj->inv_trans, 4);
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
	matrix_by_t_vec(obj.inv_trans, child->target, &temp, 4);
	copy_t_vec(&child->target, temp);
	return ;
	/*matrix_by_t_vec(obj.mt_trans, child->dir, &child->dir, 4);
	negate(child->dir, &child->dir);
	matrix_by_t_vec(obj.mt_trans, child->og, &child->og, 4);
	negate(child->dir, &child->og);*/
}
