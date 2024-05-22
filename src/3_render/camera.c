/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:03:19 by arturo            #+#    #+#             */
/*   Updated: 2024/05/22 12:22:14 by arturo           ###   ########.fr       */
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
	cam->pixel_size = ((cam->half_canvas[X] * 2) / cam->half_window[X]) / 2;
}

void	new_parent_ray(t_camera cam, t_ray *ray, float pixel[2])
{
	float	offset[2];
	t_vec	target;
	t_vec	temp;

	ray->hit = NULL;
	ray->closest = NULL;
	offset[X] = (pixel[X] + 0.5) * cam.pixel_size;
	offset[Y] = (pixel[Y] + 0.5) * cam.pixel_size;
	target[X] = -cam.half_canvas[X] + offset[X];
	target[Y] = cam.half_canvas[Y] - offset[Y];
	target[Z] = cam.og[Z] + 1;
	copy_t_vec(&ray->og, cam.og);
	substract(target, ray->og, &ray->dir);
	//printf("ray dir before> \n");
	//print_t_vec(ray->dir);
	if (cam.default_orient == FALSE)
	{
		matrix_by_t_vec(cam.inv_trans, ray->dir, &temp, 4);
		copy_t_vec(&ray->dir, temp);
		//printf("ray dir after>\n");
		//print_t_vec(ray->dir);
	}
	normalize(ray->dir, &ray->dir);
	/*if ((pixel[X] == 0 && pixel[Y] == 0) || (pixel[X] == cam.half_window[X] && pixel[Y] == cam.half_window[Y])
		|| (pixel[X] == cam.half_window[X] * 2 - 1 && pixel[Y] == cam.half_window[Y] * 2 - 1))
	{
		printf("target> for ( %.2f, %.2f)\n", pixel[X], pixel[Y]);
		print_t_vec(target);
		printf(" og>");
		print_t_vec(ray->og);
		printf("dir>");
		print_t_vec(ray->dir);
		printf("\n");
	}*/
}

void	cam_transform(t_camera *cam, t_vec orientation)
{
	int		total;
	t_vec	rot;
	t_vec	def;
	t_mtrx	mt[MAX_TRANSF];
	float	rad;

	cam->default_orient = TRUE;
	if (orientation[X] == 0 && orientation[Y] == 0 && orientation[Z] == 1)
		return ;
	cam->default_orient = FALSE;
	total = 0;
	create_vector(&def, 0, 0, 1);
	cross_product(orientation, def, &rot);
	if (rot[Z] == 0 && rot[Y] == 0 && rot[X] == 0 && ++total > 0)
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
	chain_transform(mt, &cam->mt_trans, total);
	invert_matrix(cam->mt_trans, &cam->inv_trans, 4);
}

/*
int	main(void)
{
	t_camera	cam;
	float		pixel[2];
	t_ray		ray;
*/
	//MY TEST
	/*
	cam.half_window[X] = 800;
	cam.half_window[Y] = 400;
	cam.fov = M_PI / 2;
	cam.default_orient = TRUE;
	create_tupple(&cam.og, 0, 0, 0);
	calc_pixel_size(&cam);
	printf("half size> %.2f , %.2f\n", cam.half_canvas[X], cam.half_canvas[Y]);
	printf("pixel size> %.2f\n", cam.pixel_size);
	pixel[X] = 0;
	pixel[Y] = 0;
	new_parent_ray(cam, &ray, pixel);
	printf("og  >");
	print_t_vec(ray.og);
	printf("dir >");
	print_t_vec(ray.dir);
	printf("\n");
	pixel[X] = 399;
	pixel[Y] = 199;
	new_parent_ray(cam, &ray, pixel);
	printf("og  >");
	print_t_vec(ray.og);
	printf("dir >");
	print_t_vec(ray.dir);
	printf("\n");
	pixel[X] = 799;
	pixel[Y] = 399;
	new_parent_ray(cam, &ray, pixel);
	printf("og  >");
	print_t_vec(ray.og);
	printf("dir >");
	print_t_vec(ray.dir);
	printf("\n");
	*/
	//TEST 2
	/*
	cam.half_window[X] = 201;
	cam.half_window[Y] = 101;
	cam.fov = M_PI / 2;
	cam.default_orient = TRUE;
	create_tupple(&cam.og, 0, 0, 0);
	calc_pixel_size(&cam);
	printf("pixel size> %.2f\n", cam.pixel_size);
	pixel[X] = 0;
	pixel[Y] = 0;
	new_parent_ray(cam, &ray, pixel);
	print_t_vec(ray.og);
	print_t_vec(ray.dir);*/
	//TEST 3

/*	t_mtrx	mt[MAX_TRANSF];
	t_mtrx	mt_trans;

	translation(&mt[0], 0, -2, 5);
	rotation(&mt[1], M_PI / 4, 'y');
	chain_transform(mt, &mt_trans, 2);
	copy_matrix(&cam.mt_trans, mt_trans, 4);
	invert_matrix(cam.mt_trans, &cam.inv_trans, 4);*/
	/*t_vec from, to, up;

	create_tupple(&cam.og, 0, 0, -5);
	copy_t_vec(&from, cam.og);
	create_tupple(&to, 0, 0, 0);
	create_vector(&up, .5, .5, 0);
	//view_transformation(from, to, up, &cam.mt_trans);
	cam_transform(&cam, up);
	cam.half_window[X] = 201;
	cam.half_window[Y] = 101;
	cam.fov = M_PI / 2;
	calc_pixel_size(&cam);
	printf("pixel size> %.2f\n", cam.pixel_size);
	pixel[X] = 100;
	pixel[Y] = 50;
	new_parent_ray(cam, &ray, pixel);
	//printf("\n\nRESULT>\n");
	//print_matrix(cam.mt_trans, 4);
	//print_matrix(cam.inv_trans, 4);
	print_t_vec(ray.og);
	print_t_vec(ray.dir);
}*/
/*
void	new_ray_test(t_camera cam, t_ray *ray, float pixel[2])
{
	t_vec	target;
	t_vec	temp;

	ray->hit = NULL;
	ray->closest = NULL;
	//print_t_vec(cam.og);
	copy_t_vec(&ray->og, cam.og);
	target[X] = -cam.half_canvas[X] + (cam.pixel_size * pixel[X]);
	target[Y] = cam.half_canvas[Y] - (cam.pixel_size * pixel[Y]);
	target[Z] = 10;
	target[TYPE] = POINT;
	//printf("dir before:");
	substract(target, ray->og, &ray->dir);
	normalize(ray->dir, &ray->dir);
	//print_t_vec(ray->dir);
	if (cam.default_orient == FALSE)
	{
		matrix_by_t_vec(cam.mt_trans, ray->dir, &temp, 4);
		copy_t_vec(&ray->dir, temp);
	}
	//printf("dir after: ");
	clear_negative_zeros_t_vec(&ray->dir);
	//print_t_vec(ray->dir);
	//print_t_vec(ray->og);
	//printf("\n");
}

int	main(void)
{
	t_camera	cam;
	t_ray		ray;
	float		pixel[2];
	t_vec		or;

	cam.half_window[X] = 400 / 2;
	cam.half_window[Y] = 400 / 2;
	cam.fov = M_PI / 2;
	create_tupple(&cam.og, 0, 0, -5);
	calc_pixel_size(&cam);
	printf("pixel size> %f, viewport[%.2f, %.2f]\n", cam.pixel_size, cam.half_canvas[X] * 2, cam.half_canvas[Y] * 2);
	create_vector(&or, 0, 0, -1);
	cam_transform(&cam, or);
	pixel[X] = 100;
	pixel[Y] = 100;
	new_ray_test(cam, &ray, pixel);
	print_t_vec(ray.dir);
}*/