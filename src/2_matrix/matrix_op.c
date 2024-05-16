/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 20:31:56 by arturo            #+#    #+#             */
/*   Updated: 2024/05/15 19:17:15 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	matrix_by_matrix(t_mtrx m1, t_mtrx m2, t_mtrx *result, int mt_size)
{
	int	r;
	int	c;
	int	i;

	r = -1;
	while (++r < mt_size)
	{
		c = -1;
		while (++c < mt_size)
		{
			(*result)[r][c] = 0;
			i = -1;
			while (++i < mt_size)
				(*result)[r][c] += (m1[r][i] * m2[i][c]);
		}
	}
	//clear_negative_zeros_mt(result);
}

void	matrix_by_t_vec(t_mtrx m1, t_vec v2, t_vec *result, int mt_size)
{
	int	r;
	int	c;

	r = -1;
	while (++r < mt_size)
	{
		(*result)[r] = 0;
		c = -1;
		while (++c < mt_size)
			(*result)[r] += (m1[r][c] * v2[c]);
	}
	//clear_negative_zeros_t_vec(result);
}

void	transpose(t_mtrx matrix, t_mtrx *result, int mt_size)
{
	int	i;
	int	j;

	i = -1;
	while (++i < mt_size)
	{
		j = -1;
		while (++j < mt_size)
			(*result)[i][j] = matrix[j][i];
	}
	//clear_negative_zeros_mt(result);
}
