/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 20:31:56 by arturo            #+#    #+#             */
/*   Updated: 2024/05/08 21:29:25 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	matrix_by_matrix(t_mtrx m1, t_mtrx m2, t_mtrx *result, int mt_size)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (++i < mt_size)
	{
		j = -1;
		while (++j < mt_size)
		{
			(*result)[i][j] = 0;
			k = -1;
			while (++k < mt_size)
				(*result)[i][j] += m1[i][k] * m2[j][k];
		}
	}
}

void	matrix_by_tupple(t_mtrx m1, t_vec v2, t_vec *result, int mt_size)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (++i < mt_size)
	{
		(*result)[i] = 0;
		k = -1;
		while (++k < mt_size)
			(*result)[i] += m1[i][k] * v2[i];
	}
}

void	create_identity_matrix(t_mtrx *matrix, int mt_size)
{
	int i;
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

void	sub_matrix(int i, t_mtrx old, t_mtrx *new, int mt_size)
{
	int j = -1;
	while ()
}

//always send result as 0 first call 
float	determinant(t_mtrx old, int mt_size, float result)
{
	t_mtrx	new;
	int		i;

	if (mt_size < 3)
		return (EXIT_FAILURE);
	while (++i < mt_size)
	{
		sub_matrix(i, old, &new, mt_size);
		if (mt_size > 3)
			result += determinant(new, mt_size - 1, result);
		else
			result += (((new[0][0] * new[1][1]) - \
			(new[0][1] * new[1][0])) * old[0][i]);
	}
	return (result);
}

int	inverting_matrix(t_mtrx matrix, t_mtrx *result, int mt_size)
{
	float	det;
	int		i;
	int		j;

	det = determinant(matrix, mt_size);//TODO
	if (det == 0)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < mt_size)
	{
		j = -1;
		while (++j < mt_size)
			(*result)[i][j] = co_factor(matrix, j, i, mt_size) / det;
	}
	return (EXIT_SUCCESS);
}
