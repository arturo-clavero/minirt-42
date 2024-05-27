/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 20:31:56 by arturo            #+#    #+#             */
/*   Updated: 2024/05/27 15:09:17 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

//used for chaining transformations
//a translation matrix1 of z +2 and a rotation matrix2 of M_PI / 2 in x-axis
//is the same as matrix2 * matrix1
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
}

//used to transform a vector (v1) by a transformation matrix (m1)
//transformed vector stored in "result"
void	matrix_by_t_vec(t_mtrx m1, t_vec v1, t_vec *result, int mt_size)
{
	int	r;
	int	c;

	r = -1;
	while (++r < mt_size)
	{
		(*result)[r] = 0;
		c = -1;
		while (++c < mt_size)
			(*result)[r] += (m1[r][c] * v1[c]);
	}
}

//flipped version of a matrix
//	The transpose of an orthogonal matrix (i.e rotation matrix)
// == its inverted matrix 
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
}
