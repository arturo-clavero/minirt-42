/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:16:28 by arturo            #+#    #+#             */
/*   Updated: 2024/08/02 20:06:05 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
/// @brief
// Combines 2 vectors together into a float number that measures
// how "similar" 2 vectors are
// Bonus use> 
//		1)magnitude (or length) of a vector
//		 = fsqrt(dot_product(vector1, vector1));
float	dot_product(t_vec vec1, t_vec vec2)
{
	float	result;
	int		i;

	result = 0;
	i = -1;
	while (++i < 3)
	{
		result += vec1[i] * vec2[i];
	}
	if (result == -0)
		result = 0;
	return (result);
}

/// @brief stores the cross product of v1 x v2 in result vector
/// result vector will be perpendicular to both v1 and v2
// Bonus use>
//		1) calculate the angle between two vectors, 
//		2) determine a vector normal to a plane,
void	cross_product(t_vec v1, t_vec v2, t_vec *result)
{
	(*result)[X] = (v1[Y] * v2[Z]) - (v1[Z] * v2[Y]);
	(*result)[Y] = (v1[Z] * v2[X]) - (v1[X] * v2[Z]);
	(*result)[Z] = (v1[X] * v2[Y]) - (v1[Y] * v2[X]);
	(*result)[TYPE] = VECTOR;
}

/// @brief Normalizes vec and stores it in result
/// A normalized vector is a vector that has a magnitude (or length) of 1
void	normalize(t_vec vec, t_vec *result)
{
	float	mag;
	int		i;

	i = -1;
	mag = 0;
	while (++i < 3)
		mag += vec[i] * vec[i];
	mag = sqrtf(mag);
	i = -1;
	while (++i < 3)
		(*result)[i] = vec[i] / mag;
	(*result)[3] = vec[3];
}

/// @brief Result will have opposite direction to vec, 
//but same magnitude (or length)
//Example> if vec->direction = (1, -2, 3), 
//then result->direction = (-1, 2, -3);
void	negate(t_vec vec, t_vec *result)
{
	int		i;
	t_vec	zero;

	i = -1;
	while (++i < 4)
		zero[i] = 0;
	i = -1;
	while (++i < 4)
		(*result)[i] = zero[i] - vec[i];
}

bool	are_vecs_colinear(t_vec v1, t_vec v2)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (v1[i] != v2[i])
			return (FALSE);
	}
	return (TRUE);
}
