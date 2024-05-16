/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 21:35:06 by arturo            #+#    #+#             */
/*   Updated: 2024/05/15 19:10:34 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

t_submtrx	create_submtrx_struct(t_mtrx m, int y, int x, int mt_size)
{
	t_submtrx	sub;

	sub.excl_x = x;
	sub.excl_y = y;
	copy_matrix(&sub.old, m, mt_size);
	sub.old_mtsize = mt_size;
	return (sub);
}

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

int	matrix_comparison(t_mtrx m1, t_mtrx m2, int mt_size)
{
	int	i;
	int	j;

	i = -1;
	while (++i < mt_size)
	{
		j = -1;
		while (++j < mt_size)
		{
			if (float_comparison(m1[i][j], m2[i][j]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

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
