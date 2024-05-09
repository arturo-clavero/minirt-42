/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 20:31:56 by arturo            #+#    #+#             */
/*   Updated: 2024/05/09 17:24:02 by artclave         ###   ########.fr       */
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

void	sub_matrix(t_submtrx sub)
{
	int	old_x;
	int	old_y;
	int	new_x;
	int	new_y;

	new_y = 0;
	new_x = -1;
	old_y = -1;
	while (++old_y < sub.old_mtsize)
	{
		if (old_y == sub.excl_y)
			continue ;
		old_x = -1;
		while (++old_x < sub.old_mtsize && ++new_x > 0)
		{
			if (old_x == sub.excl_x && --new_x >= 0)
				continue ;
			(*sub.new)[new_y][new_x] = sub.old[old_y][old_x];
			if (new_x >= (sub.old_mtsize - 1) && ++new_y > 0)
				new_x = 0;
		}
	}
	sub.sign = 1;
	if ((sub.excl_x + sub.excl_y) % 2 != 0)
		sub.sign = -1;
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

//always send result as 0 first call 
float	determinant(t_mtrx old, int mt_size, float result)
{
	t_submtrx	sub;
	t_mtrx		new;
	int			i;

	if (mt_size < 3)
		return (EXIT_FAILURE);
	i = -1;
	copy_matrix(&sub.old, old, mt_size);
	sub.excl_y = 0;
	sub.new = &new;
	sub.old_mtsize = mt_size;
	while (++i < mt_size)
	{
		sub.excl_x = i;
		sub_matrix(sub);
		if (mt_size > 3)
			result += determinant(new, mt_size - 1, result);
		else
			result += (((new[0][0] * new[1][1]) - \
			(new[0][1] * new[1][0])) * old[0][i] * ((i % 2) / (i % 2) * -1));
	}
	return (result);
}

float	cofactor(t_mtrx old, int excl_x, int excl_y, int mt_size)
{
	t_submtrx	sub;
	t_mtrx		new;
	int			sign;

	if (mt_size < 3)
		return (EXIT_FAILURE);
	copy_matrix(&sub.old, old, mt_size);
	sub.new = &new;
	sub.excl_x = excl_x;
	sub.excl_y = excl_y;
	sub.old_mtsize = mt_size;
	sub_matrix(sub);
	if (mt_size > 3)
		return (determinant(*sub.new, mt_size - 1, 0));
	return (((*sub.new)[0][0] * (*sub.new)[1][1]) - \
	((*sub.new)[0][1] * (*sub.new)[1][0]) * sub.sign);
}

int	inverting_matrix(t_mtrx matrix, t_mtrx *result, int mt_size)
{
	float	det;
	int		i;
	int		j;

	det = determinant(matrix, mt_size, 0);
	if (det == 0)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < mt_size)
	{
		j = -1;
		while (++j < mt_size)
			(*result)[i][j] = cofactor(matrix, j, i, mt_size) / det;
	}
	return (EXIT_SUCCESS);
}

int	float_comparison(float a, float b)
{
	if (fabs(a - b) < EPSILON)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

void	print_matrix(t_mtrx m, int mt_size)
{
	int	i;
	int	j;

	i = -1;
	while (++i < mt_size)
	{
		j = -1;
		while (++j < mt_size)
		{
			printf("%.2f ", m[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int	matrix_comparison(t_mtrx m1, t_mtrx m2, int size1, int size2)
{
	int	i;
	int	j;

	if (size1 != size2)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < size1)
	{
		j = -1;
		while (++j < size1)
		{
			if (float_comparison(m1[i][j], m2[i][j]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
