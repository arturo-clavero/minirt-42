/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:38:10 by arturo            #+#    #+#             */
/*   Updated: 2024/08/03 05:25:59 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	lexer(t_mlx *mlx, t_pars *pars)
{
	t_pars	*temp;

	mlx->light->has_ambient = FALSE;
	create_vector(&mlx->light->color, 1, 1, 1);
	while (pars)
	{
		if (pars->element.type == CAMERA)
			add_cam_lexer(pars->element, mlx);
		else if (pars->element.type == SPHERE || \
		pars->element.type == CYLINDER || pars->element.type == PLANE)
			add_obj_lexer(pars->element, mlx);
		else
			add_light_lexer(pars->element, mlx->light);
		temp = pars->next;
		free(pars);
		pars = temp;
	}
}
