/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chpt7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:56:29 by arturo            #+#    #+#             */
/*   Updated: 2024/05/21 13:42:08 by arturo           ###   ########.fr       */
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