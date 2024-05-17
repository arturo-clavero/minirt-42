/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:11:07 by arturo            #+#    #+#             */
/*   Updated: 2024/05/17 12:17:47 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "header.h"

# define SPHERE 1

typedef struct s_ray t_ray;

typedef struct s_obj
{
	int		type;
	float	r;
	t_vec	og;
	t_mtrx	mt_trans;
	t_mtrx	inv_trans;
	t_vec	color;
	t_ray	*ray;
	bool	is_transformed;
}		t_obj;

typedef struct s_dlist
{
	t_obj			obj;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}	t_objlist;

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
	t_vec		target;
	t_vec		color;
	t_intersect	*closest;
	t_intersect	*hit;
}		t_ray;

/*------------INTERSECT SPHERE------*/
void		init_ray(t_ray *ray);
void		point_at_distance(float distance, t_ray *ray, t_vec *point);
void		add_intersection_to_ray(float d, t_intersect **hit, \
t_intersect **closest, t_obj sph);
int			intersects_sphere(t_ray *parent_ray, t_ray *child_ray, t_obj sph);
void		transform_object(t_mtrx mt[MAX_TRANSF], int total, \
t_obj *obj);
void		transform_ray(t_ray *parent, t_ray *child, t_obj obj);
void		copy_ray(t_ray *dst, t_ray *src);

#endif