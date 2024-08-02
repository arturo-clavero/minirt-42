/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:55:45 by arturo            #+#    #+#             */
/*   Updated: 2024/07/22 02:59:48 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include "header.h"

typedef struct s_data
{
	void	*img;
	char	*address;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_data;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	float		win_size[2];
	float		vp_size[2];
	float		vp_min[2];
	float		vp_wall;
	float		pixel_size;
	t_data		image;
	t_objlist	*obj_list;
	t_ray		*ray;
	t_light		*light;
	t_camera	cam;
}		t_mlx;

void	ft_mlx_pixel_put(t_data *data, int x, int y, t_vec color);
void	initialize_mlx(t_mlx *mlx);
int		key_press_hook(int keycode, t_mlx *mlx);
int		x_button(t_mlx *mlx);

#endif