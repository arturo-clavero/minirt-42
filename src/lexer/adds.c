/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:55:29 by arturo            #+#    #+#             */
/*   Updated: 2024/08/04 05:56:34 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	add_cam_lexer(t_elem element, t_mlx *mlx)
{
	static int	added = 0;

	if (added == 1)
		return ;
	cam_transform(&mlx->cam, element.orientation, element.center);
	mlx->cam.half_window[X] = mlx->win_size[X];
	mlx->cam.half_window[Y] = mlx->win_size[Y];
	mlx->cam.fov = to_rad(element.fov_in_deg);
	calc_pixel_size(&mlx->cam);
	mlx->cam.exists = TRUE;
	added = 1;
}

void	add_obj_lexer(t_elem element, t_mlx *mlx)
{
	t_mtrx	mt[MAX_TRANSF];
	int		total;
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	obj->type = element.type;
	obj->r = 1;
	if (element.type == CYLINDER)
	{
		element.height /= (element.diameter / 2);
		obj->max = element.height / 2.0f;
		obj->min = obj->max * -1.0f;
	}
	create_tupple(&obj->og, 0, 0, 0);
	scalar_mult(element.color_range255, (1.0f / 255.0f), &obj->color);
	total = 0;
	scale(element, &total, &mt);
	if (obj->type != SPHERE)
		rotate(obj->type, element.orientation, &total, &mt);
	translate(element.center, &total, &mt);
	create_identity_matrix(&obj->mt_trans, 4);
	chain_transform(mt, &obj->mt_trans, total);
	invert_matrix(obj->mt_trans, &obj->inv_trans, 4);
	add_obj_to_list(obj, &mlx->obj_list);
}

void	add_light_lexer(t_elem element, t_light *light)
{
	static int	added[3];

	if (added[element.type - 4] == 1)
		return ;
	if (element.type == AMBIENT)
	{
		scalar_mult(element.color_range255, (1.0f / 255.0f), &light->color);
		light->ambient = element.brightness;
		added[0] = 1;
		light->has_ambient = TRUE;
		light->exists = TRUE;
	}
	else if (element.type == DIFFUSE)
	{
		copy_t_vec(&light->og, element.center);
		light->diffuse = element.brightness;
		added[1] = 1;
		light->has_diffuse = TRUE;
		light->exists = TRUE;
	}
}
