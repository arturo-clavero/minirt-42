/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:11:07 by arturo            #+#    #+#             */
/*   Updated: 2024/05/21 08:40:21 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "header.h"

typedef struct s_intersect
{
	float				dist;
	t_obj				object;
	struct s_intersect	*next;
}		t_intersect;

typedef struct s_ray
{
	t_vec		og;
	t_vec		dir;
	t_vec		color;
	t_intersect	*closest;
	t_intersect	*hit;
}		t_ray;

void		add_intersection_to_ray(float d, t_intersect **hit, \
t_intersect **closest, t_obj sph);
void		transform_object(t_mtrx mt[MAX_TRANSF], int total, \
t_obj *obj);
void		transform_ray(t_ray *parent, t_ray *child, t_obj obj);
void		copy_ray(t_ray *dst, t_ray *src);

#endif