/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:12:49 by arturo            #+#    #+#             */
/*   Updated: 2024/05/24 11:27:52 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

//Addition of components, x, y, z and w, of 2 vectors
//Watch out! you can NOT add 2 points with this ft
//point + point = INVALID, because -> w(1) + w(1) = w(2) // 2 is nothing!
//point + vector = point, because -> w(1) + w(0) = w(1) // 1 is a point
//vector + vector = vector, because -> w(0) + w(0) = w(0) // 0 is vector)
void	add(t_vec point1, t_vec point2, t_vec *result)
{
	int	i;

	i = -1;
	while (++i < 4)
		(*result)[i] = point1[i] + point2[i];
}

//Substract of components, x, y, z and w, -> point1 minus point2
//Watch out! you can NOT do vector minus point!
//vector - point = INVALID, because ->(w(0) - w(1) = w(-1) // -1 is NOTHING
//point - vector = point, because ->(w(1) - w(0) = w(1) // 1 is a point
//point - point = vector, because ->(w(1) - w(1) = w(0) // 0 is vector
//vector - vector = vector, because ->(w(0) - w(0) = w(0) // 0 is vector)
void	substract(t_vec point1, t_vec point2, t_vec *result)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		(*result)[i] = point1[i] - point2[i];
	}
	(*result)[TYPE] = VECTOR;
}

//Multiply each component of a vector "vec" by a float "scalar"
//Store resulting vector in result
void	scalar_mult(t_vec vec, float scalar, t_vec *result)
{
	int	i;

	i = -1;
	while (++i < 4)
		(*result)[i] = vec[i] * scalar;
}
