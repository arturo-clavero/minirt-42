/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:20:30 by artclave          #+#    #+#             */
/*   Updated: 2024/08/01 12:20:34 by artclave         ###   ########.fr       */
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
}

void	initialize_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win_size[X] = 1600;
	mlx->win_size[Y] = 900;
	mlx->win = mlx_new_window(mlx->mlx, \
	mlx->win_size[X], mlx->win_size[Y], "miniRT");
	mlx->image.img = mlx_new_image(mlx->mlx, \
	mlx->win_size[X], mlx->win_size[Y]);
	mlx->image.address = mlx_get_data_addr(mlx->image.img, \
	&mlx->image.bits_per_pixel, &mlx->image.line_length, &mlx->image.endian);
	mlx->obj_list = NULL;
	mlx->ray = malloc(sizeof(t_ray));
	init_viewport(mlx);
	init_light(mlx);
}
