/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:50:23 by arturo            #+#    #+#             */
/*   Updated: 2024/08/03 00:47:42 by artclave         ###   ########.fr       */
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

	if (d < 0.01)
		return ;
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
	matrix_by_t_vec(obj.inv_trans, child->dir, &temp, 4);
	copy_t_vec(&child->dir, temp);
	matrix_by_t_vec(obj.inv_trans, child->og, &temp, 4);
	copy_t_vec(&child->og, temp);
}
