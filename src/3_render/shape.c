/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:53:05 by arturo            #+#    #+#             */
/*   Updated: 2024/05/23 11:17:27 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	intersects_sphere(t_ray *parent_ray, t_ray *child_ray, t_obj sph)
{
	t_vec		sph_to_ray;
	t_vec		quadratic;
	float		hit;

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

void	intersects_plane(t_ray *parent_ray, t_ray *child_ray, t_obj pl)
{
	float	hit;

	if (fabs(child_ray->dir[Y]) < EPSILON)
		return ;
	hit = -child_ray->og[Y] / child_ray->dir[Y];
	//if (hit > 0.01)
		add_intersection_to_ray(hit, &parent_ray->hit, &parent_ray->closest, pl);
}
