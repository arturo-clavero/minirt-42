/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:21:42 by artclave          #+#    #+#             */
/*   Updated: 2024/08/04 14:28:21 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	key_press_hook(int keycode, t_mlx *mlx)
{
	if (keycode == 65307)
	{
		clean(mlx);
		exit(0);
	}
	return (0);
}

int	x_button(t_mlx *mlx)
{
	clean(mlx);
	exit(0);
}

int	click_obj(int button, int x, int y, t_mlx *mlx)
{
	float	pos[2];

	if (button == 1 && mlx->is_selected == FALSE)
	{
		pos[X] = x;
		pos[Y] = y;
		new_parent_ray(mlx->cam, mlx->mouse_ray, pos);
		if (find_intersection(mlx->mouse_ray, mlx) != -1)
		{
			mlx->is_selected = TRUE;
			mlx->start[X] = pos[X];
			mlx->start[Y] = pos[Y];
		}
	}
	else if (button == 1 && mlx->is_selected == TRUE)
	{
		mlx->is_selected = FALSE;
		clean_ray(mlx->mouse_ray);
	}
	return (0);
}

int	check_mouse_rotations(int keycode, t_mlx *mlx)
{
	t_mtrx	rot;
	t_mtrx	temp;

	if (keycode == 120)
		rotation_axis(&rot, 0.785398, X);
	else if (keycode == 121)
		rotation_axis(&rot, 0.785398, Y);
	else if (keycode == 122)
		rotation_axis(&rot, 0.785398, Z);
	else
		return (0);
	matrix_by_matrix(mlx->mouse_ray->closest->object->mt_trans, rot, &temp, 4);
	copy_matrix(&mlx->mouse_ray->closest->object->mt_trans, temp, 4);
	invert_matrix(mlx->mouse_ray->closest->object->mt_trans, \
	&mlx->mouse_ray->closest->object->inv_trans, 4);
	mlx_destroy_image(mlx->mlx, mlx->image.img);
	init_scene(mlx);
	return (0);
}

int	key_event(int keycode, t_mlx *mlx)
{
	if (mlx->is_selected == FALSE)
		return (0);
	if (keycode == KEY_LEFT)
		mlx->mouse_ray->closest->object->mt_trans[0][3] -= 1;
	else if (keycode == KEY_UP)
		mlx->mouse_ray->closest->object->mt_trans[1][3] += 1;
	else if (keycode == KEY_RIGHT)
		mlx->mouse_ray->closest->object->mt_trans[0][3] += 1;
	else if (keycode == KEY_DOWN)
		mlx->mouse_ray->closest->object->mt_trans[1][3] -= 1;
	else if (keycode == 47)
		mlx->mouse_ray->closest->object->mt_trans[2][3] -= 1;
	else if (keycode == 65506)
		mlx->mouse_ray->closest->object->mt_trans[2][3] += 1;
	else
		return (check_mouse_rotations(keycode, mlx));
	invert_matrix(mlx->mouse_ray->closest->object->mt_trans, \
	&mlx->mouse_ray->closest->object->inv_trans, 4);
	mlx_destroy_image(mlx->mlx, mlx->image.img);
	init_scene(mlx);
	return (0);
}
