/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:12:49 by arturo            #+#    #+#             */
/*   Updated: 2024/05/08 19:14:36 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	create_tupple(t_vec *result, float x, float y, float z)
{
	(*result)[0] = x;
	(*result)[1] = y;
	(*result)[2] = z;
	(*result)[TYPE] = POINT;
}

void	create_vector(t_vec *result, float x, float y, float z)
{
	(*result)[0] = x;
	(*result)[1] = y;
	(*result)[2] = z;
	(*result)[TYPE] = VECTOR;
}

void	add(t_vec point1, t_vec point2, t_vec *result)
{
	int	i;

	i = -1;
	while (++i < 4)
		(*result)[i] = point1[i] + point2[i];
}

void	substract(t_vec point1, t_vec point2, t_vec *result)
{
	int	i;

	i = -1;
	while (++i < 4)
		(*result)[i] = point1[i] - point2[i];
}

void	scalar_mult(t_vec vec, float scalar, t_vec *result)
{
	int	i;

	i = -1;
	while (++i < 4)
		(*result)[i] = vec[i] * scalar;
}
