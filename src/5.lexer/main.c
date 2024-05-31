/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:38:10 by arturo            #+#    #+#             */
/*   Updated: 2024/05/31 08:29:49 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	lexer(t_mlx *mlx, t_pars *pars)
{
	t_pars	*temp;

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
		temp = pars->next;
		free(pars);
		pars = temp;
	}
}
