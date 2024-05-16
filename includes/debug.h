/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:09:28 by arturo            #+#    #+#             */
/*   Updated: 2024/05/15 21:04:46 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

#include "header.h"

void		print_matrix(t_mtrx m, int mt_size);
void		print_t_vec(t_vec vec);
void		print_shear(float sh[6]);
void		print_intersections(t_ray *ray);
void		print_ray(t_ray *ray);

#endif