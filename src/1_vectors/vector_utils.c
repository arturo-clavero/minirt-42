/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:21:14 by arturo            #+#    #+#             */
/*   Updated: 2024/05/16 13:57:01 by arturo           ###   ########.fr       */
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

void	copy_t_vec(t_vec *dst, t_vec src)
{
	int	i;

	i = -1;
	while (++i < 4)
		(*dst)[i] = src[i];
}

void	blend_colors(t_vec color1, t_vec color2, t_vec *result)
{
	int	i;

	i = -1;
	while (++i < 4)
		(*result)[i] = color1[i] * color2[i];
	//clear_negative_zeros_t_vec(result);
}

void	clear_negative_zeros_t_vec(t_vec *vec)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if ((*vec)[i] == -0)
		{
			(*vec)[i] = +0;
		}
	}
}

