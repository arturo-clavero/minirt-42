/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:40:31 by arturo            #+#    #+#             */
/*   Updated: 2024/05/09 16:52:18 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <limits.h>
# include <unistd.h>

# define X 0
# define Y 1
# define Z 2
# define TYPE 3
# define POINT 1
# define VECTOR 0
# define EPSILON 0.00001

typedef float	t_vec[4];
typedef float	t_mtrx[4][4];

typedef struct s_submtrx
{
	t_mtrx	old;
	t_mtrx	*new;
	int		old_mtsize;
	int		excl_x;
	int		excl_y;
	int		sign;
}		t_submtrx;

/*----BASIC OPERATIONS-----*/
void	create_tupple(t_vec *result, float x, float y, float z);
void	create_vector(t_vec *result, float x, float y, float z);
void	add(t_vec point1, t_vec point2, t_vec *result);
void	substract(t_vec point1, t_vec point2, t_vec *result);
void	scalar_mult(t_vec vec, float scalar, t_vec *result);

/*----VECTOR OPERATIONS-----*/
float	dot_product(t_vec vec1, t_vec vec2);
void	cross_product(t_vec v1, t_vec v2, t_vec *result);
float	inv_magnitude(t_vec vec);
void	normalize(t_vec vec, t_vec *result);
void	negate(t_vec vec, t_vec *result);

/*-----COLOR OPERATIONS-----*/
void	blend_colors(t_vec color1, t_vec color2, t_vec *result);

/*-----BASIC MATH----------------*/
int		float_comparison(float a, float b);

/*------MATRIX OPERATIONS----------*/
void	matrix_by_matrix(t_mtrx m1, t_mtrx m2, t_mtrx *result, int mt_size);
void	matrix_by_tupple(t_mtrx m1, t_vec v2, t_vec *result, int mt_size);
void	create_identity_matrix(t_mtrx *matrix, int mt_size);
void	transpose(t_mtrx matrix, t_mtrx *result, int mt_size);
void	sub_matrix(t_submtrx sub);
void	copy_matrix(t_mtrx *dst, t_mtrx src, int mt_size);
float	determinant(t_mtrx old, int mt_size, float result);
float	cofactor(t_mtrx old, int excl_x, int excl_y, int mt_size);
int		inverting_matrix(t_mtrx matrix, t_mtrx *result, int mt_size);
int		matrix_comparison(t_mtrx m1, t_mtrx m2, int size1, int size2);

/*----------TESTING UTILS----------*/
void	print_matrix(t_mtrx m, int mt_size);

#endif
