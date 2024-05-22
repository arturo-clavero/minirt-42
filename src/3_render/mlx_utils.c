/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:51:14 by arturo            #+#    #+#             */
/*   Updated: 2024/05/22 07:19:50 by arturo           ###   ########.fr       */
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

void	initialize_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win_size[X] = 800;
	mlx->win_size[Y] = 400;
	mlx->win = mlx_new_window(mlx->mlx, \
	mlx->win_size[X], mlx->win_size[Y], "TEST");
	mlx->image.img = mlx_new_image(mlx->mlx, \
	mlx->win_size[X], mlx->win_size[Y]);
	mlx->image.address = mlx_get_data_addr(mlx->image.img, \
	&mlx->image.bits_per_pixel, &mlx->image.line_length, &mlx->image.endian);
	mlx->obj_list = NULL;
	mlx->ray = malloc(sizeof(t_ray));
	mlx->light = malloc(sizeof(t_light));
}
