/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 21:46:38 by arturo            #+#    #+#             */
/*   Updated: 2024/08/04 01:54:48 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	scale(t_elem elem, int *total, t_mtrx (*mt)[MAX_TRANSF])
{
	if (elem.type == PLANE || elem.diameter == 2)
		return ;
	create_identity_matrix(&(*mt)[*total], 4);
	(*mt)[*total][0][0] = elem.diameter / 2.f;
	(*mt)[*total][1][1] = elem.diameter / 2.f;
	(*mt)[*total][2][2] = elem.diameter / 2.f;
	*total = *total + 1;
}

void	translate(t_vec center, int *total, t_mtrx (*mt)[MAX_TRANSF])
{
	if (center[X] == 0 && center[Y] == 0 && center[Z] == 0)
		return ;
	create_identity_matrix(&(*mt)[*total], 4);
	(*mt)[*total][0][3] = center[X];
	(*mt)[*total][1][3] = center[Y];
	(*mt)[*total][2][3] = center[Z];
	*total = *total + 1;
}

void	chain_transform(t_mtrx mt[MAX_TRANSF], t_mtrx *final, int total)
{
	int		i;
	t_mtrx	result;
	t_mtrx	temp_m;

	if (total < 1)
		return ;
	if (total == 1)
	{
		copy_matrix(final, mt[0], 4);
		return ;
	}
	i = total;
	while (--i >= 0 && total > 1)
	{
		if (i == total - 1 && --i >= 0)
			matrix_by_matrix(mt[i + 1], mt[i], &result, 4);
		else
		{
			matrix_by_matrix(result, mt[i], &temp_m, 4);
			copy_matrix(&result, temp_m, 4);
		}
	}
	copy_matrix(final, result, 4);
}
