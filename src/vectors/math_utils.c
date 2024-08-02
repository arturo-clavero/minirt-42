/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:39:36 by arturo            #+#    #+#             */
/*   Updated: 2024/05/24 11:04:08 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/// @brief Compares if 2 floats are equal using EPSILON (0.00001)
/// @return 0 if equal, 1 if not equal
int	float_comparison(float a, float b)
{
	if (fabs(a - b) < EPSILON)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

/// @brief takes degrees, returns radians (for rotation matrices/ cam fov...)
float	to_rad(float deg)
{
	return ((deg / 180) * M_PI);
}
