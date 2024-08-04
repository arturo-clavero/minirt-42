/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:20:30 by artclave          #+#    #+#             */
/*   Updated: 2024/08/04 14:24:18 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_mlx_pixel_put(t_data *data, int x, int y, t_vec color)
{
	char			*dst;
	unsigned int	packed_rgb;
	int				i;

	dst = data->address + (y * data->line_length
			+ x * (data->bits_per_pixel / 8));
	i = -1;
	while (++i < 3)
	{
		if (color[i] < 0)
			color[i] = 0;
		else if (color[i] > 1)
			color[i] = 1;
	}
	packed_rgb = (((int)(color[0] * 255)) << 16) \
	| (((int)(color[1] * 255)) << 8) | (int)(color[2] * 255);
	*(unsigned int *)dst = packed_rgb;
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

void	init_light(t_mlx *mlx)
{
	mlx->light = malloc(sizeof(t_light));
	mlx->light->diffuse = 0;
	mlx->light->specular = 0;
	mlx->light->shine = 0;
	mlx->light->exists = FALSE;
	mlx->light->has_ambient = FALSE;
	mlx->light->has_diffuse = FALSE;
	mlx->light->ambient = 0;
}

void	initialize_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win_size[X] = 1600;
	mlx->win_size[Y] = 900;
	mlx->win = mlx_new_window(mlx->mlx, \
	mlx->win_size[X], mlx->win_size[Y], "miniRT");
	mlx->obj_list = NULL;
	mlx->cam.exists = FALSE;
	mlx->is_selected = FALSE;
	mlx->ray = malloc(sizeof(t_ray));
	mlx->mouse_ray = malloc(sizeof(t_ray));
	init_viewport(mlx);
	init_light(mlx);
}
