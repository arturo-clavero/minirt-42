/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:32:02 by arturo            #+#    #+#             */
/*   Updated: 2024/05/27 15:25:20 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	negative_translation(t_mtrx *trans, float x, float y, float z)
{
	t_mtrx	inv;

	translation(trans, x, y, z);
	invert_matrix(*trans, &inv, 4);
	copy_matrix(trans, inv, 4);
}

void	negative_rotation(t_mtrx *rot, float rad, char axis)
{
	rad = (2 * M_PI) - rad;
	rotation(rot, rad, axis);
}

void	negative_scalar(t_mtrx *scl, float x, float y, float z)
{
	t_mtrx	inv;

	scalar(scl, x, y, z);
	invert_matrix(*scl, &inv, 4);
	copy_matrix(scl, inv, 4);
}

//initiates all shearing values to 0
void	init_shear_float(float (*sh)[6])
{
	int	i;

	i = -1;
	while (++i < 5)
		(*sh)[i] = 0;
}

//adds a shearing value, one at a time, to struct sh
void	add_shear_value(char change, char prop_to, int value, float (*sh)[6])
{
	if (change == 'x')
	{
		if (prop_to == 'y')
			(*sh)[0] = value;
		else if (prop_to == 'z')
			(*sh)[1] = value;
	}
	else if (change == 'y')
	{
		if (prop_to == 'x')
			(*sh)[2] = value;
		else if (prop_to == 'z')
			(*sh)[3] = value;
	}
	else if (change == 'z')
	{
		if (prop_to == 'x')
			(*sh)[4] = value;
		else if (prop_to == 'y')
			(*sh)[5] = value;
	}
}
