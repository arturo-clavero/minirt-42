/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:12:16 by arturo            #+#    #+#             */
/*   Updated: 2024/08/02 23:37:17 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "header.h"

void	lexer(t_mlx *mlx, t_pars *pars);
void	add_cam_lexer(t_elem element, t_mlx *mlx);
void	add_light_lexer(t_elem element, t_light	*light);
void	add_obj_to_list(t_obj obj, t_objlist **list);
void	add_obj_lexer(t_elem element, t_mlx *mlx);

#endif