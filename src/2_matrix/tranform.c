/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tranform.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 21:46:38 by arturo            #+#    #+#             */
/*   Updated: 2024/05/27 15:24:27 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

//creates transformation matrix to "move" a vector in the x y and z direction 
void	translation(t_mtrx *trans, float x, float y, float z)
{
	create_identity_matrix(trans, 4);
	(*trans)[0][3] = x;
	(*trans)[1][3] = y;
	(*trans)[2][3] = z;
}

//creates a transformation matrix that makes a vector bigger or smaller 
//in x y and z direction 
//value of 0.5 would be half the size, 1 is the same size, 2 is double the size
void	scalar(t_mtrx *scl, float x, float y, float z)
{
	create_identity_matrix(scl, 4);
	(*scl)[0][0] = x;
	(*scl)[1][1] = y;
	(*scl)[2][2] = z;
}

//rotates the matrix by radians "rad", in the specified axis ('x' or 'y' or 'z')
void	rotation(t_mtrx *rot, float rad, char axis)
{
	create_identity_matrix(rot, 4);
	if (axis == 'x')
	{
		(*rot)[1][1] = cos(rad);
		(*rot)[2][2] = (*rot)[1][1];
		(*rot)[2][1] = sin(rad);
		(*rot)[1][2] = -sin(rad);
	}
	if (axis == 'y')
	{
		(*rot)[0][0] = cos(rad);
		(*rot)[2][2] = (*rot)[0][0];
		(*rot)[2][0] = -sin(rad);
		(*rot)[0][2] = sin(rad);
	}
	if (axis == 'z')
	{
		(*rot)[0][0] = cos(rad);
		(*rot)[1][1] = (*rot)[0][0];
		(*rot)[1][0] = sin(rad);
		(*rot)[0][1] = -sin(rad);
	}
}

//"slants" a vector in a specific direction using these values>
//shr[0] == slanting "x-axis" relative to the "y-axis"
//shr[1] == slanting "x-axis" relative to the "z-axis"
//shr[2] == slanting "y-axis" relative to the "x-axis"
//shr[3] == slanting "y-axis" relative to the "z-axis"
//shr[4] == slanting "z-axis" relative to the "x-axis"
//shr[5] == slanting "z-axis" relative to the "y-axis"
void	shearing(t_mtrx *mt, float shr[6])
{
	int		s;
	int		x;
	int		y;

	create_identity_matrix(mt, 4);
	s = 0;
	y = -1;
	while (++y < 3)
	{
		x = -1;
		while (++x < 3)
		{
			if (x == y)
				continue ;
			(*mt)[y][x] = shr[s];
			s++;
		}
	}
}

//creates one transformation matrix representing multiple transformations
//chain transfromations are multiplied in reverse order
// chain of (rotation + translation + scaling)
// = (scaling * translation * rotation)
void	chain_transform(t_mtrx mt[MAX_TRANSF], t_mtrx *final, int total)
{
	int		i;
	t_mtrx	result;
	t_mtrx	temp_m;

	i = total;
	if (total == 1)
		copy_matrix(&result, mt[0], 4);
	while (--i >= 0 && total > 1)
	{
		if (i == total - 1)
		{
			matrix_by_matrix(mt[i], mt[i - 1], &result, 4);
			i--;
		}
		else
		{
			matrix_by_matrix(result, mt[i], &temp_m, 4);
			copy_matrix(&result, temp_m, 4);
		}
	}
	copy_matrix(final, result, 4);
}
