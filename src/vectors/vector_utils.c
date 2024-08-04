/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:21:14 by arturo            #+#    #+#             */
/*   Updated: 2024/08/04 14:16:57 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

//Creates a tupple or a point -> (x, y, z, 1);
//assigns a w value of 1, to differentiate points from vectors
//we need this w value to perform operations
//a point or a tupple is like a static position with 3d coordinates
void	create_tupple(t_vec *result, float x, float y, float z)
{
	(*result)[0] = x;
	(*result)[1] = y;
	(*result)[2] = z;
	(*result)[TYPE] = POINT;
}

//Creates a vector -> (x, y, z, 0);
//assigns a w value of 0, to differentiate points from vectors
//we need this w value to perform operations
//a vector implies a movement with directions in x y and z axis
void	create_vector(t_vec *result, float x, float y, float z)
{
	(*result)[0] = x;
	(*result)[1] = y;
	(*result)[2] = z;
	(*result)[TYPE] = VECTOR;
}

//copies a vector or a point in src (source vector) to dst (destination vector)
void	copy_t_vec(t_vec *dst, t_vec src)
{
	int	i;

	i = -1;
	while (++i < 4)
		(*dst)[i] = src[i];
}

//we store colors as vectors with w value of 0,
// x, y, z values represent R, G, B floats, between 0 and 1 
//(0 is dark/min intensity, 1 is very bright or max intensity)
//We can mix color1 and color2 and store the final color in result
void	blend_colors(t_vec color1, t_vec color2, t_vec *result)
{
	int	i;

	i = -1;
	while (++i < 4)
		(*result)[i] = color1[i] * color2[i];
}
