/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:12:49 by arturo            #+#    #+#             */
/*   Updated: 2024/05/16 21:30:53 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	add(t_vec point1, t_vec point2, t_vec *result)
{
	int	i;

	i = -1;
	while (++i < 4)
		(*result)[i] = point1[i] + point2[i];
	//clear_negative_zeros_t_vec(result);
}

void	substract(t_vec point1, t_vec point2, t_vec *result)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		(*result)[i] = point1[i] - point2[i];
	}
	(*result)[TYPE] = VECTOR;
	//clear_negative_zeros_t_vec(result);
}

void	scalar_mult(t_vec vec, float scalar, t_vec *result)
{
	int	i;

	i = -1;
	while (++i < 4)
		(*result)[i] = vec[i] * scalar;
	//clear_negative_zeros_t_vec(result);
}
