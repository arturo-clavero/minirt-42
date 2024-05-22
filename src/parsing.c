/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:46:44 by arturo            #+#    #+#             */
/*   Updated: 2024/05/22 12:23:39 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	transform_object(t_mtrx mt[MAX_TRANSF], int total, \
t_obj *obj)
{
	t_mtrx	temp_mt;
	t_mtrx	new_trans;

	chain_transform(mt, &new_trans, total);
	if (obj->is_transformed == TRUE)
	{
		matrix_by_matrix(new_trans, obj->mt_trans, &temp_mt, 4);
		copy_matrix(&new_trans, temp_mt, 4);
	}
	copy_matrix(&obj->mt_trans, new_trans, 4);
	obj->is_transformed = TRUE;
	invert_matrix(obj->mt_trans, &obj->inv_trans, 4);
}

void	add_obj_to_list(t_obj obj, t_objlist **list)
{
	t_objlist	*new;
	t_objlist	*prev;

	new = malloc(sizeof(t_objlist));
	if (!new)
		return ;
	new->obj = obj;
	new->next = NULL;
	new->prev = NULL;
	if (*list == NULL)
		*list = new;
	else
	{
		prev = *list;
		while (prev->next)
			prev = prev->next;
		new->prev = prev;
		prev->next = new;
	}
}

void	init_viewport(t_mlx *mlx)
{
	mlx->vp_size[X] = 80;
	mlx->vp_size[Y] = 80;
	mlx->vp_min[X] = -mlx->vp_size[X] / 2;
	mlx->vp_min[Y] = mlx->vp_size[Y] / 2;
	mlx->vp_wall = 10;
	mlx->pixel_size = mlx->vp_size[X] / mlx->win_size[X];
}

void	new_light(t_light *light)
{
	create_tupple(&light->og, 0, 5, -10);
	create_vector(&light->color, 1, 1, 1);
	light->ambient = 0.2;
	light->specular = 1;
	light->diffuse = 1;
	light->shine = 200;
}

void	new_sphere(t_mlx *mlx, int trans, t_mtrx mt[MAX_TRANSF])
{
	t_obj		sph;

	sph.type = SPHERE;
	create_tupple(&sph.og, 0, 0, 0);
	sph.r = 1;
	sph.is_transformed = FALSE;
	sph.ray = malloc(sizeof(t_ray));
	create_vector(&sph.color, 0, 0, 1);
	if (trans > 0)
	{
		transform_object(mt, trans, &sph);
	}
	add_obj_to_list(sph, &mlx->obj_list);
}
/*
void	new_camera(t_camera *cam, t_vec og, t_vec ornt, t_mlx *mlx)
{
	t_vec	temp;

	cam->fov = M_PI / 2;
	cam->half_window[X] = mlx->win_size[X] / 2;
	cam->half_window[Y] = mlx->win_size[Y] / 2;
	copy_t_vec(&cam->og, og);
	copy_t_vec(&cam->from, cam->og);
	copy_t_vec(&cam->to, ornt);
	create_vector(&cam->up, 0, 1, 0);
	if (ornt[Y] != 0)
		create_vector(&cam->up, 0, 0, 1);
	if (ornt[X] == 0 && ornt[Y] == 0 && ornt[Z] == 1)
	{
		cam->default_orient = TRUE;
		return ;
	}
	cam->default_orient = FALSE;
	view_transformation(cam->from, cam->to, cam->up, &cam->mt_trans);
	invert_matrix(cam->mt_trans, &cam->inv_trans, 4);
	matrix_by_t_vec(cam->inv_trans, cam->og, &temp, 4);
	copy_t_vec(&cam->og, temp);
}*/

void	parsing(t_mlx *mlx)
{
	t_camera	cam;
	t_vec		or;
	t_mtrx		mt[MAX_TRANSF];

	init_viewport(mlx);
	create_tupple(&cam.og, 0, 0, -5);
	create_vector(&or, 0, 1, 0);
	cam_transform(&cam, or);
	cam.half_window[X] = mlx->win_size[X] / 2;
	cam.half_window[Y] = mlx->win_size[Y] / 2;;
	cam.fov = M_PI / 2;
	calc_pixel_size(&cam);
	mlx->cam = cam;
	//new_sphere(mlx, 0, mt);
	translation(&mt[0], 0, 5, -5);
	new_sphere(mlx, 1, mt);
	//scalar(&mt1[0], 2, 2, 2);
	//new_sphere(mlx, 2, mt);
	new_light(mlx->light);
	//init_viewport(mlx);
}
