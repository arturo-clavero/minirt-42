/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 08:38:14 by arturo            #+#    #+#             */
/*   Updated: 2024/08/04 06:26:25 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	clean(t_mlx *mlx)
{
	t_objlist	*temp;

	free(mlx->ray);
	free(mlx->light);
	while (mlx->obj_list)
	{
		temp = mlx->obj_list->next;
		free(mlx->obj_list->obj);
		free (mlx->obj_list);
		mlx->obj_list = temp;
	}
}
