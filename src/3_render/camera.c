/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:03:19 by arturo            #+#    #+#             */
/*   Updated: 2024/05/27 15:26:33 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	multiply_by_negative_from(t_mtrx *transf, t_vec from)
{
	t_mtrx	temp;
	t_mtrx	transl;
	t_vec	neg_from;

	create_tupple(&neg_from, -from[X], -from[Y], -from[Z]);
	clear_negative_zeros_t_vec(&neg_from);
	translation(&transl, neg_from[X], neg_from[Y], neg_from[Z]);
	print_matrix(transl, 4);
	print_matrix(*transf, 4);
	matrix_by_matrix(*transf, transl, &temp, 4);
	copy_matrix(transf, temp, 4);
}

void	view_transformation(t_vec from, t_vec to, t_vec up, t_mtrx *trans)
{
	t_vec	forward;
	t_vec	left;
	t_vec	true_up;
	t_vec	up_n;

	substract(to, from, &forward);
	normalize(forward, &forward);
	normalize(up, &up_n);
	cross_product(forward, up_n, &left);
	cross_product(left, forward, &true_up);
	copy_t_vec(&(*trans)[0], left);
	copy_t_vec(&(*trans)[1], true_up);
	create_vector(&(*trans)[2], -forward[X], -forward[Y], -forward[Z]);
	clear_negative_zeros_t_vec(&(*trans)[2]);
	create_tupple(&(*trans)[3], 0, 0, 0);
	multiply_by_negative_from(trans, from);
}

void	calc_pixel_size(t_camera *cam)
{
	float	half_view;
	float	aspect_ratio;

	if (cam->fov > M_PI - 0.01)
		cam->fov -= 0.01;
	half_view = tan(cam->fov / 2);
	aspect_ratio = cam->half_window[X] / cam->half_window[Y];
	if (aspect_ratio >= 1)
	{
		cam->half_canvas[X] = half_view;
		cam->half_canvas[Y] = half_view / aspect_ratio;
	}
	else
	{
		cam->half_canvas[X] = half_view * aspect_ratio;
		cam->half_canvas[Y] = half_view;
	}
	cam->pixel_size = ((cam->half_canvas[X] * 2) / cam->half_window[X]);
}

void	cam_transform(t_camera *cam, t_vec orientation, t_vec og)
{
	int		total;
	t_vec	rot;
	t_vec	def;
	t_mtrx	mt[MAX_TRANSF];
	float	rad;

	total = 0;
	cam->default_orient = TRUE;
	if ((og[X] != 0 || og[Y] != 0 || og[Z] != 0) && ++total > 0)
	{
		cam->default_orient = FALSE;
		translation(&mt[total - 1], -og[X], -og[Y], -og[Z]);
	}
	if (!(orientation[X] == 0 && orientation[Y] == 0 && orientation[Z] == 1))
		cam->default_orient = FALSE;
	if (cam->default_orient == TRUE)
		return ;
	create_vector(&def, 0, 0, 1);
	cross_product(orientation, def, &rot);
	if (rot[Z] == 0 && rot[Y] == 0 && rot[X] == 0 && orientation[Z] == -1 && ++total > 0)
	{
		rad = M_PI;
		rotation(&mt[total - 1], rad, 'y'); //x or y axis rotation work here as long as its 180 also negative 180 is same as pos 180
	}
	if (rot[Y] != 0 && ++total > 0)
	{
		rad = rot[Y] * M_PI / 2;
		if (rad < 0)
			rad += (2 * M_PI);
		rotation(&mt[total - 1], rad, 'y');
	}
	if (rot[X] != 0 && ++total > 0)
	{
		rad = rot[X] * M_PI / 2;
		if (rad < 0)
			rad += (2 * M_PI);
		rotation(&mt[total - 1], rad, 'x');
	}
	if (cam->default_orient == TRUE)
		return ;
	chain_transform(mt, &cam->mt_trans, total);
	invert_matrix(cam->mt_trans, &cam->inv_trans, 4);
}
