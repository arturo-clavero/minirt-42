/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:05:40 by arturo            #+#    #+#             */
/*   Updated: 2024/08/04 14:29:14 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "header.h"
# include "parsing.h"

# define MAX_TRANSF 5
# define A 0
# define B 1
# define C 2
# define DISCRIMINANT 3

typedef float	t_mtrx[4][4];

typedef struct s_submtrx
{
	t_mtrx	old;
	t_mtrx	new;
	int		old_mtsize;
	int		excl_x;
	int		excl_y;
	int		sign;
}		t_submtrx;

/*------MATRIX OPERATIONS----------*/
void		matrix_by_matrix(t_mtrx m1, t_mtrx m2, t_mtrx *result, int mt_size);
void		matrix_by_t_vec(t_mtrx m1, t_vec v2, t_vec *result, int mt_size);
void		create_identity_matrix(t_mtrx *matrix, int mt_size);
void		transpose(t_mtrx matrix, t_mtrx *result, int mt_size);
void		sub_matrix(t_submtrx *sub);
t_submtrx	create_submtrx_struct(t_mtrx m, int excl_y, \
int excl_x, int mt_size);
void		copy_matrix(t_mtrx *dst, t_mtrx src, int mt_size);
float		determinant(t_mtrx m, int mt_size);
float		cofactor(t_mtrx m1, int y, int x, int mt_size);
int			invert_matrix(t_mtrx mt, t_mtrx *inv, int mt_size);
int			matrix_comparison(t_mtrx m1, t_mtrx m2, int mt_size);

/*------MATRIX TRANSFORMATIONS----------*/
void		negative_translation(t_mtrx *trans, float x, float y, float z);
void		negative_scalar(t_mtrx *scl, float x, float y, float z);
void		rotation_axis(t_mtrx *rot, float rad, int axis);
void		negative_rotation(t_mtrx *rot, float rad, char axis);
float		to_rad(float deg);
void		shearing(t_mtrx *mt, float shr[6]);
void		init_shear_float(float (*sh)[6]);
void		add_shear_value(char change, char prop_to, \
int value, float (*sh)[6]);
void		chain_transform(t_mtrx mt[MAX_TRANSF], t_mtrx *final, int total);
//void		clear_negative_zeros_mt(t_mtrx	*m);

//debug
void		print_t_matrix(t_mtrx mt);

//important
void		scale(t_elem elem, int *total, t_mtrx (*mt)[MAX_TRANSF]);
void		rotate(int type, t_vec end, int *total, t_mtrx (*mt)[MAX_TRANSF]);
void		translate(t_vec center, int *total, t_mtrx (*mt)[MAX_TRANSF]);

#endif
