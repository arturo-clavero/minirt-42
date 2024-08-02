/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 21:39:15 by arturo            #+#    #+#             */
/*   Updated: 2024/05/27 15:01:35 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

//creates a matrix deleting row index sub->excl_x, and column index sub->excl_y
//from original matrix sub->old
//the new sub-matrix will be stored in sub->new
void	sub_matrix(t_submtrx *sub)
{
	int	old_x;
	int	old_y;
	int	new_x;
	int	new_y;

	new_y = -1;
	old_y = -1;
	while (++old_y < sub->old_mtsize && new_y + 1 < sub->old_mtsize - 1)
	{
		new_x = -1;
		if (old_y == sub->excl_y)
			continue ;
		new_y++;
		old_x = -1;
		while (++old_x < sub->old_mtsize && new_x + 1 < sub->old_mtsize - 1)
		{
			if (old_x == sub->excl_x)
				continue ;
			sub->new[new_y][++new_x] = sub->old[old_y][old_x];
		}
	}
	sub->sign = 1;
	if ((sub->excl_x + sub->excl_y) % 2 != 0)
		sub->sign = -1;
}

//calculates the "cofactor" of each row along a fixed column (y = 0) of a matrix
//then multiplies each cofactor with its corresponding element. 
//The sum of the products obtained by the operations == the determinant.
//Unless the matrix is 2x2, then the determinant is calculated like so>
//top left by bottom right elements - the top right by the bottom left elements.
//The determinant is needed to calculate the inverse of a matrix
float	determinant(t_mtrx m, int mt_size)
{
	int		x;
	int		y;
	float	sum;

	if (mt_size == 2)
		return ((m[0][0] * m[1][1]) - (m[0][1] * m[1][0]));
	sum = 0;
	y = 0;
	x = -1;
	while (++x < mt_size)
		sum += (cofactor(m, y, x, mt_size) * m[y][x]);
	if (sum == -0)
		sum = 0;
	return (sum);
}

//Eliminates row 'x' and column 'y' of a matrix
//calculates the determinant of the modified matrix
float	cofactor(t_mtrx m1, int y, int x, int mt_size)
{
	t_submtrx	sub;
	t_mtrx		m2;
	float		minor;
	int			sign;

	sub = create_submtrx_struct(m1, y, x, mt_size);
	sub_matrix(&sub);
	mt_size--;
	copy_matrix(&m2, sub.new, mt_size);
	minor = determinant(m2, mt_size);
	sign = 1;
	if ((y + x) % 2 != 0 && minor != 0)
		sign = -1;
	return (minor * sign);
}

//Inverted matrices are used to transform rays 
//	by the opposite transformation of an object.
//If we want to move an object by an x of +2
//	we instead transform the ray by x of -2,
//	as all intersection fts expect objects in a default position and scale
int	invert_matrix(t_mtrx mt, t_mtrx *inv, int mt_size)
{
	float	det;
	int		x;
	int		y;

	det = determinant(mt, mt_size);
	if (det == 0)
		return (EXIT_FAILURE);
	y = -1;
	while (++y < mt_size)
	{
		x = -1;
		while (++x < mt_size)
			(*inv)[y][x] = cofactor(mt, x, y, mt_size) / det;
	}
	return (EXIT_SUCCESS);
}
