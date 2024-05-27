/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 21:35:06 by arturo            #+#    #+#             */
/*   Updated: 2024/05/27 15:13:14 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

//An indentity matrix is used as a base for transformation matrices
//it has diagonal line of 1s from top left o bottom right and 0s>
//{ {1, 0, 0, 0},
//	{0, 1, 0, 0},
//	{0, 0, 1, 0},
//	{0, 0, 0, 1} }
void	create_identity_matrix(t_mtrx *matrix, int mt_size)
{
	int	i;
	int	j;

	i = -1;
	while (++i < mt_size)
	{
		j = -1;
		while (++j < mt_size)
		{
			if (j == i)
				(*matrix)[i][j] = 1;
			else
				(*matrix)[i][j] = 0;
		}
	}
}

//creates a struct used in the function to create a sub-matrix
t_submtrx	create_submtrx_struct(t_mtrx m, int y, int x, int mt_size)
{
	t_submtrx	sub;

	sub.excl_x = x;
	sub.excl_y = y;
	copy_matrix(&sub.old, m, mt_size);
	sub.old_mtsize = mt_size;
	return (sub);
}

//copies matrix "src" to matrix "dst"
void	copy_matrix(t_mtrx *dst, t_mtrx src, int mt_size)
{
	int	i;
	int	j;

	i = -1;
	while (++i < mt_size)
	{
		j = -1;
		while (++j < mt_size)
			(*dst)[i][j] = src[i][j];
	}
}

//elements -0s are changed to +0s
void	clear_negative_zeros_mt(t_mtrx	*m)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if ((*m)[i][j] == -0)
				(*m)[i][j] = 0;
		}
	}
}
