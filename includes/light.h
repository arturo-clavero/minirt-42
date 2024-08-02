/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:04:42 by arturo            #+#    #+#             */
/*   Updated: 2024/08/03 05:24:51 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "header.h"

# define AMBIENT 4
# define DIFFUSE 5
# define SPECULAR 6

typedef struct s_mlx	t_mlx;

typedef struct s_light
{
	t_vec	og;
	t_vec	dir;
	t_vec	eye;
	t_vec	point;
	t_vec	normal;
	t_vec	reflect;
	t_vec	color;
	float	ambient;//between 0 and 1
	float	diffuse;//between 0 and 1
	float	specular;//between 0  and 1
	float	shine;//between 10 and 200
	bool	is_shadow;
	bool	has_ambient;
}		t_light;

void	is_point_in_shadow(t_light *light, t_mlx *mlx);
void	calc_light_vectors(t_light *light, t_ray ray, t_intersect *closest);
void	compute_final_color(t_light light, t_obj obj, t_ray *ray);
void	calc_plane_normal(t_light *light, t_intersect *closest);
void	calc_cyl_normal(t_light *light, t_intersect *closest);
void	calc_sph_normal(t_light *light, t_intersect *closest);

#endif