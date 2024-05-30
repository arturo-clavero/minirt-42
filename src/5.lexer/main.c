/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:38:10 by arturo            #+#    #+#             */
/*   Updated: 2024/05/30 13:11:47 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	lexer(t_mlx *mlx, t_pars *pars)
{
	mlx->light->diffuse = 0;
	mlx->light->specular = 0;
	mlx->light->shine = 0;
	while (pars)
	{
		if (pars->element.type == CAMERA)
			add_cam_lexer(pars->element, mlx);
		else if (pars->element.type == SPHERE)
			add_sph_lexer(pars->element, mlx);
		else if (pars->element.type == PLANE)
			add_pln_lexer(pars->element, mlx);
		else if (pars->element.type == CYLINDER)
			add_cyl_lexer(pars->element, mlx);
		else
			add_light_lexer(pars->element, mlx->light);
		pars = pars->next;
	}
}
