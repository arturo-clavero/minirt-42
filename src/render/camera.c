/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:03:19 by arturo            #+#    #+#             */
/*   Updated: 2024/08/03 04:01:42 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

void	cam_transform(t_camera *cam, t_vec orientation, t_vec center)
{
	int		total;
	t_mtrx	mt[MAX_TRANSF];

	total = 0;
	create_identity_matrix(&cam->mt_trans, 4);
	center[X] *= -1;
	center[Y] *= -1;
	center[Z] *= -1;
	translate(center, &total, &mt);
	rotate(CAMERA, orientation, &total, &mt);
	chain_transform(mt, &cam->mt_trans, total);
	invert_matrix(cam->mt_trans, &cam->inv_trans, 4);
	printf("CAMERA\n--------------------\n");
	print_t_matrix(cam->inv_trans);
}
