/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 01:45:30 by artclave          #+#    #+#             */
/*   Updated: 2024/08/04 01:55:37 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

void	set_up_rotations(t_vec axis, float angle, t_mtrx *result)
{
	t_mtrx	rots[4];
	int		i;

	i = -1;
	while (++i < 3)
	{
		create_identity_matrix(&rots[i], 4);
		if (fabs(axis[i]) != 0 && axis[i] < 0)
			rotation_axis(&rots[i], angle, i);
		if (fabs(axis[i]) != 0 && axis[i] > 0)
			rotation_axis(&rots[i], angle * -1, i);
	}
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
	r = acosf(dot_product(start, end));
	create_identity_matrix(&(*mt)[*total], 4);
	if (fabs(r - M_PI) < EPSILON)
	{
		if (type == CAMERA)
			(*mt)[*total][0][0] = -1;
		else
			(*mt)[*total][1][1] = -1;
		(*mt)[*total][2][2] = -1;
		*total = *total + 1;
		return ;
	}
	set_up_rotations(u, r, &(*mt)[*total]);
	*total = *total + 1;
}
