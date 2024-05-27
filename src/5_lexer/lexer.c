/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:57:27 by arturo            #+#    #+#             */
/*   Updated: 2024/05/27 22:15:09 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "header.h"

void	add_cam_to_scene(t_elem cam, t_mlx *mlx)
{
	mlx->cam.fov = to_rad(cam.fov_deg);
	mlx->cam.half_window[X] = mlx->win_size[X] / 2;
	mlx->cam.half_window[Y] = mlx->win_size[Y] / 2;
	cam_transform(&mlx->cam, cam.orientation, cam.center);
}

void	add_light_to_scene(t_elem light, t_mlx *mlx)
{
	t_vec	color_range1;

	scalar_mult(light.color_range255, 1 / 255, &color_range1);
	if (light.type == AMBIENT)
	{
		mlx->light->ambient = light.brightness;
		copy_t_vec(&mlx->light->color, color_range1);//CHANGE TO AMB COLOR
	}
	if (light.type == DIFFUSE)
	{
		mlx->light->diffuse = light.brightness;
		//copy_t_vec(&mlx->light->color, color_range1); DIFFUSE COL
	}
	if (light.type == SPECULAR)
	{
		mlx->light->shine = light.brightness;
		//copy_t_vec(&mlx->light->color, color_range1); SPECULAR COL
	}
	copy_t_vec(&mlx->light->og, light.center);
}

void	transform_object(t_elem shape, t_obj *new)
{
	t_mtrx	mt[MAX_TRANSF];
	int		total;

	total = 0;
	if ((shape.center[X] != 0 || shape.center[Y] != 0 || shape.center[Z] != 0) \
	&& ++total > 0)
		translation(&mt[total - 1], shape.center[X], shape.center[Y], \
		shape.center[Z]);
	if (shape.type != PLANE && new->r != 1 && ++total > 0)
		scalar(&mt[total - 1], new->r, new->r, new->r);
	if (shape.type != SPHERE)
		rotate_obj(shape.orientation, &mt, &total);
	new->is_transformed = FALSE;
	if (total > 0)
	{
		new->is_transformed = TRUE;
		chain_transform(mt, &new->mt_trans, total);
		invert_matrix(new->mt_trans, &new->inv_trans, 4);
	}
}

void	add_shape_to_scene(t_elem shape, t_mlx *mlx)
{
	t_objlist	*new;
	t_objlist	*prev;

	new = malloc(sizeof(t_objlist));
	scalar_mult(shape.color_range255, 1 / 255, &new->obj.color);
	if (shape.type == CYLINDER)
	{
		new->obj.max = new->obj.og[Y] + (shape.height / 2);
		new->obj.min = new->obj.max - shape.height;
	}
	if (shape.type == SPHERE || shape.type == CYLINDER)
		new->obj.r = shape.diameter / 2;
	transform_object(shape, &new->obj);
	new->next = NULL;
	if (mlx->obj_list == NULL)
		mlx->obj_list = new;
	else
	{
		prev = mlx->obj_list;
		while (prev->next)
			prev = prev->next;
		prev->next = new;
	}
}

void	lexer(t_pars *pars, t_mlx *mlx)
{
	t_pars	*temp;

	while (pars)
	{
		if (pars->element.type == CAMERA)
			add_cam_to_scene(pars->element, mlx);
		else if (pars->element.type == AMBIENT || pars->element.type == DIFFUSE \
		|| pars->element.type == SPECULAR)
			add_light_to_scene(pars->element, mlx);
		else
			add_shape_to_scene(pars->element, mlx);
		temp = pars;
		pars = pars->next;
		free(temp);
	}
}
