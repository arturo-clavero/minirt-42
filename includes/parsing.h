/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:11:41 by arturo            #+#    #+#             */
/*   Updated: 2024/05/30 12:07:51 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "header.h"

# define CAMERA 0

typedef struct s_elem
{
	int		type;
	t_vec	orientation;
	t_vec	center;
	t_vec	color_range255;
	float	brightness;
	float	shine;
	float	fov_in_deg;
	float	diameter;
	float	height;
}		t_elem;

typedef struct s_pars
{
	t_elem			element;
	struct s_pars	*next;
}		t_pars;

void	parsing(t_pars **pars);
void	add_element_to_pars_list(t_elem elem, t_pars **pars);
void	lex_transf_obj(t_obj *obj, t_elem e, t_mtrx (*mt)[MAX_TRANSF], int *tot_ptr);
void	lexer(t_mlx *mlx, t_pars *pars);
void	rotate_object(t_mtrx (*mt)[MAX_TRANSF], int *total_ptr, t_elem elem);

#endif
