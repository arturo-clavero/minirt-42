/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:04:42 by arturo            #+#    #+#             */
/*   Updated: 2024/05/23 20:26:50 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "header.h"

# define AMBIENT 0
# define DIFFUSE 1
# define SPECULAR 2

typedef struct s_light
{
	t_vec	og;
	t_vec	dir;
	t_vec	eye;
	t_vec	point;
	t_vec	normal;
	t_vec	reflect;
	t_vec	color;
	float	intensity;
	float	ambient;//between 0 and 1
	float	diffuse;//between 0 and 1
	float	specular;//between 0  and 1
	float	shine;//between 10 and 200
	bool	is_shadow;
}		t_light;

void	calc_light_vectors(t_light *light, t_ray ray, t_intersect *closest);
void	compute_final_color(t_light light, t_obj obj, t_ray *ray);

#endif