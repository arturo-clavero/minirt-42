/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:38:10 by arturo            #+#    #+#             */
/*   Updated: 2024/05/30 12:07:34 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	add_cam_lexer(t_elem element, t_mlx *mlx)
{
	cam_transform(&mlx->cam, element.orientation, element.center);
	mlx->cam.half_window[X] = mlx->win_size[X];
	mlx->cam.half_window[Y] = mlx->win_size[Y];
	mlx->cam.fov = to_rad(element.fov_in_deg);
	calc_pixel_size(&mlx->cam);
}

void	add_sph_lexer(t_elem element, t_mlx *mlx)
{
	t_obj	sph;
	t_mtrx	mt[MAX_TRANSF];
	int		total;

	sph.type = SPHERE;
	create_tupple(&sph.og, 0, 0, 0);
	sph.r = 1;
	scalar_mult(element.color_range255, (1.0f / 255.0f), &sph.color);
	total = -1;
	lex_transf_obj(&sph, element, &mt, &total);
	if (++total > 0)
		transform_object(mt, total, &sph);
	add_obj_to_list(sph, &mlx->obj_list);
}

void	add_pln_lexer(t_elem element, t_mlx *mlx)
{
	t_obj	pl;
	int		total;
	t_mtrx	mt[MAX_TRANSF];

	pl.type = PLANE;
	create_tupple(&pl.og, 0, 0, 0);
	scalar_mult(element.color_range255, (1.0f / 255.0f), &pl.color);
	total = -1;
	lex_transf_obj(&pl, element, &mt, &total);
	rotate_object(&mt, &total, element);
	if (++total > 0)
		transform_object(mt, total, &pl);
	add_obj_to_list(pl, &mlx->obj_list);
}

void	add_cyl_lexer(t_elem element, t_mlx *mlx)
{
	t_obj	cyl;
	int		total;
	t_mtrx	mt[MAX_TRANSF];

	cyl.type = CYLINDER;
	create_tupple(&cyl.og, 0, 0, 0);
	cyl.r = 1;
	cyl.max = element.height / 2.0f;
	cyl.min = cyl.max * -1.0f;
	scalar_mult(element.color_range255, (1.0f / 255.0f), &cyl.color);
	total = -1;
	lex_transf_obj(&cyl, element, &mt, &total);
	rotate_object(&mt, &total, element);
	if (++total > 0)
		transform_object(mt, total, &cyl);
	add_obj_to_list(cyl, &mlx->obj_list);
}

void	add_light_lexer(t_elem element, t_light	*light)
{
	if (element.type == AMBIENT)
	{
		scalar_mult(element.color_range255, (1.0f / 255.0f), &light->color);
		light->ambient = element.brightness;
	}
	else if (element.type == DIFFUSE)
	{
		copy_t_vec(&light->og, element.center);
		light->diffuse = element.brightness;
	}
	else if (element.type == SPECULAR)
	{
		light->specular = element.brightness;
		light->shine = element.shine;
	}
}

void	lexer(t_mlx *mlx, t_pars *pars)
{
	while (pars)
	{
		if (pars->element.type == CAMERA)
			add_cam_lexer(pars->element, mlx);
		else if (pars->element.type == SPHERE)
			add_sph_lexer(pars->element, mlx);
		else if (pars->element.type == PLANE)
			add_pln_lexer(pars->element, mlx);
		else if (pars->element.type == CYLINDER)
			add_cyl_lexer(pars->element, mlx);
		else
			add_light_lexer(pars->element, mlx->light);
		pars = pars->next;
	}
}
