/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:04:42 by arturo            #+#    #+#             */
/*   Updated: 2024/05/16 14:05:20 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "header.h"

# define SHADE -42
# define AMBIENT 0

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
}		t_light;

void	calc_light_values(t_light	*light, t_obj obj, t_ray *ray);

#endif