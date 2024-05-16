/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:56:58 by arturo            #+#    #+#             */
/*   Updated: 2024/05/16 12:40:41 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "header.h"

# define X 0
# define Y 1
# define Z 2
# define TYPE 3
# define POINT 1
# define VECTOR 0
# define EPSILON 0.00001

typedef float	t_vec[4];

int			float_comparison(float a, float b);
void		create_tupple(t_vec *result, float x, float y, float z);
void		create_vector(t_vec *result, float x, float y, float z);
void		add(t_vec point1, t_vec point2, t_vec *result);
void		substract(t_vec point1, t_vec point2, t_vec *result);
void		scalar_mult(t_vec vec, float scalar, t_vec *result);
void		copy_t_vec(t_vec *dst, t_vec src);
float		dot_product(t_vec vec1, t_vec vec2);
void		cross_product(t_vec v1, t_vec v2, t_vec *result);
float		inv_magnitude(t_vec vec);
void		normalize(t_vec vec, t_vec *result);
void		negate(t_vec vec, t_vec *result);
void		blend_colors(t_vec color1, t_vec color2, t_vec *result);
void		clear_negative_zeros_t_vec(t_vec *vec);

#endif
