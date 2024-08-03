/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:53:05 by arturo            #+#    #+#             */
/*   Updated: 2024/08/03 17:02:54 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "debug.h"

int	intersects_sphere(t_ray *parent_ray, t_ray *child_ray, t_obj sph)
{
	t_vec		sph_to_ray;
	t_vec		quadratic;
	float		hit[2];

	//static int debug = 0;
	substract(child_ray->og, sph.og, &sph_to_ray);
	quadratic[A] = dot_product(child_ray->dir, child_ray->dir);
	quadratic[B] = 2 * (dot_product(child_ray->dir, sph_to_ray));
	quadratic[C] = dot_product(sph_to_ray, sph_to_ray) - 1;
	quadratic[DISCRIMINANT] = (quadratic[B] * quadratic[B]) \
	- (4 * quadratic[A] * quadratic[C]);
/*	if (debug == 0)
	{
		printf("sphere origin: ");
		print_t_vec(sph.og);
		printf("sphere to ray: ");
		print_t_vec(sph_to_ray);
		printf("quadratic: ");
		print_t_vec(quadratic);
		printf("discriminant = %f\n\n", quadratic[DISCRIMINANT]);
	}
	debug++;*/
	if (quadratic[DISCRIMINANT] < 0)
		return (EXIT_FAILURE);
	hit[0] = (-quadratic[B] - (sqrtf(quadratic[DISCRIMINANT]))) \
	/ (2 * quadratic[A]);
	add_intersection_to_ray(hit[0], &parent_ray->hit, &parent_ray->closest, sph);
	hit[1] = (-quadratic[B] + (sqrtf(quadratic[DISCRIMINANT]))) \
	/ (2 * quadratic[A]);
	add_intersection_to_ray(hit[1], &parent_ray->hit, &parent_ray->closest, sph);
	if (hit[0] > 0.01 || hit[1] > 0.01)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

void	intersects_plane(t_ray *parent_ray, t_ray *child_ray, t_obj pl)
{
	float	hit;

	if (fabs(child_ray->dir[Y]) < EPSILON)
		return ;
	hit = -child_ray->og[Y] / child_ray->dir[Y];
	add_intersection_to_ray(hit, &parent_ray->hit, &parent_ray->closest, pl);
}

void	intersects_cylinder_body(t_ray *parent, t_ray *r, t_obj cyl)
{
	t_vec		quad;
	float		hit;
	float		y;

	quad[A] = (r->dir[X] * r->dir[X]) + (r->dir[Z] * r->dir[Z]);
	if (quad[A] < 0.001 && quad[A] > -0.009)
		return ;
	quad[B] = (2 * r->og[X] * r->dir[X]) + (2 * r->og[Z] * r->dir[Z]);
	quad[C] = (r->og[X] * r->og[X]) + (r->og[Z] * r->og[Z]) - 1;
	quad[DISCRIMINANT] = (quad[B] * quad[B]) - (4 * quad[A] * quad[C]);
	if (quad[DISCRIMINANT] < 0.001)
		return ;
	hit = (-quad[B] -(sqrtf(quad[DISCRIMINANT]))) / (2 * quad[A]);
	y = r->og[Y] + hit * r->dir[Y];
	if (y > cyl.min && y < cyl.max)
		add_intersection_to_ray(hit, &parent->hit, &parent->closest, cyl);
	hit = (-quad[B] +(sqrtf(quad[DISCRIMINANT]))) / (2 * quad[A]);
	y = r->og[Y] + hit * r->dir[Y];
	if (y > cyl.min && y < cyl.max)
		add_intersection_to_ray(hit, &parent->hit, &parent->closest, cyl);
}

void	intersects_cylinder_caps(t_ray *parent, t_ray *child, t_obj cyl)
{
	float	hit;
	float	x;
	float	z;

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
