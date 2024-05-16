/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:39:36 by arturo            #+#    #+#             */
/*   Updated: 2024/05/13 22:41:45 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


int	float_comparison(float a, float b)
{
	if (fabs(a - b) < EPSILON)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

float	to_rad(float deg)
{
	return ((deg / 180) * M_PI);
}
