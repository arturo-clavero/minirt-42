/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chpt7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:56:29 by arturo            #+#    #+#             */
/*   Updated: 2024/05/22 12:58:56 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


//VIEW TRANSFORAMTION TEST
/*
int	main(void)
{
	t_vec	up;
	t_vec	from;
	t_vec	to;
	t_mtrx	trans;
	t_mtrx	compare;
	//TEST 4
	
	create_tupple(&from, 1, 3, 2);
	create_tupple(&to, 4, -2, 8);
	create_vector(&up, 1, 1, 0);
	view_transformation(from, to, up, &trans);
	create_identity_matrix(&compare, 4);
	printf("result should be 1> %d\n", matrix_comparison(trans, compare, 4));
	print_matrix(trans, 4);
	print_matrix(compare, 4);
	//TEST 2
	//TEST1
	create_tupple(&from, 0, 0, 0);
	create_tupple(&to, 0, 0, -1);
	create_vector(&up, 0, 1, 0);
	view_transformation(from, to, up, &trans);
	create_identity_matrix(&compare, 4);
	printf("result should be 1> %d\n", matrix_comparison(trans, compare, 4));
	print_matrix(trans, 4);
	print_matrix(compare, 4);
	//TEST2
	create_tupple(&from, 0, 0, 0);
	create_tupple(&to, 0, 0, 1);
	create_vector(&up, 0, 1, 0);
	view_transformation(from, to, up, &trans);
	scalar(&compare, -1, 1, -1);
	printf("result should be 1> %d\n", matrix_comparison(trans, compare, 4));
	print_matrix(trans, 4);
	print_matrix(compare, 4);
	//TEST 3
	create_tupple(&from, 0, 0, 8);
	create_tupple(&to, 0, 0, 0);
	create_vector(&up, 0, 1, 0);
	view_transformation(from, to, up, &trans);
	translation(&compare, 0, 0, -8);
	printf("result should be 1> %d\n", matrix_comparison(trans, compare, 4));
	print_matrix(trans, 4);
	print_matrix(compare, 4);
}
*/

//PIXEL SIZE TEST
/*
int	main(void)
{
	t_camera	cam;

	//TEST 1
	cam.half_window[X] = 200;
	cam.half_window[Y] = 125;
	cam.fov = M_PI / 2;
	calc_pixel_size(&cam);
	printf("pixel size> %.2f\n", cam.pixel_size);
	//TEST 2
	cam.half_window[X] = 125;
	cam.half_window[Y] = 200;
	cam.fov = M_PI / 2;
	calc_pixel_size(&cam);
	printf("pixel size> %.2f\n", cam.pixel_size);
}
*/

//CAMERA FINAL TESTS

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