/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:12:16 by arturo            #+#    #+#             */
/*   Updated: 2024/05/30 13:15:00 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "header.h"

void	lexer(t_mlx *mlx, t_pars *pars);
void	add_cam_lexer(t_elem element, t_mlx *mlx);
void	add_sph_lexer(t_elem element, t_mlx *mlx);
void	add_pln_lexer(t_elem element, t_mlx *mlx);
void	add_cyl_lexer(t_elem element, t_mlx *mlx);
void	add_light_lexer(t_elem element, t_light	*light);
void	add_obj_to_list(t_obj obj, t_objlist **list);
void	transform_object(t_mtrx mt[MAX_TRANSF], int total, \
t_obj *obj);
void	rotate_object(t_mtrx (*mt)[MAX_TRANSF], int *total_ptr, t_elem elem);
void	lex_transf_obj(t_obj *obj, t_elem e, t_mtrx (*mt)[MAX_TRANSF], \
int *ptr);

#endif