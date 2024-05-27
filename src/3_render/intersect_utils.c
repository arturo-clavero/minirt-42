/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:30:50 by arturo            #+#    #+#             */
/*   Updated: 2024/05/27 15:31:54 by arturo           ###   ########.fr       */
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

int	find_intersection(t_ray *parent_ray, t_mlx *mlx)
{
	t_objlist	*list;
	t_ray		child_ray;

	list = mlx->obj_list;
	while (list)
	{
		transform_ray(parent_ray, &child_ray, list->obj);
		if (list->obj.type == SPHERE)
			intersects_sphere(parent_ray, &child_ray, list->obj);
		else if (list->obj.type == PLANE)
			intersects_plane(parent_ray, &child_ray, list->obj);
		else if (list->obj.type == CYLINDER)
		{
			intersects_cylinder_body(parent_ray, &child_ray, list->obj);
			intersects_cylinder_caps(parent_ray, &child_ray, list->obj);
		}
		list = list->next;
	}
	if (parent_ray->closest)
		return (TRUE);
	return (FALSE);
}
