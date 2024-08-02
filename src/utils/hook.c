/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:21:42 by artclave          #+#    #+#             */
/*   Updated: 2024/07/23 14:46:14 by uolle            ###   ########.fr       */
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
