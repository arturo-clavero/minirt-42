/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:56:56 by arturo            #+#    #+#             */
/*   Updated: 2024/05/17 18:58:31 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

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

int			intersects_sphere(t_ray *parent_ray, t_ray *child_ray, t_obj sph);

#endif