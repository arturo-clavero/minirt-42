/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:36:04 by arturo            #+#    #+#             */
/*   Updated: 2024/07/21 20:54:17 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	key_press_hook(int keycode, t_mlx *mlx)
{
	if (keycode == 65307) {
		clean(mlx);
		exit(0);
	}
	return (0);
}

int	main(void)
{
	t_mlx	mlx;
	t_pars	*pars;

	initialize_mlx(&mlx);
	pars = NULL;
	parsing(&pars);
	lexer(&mlx, pars);
	init_scene(&mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.image.img, 0, 0);
	mlx_hook(mlx.win, 2, 1, key_press_hook, &mlx);
	mlx_loop(mlx.mlx);
	clean(&mlx);
	return (0);
}
