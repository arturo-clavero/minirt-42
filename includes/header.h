/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:40:31 by arturo            #+#    #+#             */
/*   Updated: 2024/05/27 22:23:55 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <limits.h>
# include <unistd.h>
# include <stdbool.h>

# include "vector.h"
# include "matrix.h"
# include "mlx.h"
# include "mlx_utils.h"
# include "parsing.h"
//delete debug!
# include "debug.h"

# define TRUE 1
# define FALSE 0
//	LIGHT DEFINES>
# define AMBIENT 0
# define DIFFUSE 1
# define SPECULAR 2
//	SHAPES
# define SPHERE 1
# define PLANE 2
# define CYLINDER 3

typedef struct s_obj
{
	int		type;
	float	r;
	t_vec	og;
	t_mtrx	mt_trans;
	t_mtrx	inv_trans;
	t_vec	color;
	float	min;
	float	max;
	bool	is_transformed;
}		t_obj;

typedef struct s_dlist
{
	t_obj			obj;
	struct s_dlist	*next;
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
	t_vec		color;
	t_intersect	*closest;
	t_intersect	*hit;
}		t_ray;

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

typedef struct s_pars	t_pars;

//MAIN>
void	parsing(t_pars **pars);
void	lexer(t_pars *pars, t_mlx *mlx);
void	init_scene(t_mlx *mlx);
//CAMERA>
void	new_parent_ray(t_camera cam, t_ray *ray, float pixel[2]);
void	calc_pixel_size(t_camera *cam);
void	cam_transform(t_camera *cam, t_vec orientation, t_vec og);
//LIGHT>
void	calc_sph_normal(t_light *light, t_intersect *closest);
void	calc_cyl_normal(t_light *light, t_intersect *closest);
void	calc_plane_normal(t_light *light, t_intersect *closest);
void	calc_light_vectors(t_light *light, t_ray ray, t_intersect *closest);
void	is_point_in_shadow(t_light *light, t_mlx *mlx);
void	compute_final_color(t_light light, t_obj obj, t_ray *ray);
//RAY>
void	new_parent_ray(t_camera cam, t_ray *ray, float pixel[2]);
void	add_intersection_to_ray(float d, t_intersect **hit, \
t_intersect **closest, t_obj sph);
void	transform_ray(t_ray *parent, t_ray *child, t_obj obj);
void	rotate_obj(t_vec orientation, t_mtrx (*mt)[MAX_TRANSF], int *total_ptr);
void	copy_ray(t_ray *dst, t_ray *src);
void	clean_ray(t_ray *ray);
//INTERSECT
int		intersects_sphere(t_ray *parent_ray, t_ray *child_ray, t_obj sph);
void	intersects_plane(t_ray *parent_ray, t_ray *child_ray, t_obj pl);
void	intersects_cylinder_body(t_ray *parent, t_ray *child, t_obj cyl);
void	intersects_cylinder_caps(t_ray *parent, t_ray *child, t_obj cyl);
void	add_intersection_to_ray(float d, t_intersect **hit, \
t_intersect **closest, t_obj sph);
int		find_intersection(t_ray *parent_ray, t_mlx *mlx);


#endif
