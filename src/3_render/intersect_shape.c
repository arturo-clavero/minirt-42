/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:53:05 by arturo            #+#    #+#             */
/*   Updated: 2024/05/27 15:34:04 by arturo           ###   ########.fr       */
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
	add_intersection_to_ray(hit, &parent_ray->hit, &parent_ray->closest, pl);
}

void	intersects_cylinder_body(t_ray *parent, t_ray *child, t_obj cyl)
{
	t_vec		quadratic;
	float		hit;
	float		y;

	quadratic[A] = (child->dir[X] * child->dir[X]) + \
	(child->dir[Z] * child->dir[Z]);
	if (quadratic[A] < 0.001 && quadratic[A] > -0.009)
		return ;
	quadratic[B] = (2 * child->og[X] * child->dir[X]) + \
	(2 * child->og[Z] * child->dir[Z]);
	quadratic[C] = (child->og[X] * child->og[X]) + \
	(child->og[Z] * child->og[Z]) - 1;
	quadratic[DISCRIMINANT] = (quadratic[B] * quadratic[B]) \
	- (4 * quadratic[A] * quadratic[C]);
	if (quadratic[DISCRIMINANT] < 0.001)
		return ;
	hit = (-quadratic[B] - (sqrtf(quadratic[DISCRIMINANT]))) \
	/ (2 * quadratic[A]);
	y = child->og[Y] + hit * child->dir[Y];
	if (y > cyl.min && y < cyl.max)
		add_intersection_to_ray(hit, &parent->hit, &parent->closest, cyl);
	hit = (-quadratic[B] + (sqrtf(quadratic[DISCRIMINANT]))) \
	/ (2 * quadratic[A]);
	y = child->og[Y] + hit * child->dir[Y];
	if (y > cyl.min && y < cyl.max)
		add_intersection_to_ray(hit, &parent->hit, &parent->closest, cyl);
}

void	intersects_cylinder_caps(t_ray *parent, t_ray *child, t_obj cyl)
{
	float	hit;
	float	x;
	float	z;

	if (child->dir[Y] < 0.001 && child->dir[Y] > -0.999)
		return ;
	hit = (cyl.min - child->og[Y]) / child->dir[Y];
	x = child->og[X] + hit * child->dir[X];
	z = child->og[Z] + hit * child->dir[Z];
	if ((x * x) + (z * z) <= 1)
		add_intersection_to_ray(hit, &parent->hit, &parent->closest, cyl);
	hit = (cyl.max - child->og[Y]) / child->dir[Y];
	x = child->og[X] + (hit * child->dir[X]);
	z = child->og[Z] + (hit * child->dir[Z]);
	if ((x * x) + (z * z) <= 1)
		add_intersection_to_ray(hit, &parent->hit, &parent->closest, cyl);
}
