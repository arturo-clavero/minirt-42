/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tranform.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 21:46:38 by arturo            #+#    #+#             */
/*   Updated: 2024/08/03 17:01:40 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	scale(t_elem elem, int *total, t_mtrx (*mt)[MAX_TRANSF])
{
	if (elem.type == PLANE || elem.diameter == 2)
		return ;
	//printf("elem diameter  is : %f\n", elem.diameter);
	create_identity_matrix(&(*mt)[*total], 4);
	(*mt)[*total][0][0] = elem.diameter / 2.f;
	(*mt)[*total][1][1] = elem.diameter / 2.f;
	(*mt)[*total][2][2] = elem.diameter / 2.f;
	//printf("scale, mt[%d]:\n", *total);
	//print_t_matrix((*mt)[*total]);
	*total = *total + 1;
}

void	set_up_rotations(t_vec axis, float angle, t_mtrx *result)
{
	t_mtrx	rots[4];
	int		i;


	i = -1;
	while (++i < 3)
	{
		create_identity_matrix(&rots[i], 4);
	//	if (i == X)
	//	{
			if (fabs(axis[i]) != 0 && axis[i] < 0)
				rotation_axis(&rots[i], angle, i);
			if (fabs(axis[i]) != 0 && axis[i] > 0)
				rotation_axis(&rots[i], angle * -1, i);
	/*	}
		else
		{
			if (fabs(axis[i]) != 0 && axis[i] < 0)
				rotation_axis(&rots[i], angle * -1, i);
			if (fabs(axis[i]) != 0 && axis[i] > 0)
				rotation_axis(&rots[i], angle, i);
		}*/
		
	}
	/*printf("\nso rotations are: \n");
	print_t_matrix(rots[0]);
	print_t_matrix(rots[1]);
	print_t_matrix(rots[2]);
	printf("\nrots 0 by rots1 is\n");
	print_t_matrix(rots[3]);
		
	printf("\nresult by rots2 is \n");
	print_t_matrix(*result);*/
	matrix_by_matrix(rots[0], rots[1], &rots[3], 4);
	matrix_by_matrix(rots[3], rots[2], result, 4);
}

void	rotate(int type, t_vec end, int *total, t_mtrx (*mt)[MAX_TRANSF])
{
	float	r;
	t_vec	u;
	t_vec	start;

	create_vector(&start, 0, 1, 0);
	if (type == CAMERA)
		create_vector(&start, 0, 0, 1);
	if (are_vecs_colinear(start, end) == TRUE)
		return ;
	cross_product(start, end, &u);
	normalize(u, &u);
	//printf("start is: ");
	//print_t_vec(start);
	//printf("end is: ");
	//print_t_vec(end);
	//printf("axis is: ");
	//print_t_vec(u);
	r = acosf(dot_product(start, end));
	//printf("angle is %f\n", r);
	create_identity_matrix(&(*mt)[*total], 4);
	if (fabs(r - M_PI) < EPSILON) 
	{ // Check for 180-degree rotation
	//rotation for (0,0,1) to (0,0,-1)
		(*mt)[*total][0][0] = -1;
		(*mt)[*total][2][2] = -1;
		//printf("rotation, mt[%d]:\n", *total);
		//print_t_matrix((*mt)[*total]);
		*total = *total + 1;
        return;
    }
	set_up_rotations(u, r, &(*mt)[*total]);
	//printf("rotation, mt[%d]:\n", *total);
	//print_t_matrix((*mt)[*total]);
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
	//printf("translation, mt[%d]:\n", *total);
	//print_t_matrix((*mt)[*total]);
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
		////printf("chain transform: \n");
		//print_t_matrix(*final);
		return ;

	}
	i = total;
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
	//printf("chain transform: \n");
	//print_t_matrix(*final);

}

void	rotation_axis(t_mtrx *rot, float rad, int axis)
{
	create_identity_matrix(rot, 4);
	if (axis == X)
	{
		(*rot)[1][1] = cos(rad);
		(*rot)[2][2] = (*rot)[1][1];
		(*rot)[2][1] = sin(rad);
		(*rot)[1][2] = -sin(rad);
	}
	if (axis == Y)
	{
		(*rot)[0][0] = cos(rad);
		(*rot)[2][2] = (*rot)[0][0];
		(*rot)[2][0] = -sin(rad);
		(*rot)[0][2] = sin(rad);
	}
	if (axis == Z)
	{
		(*rot)[0][0] = cos(rad);
		(*rot)[1][1] = (*rot)[0][0];
		(*rot)[1][0] = sin(rad);
		(*rot)[0][1] = -sin(rad);
	}
}
