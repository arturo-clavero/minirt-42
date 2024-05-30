/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 02:16:02 by arturo            #+#    #+#             */
/*   Updated: 2024/05/29 14:34:42 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "header.h"

void	init_scene(t_mlx *mlx);

//====PARSING====//
void	init_viewport(t_mlx *mlx);
void	new_ray(t_ray *ray, float pixel[2], t_mlx *mlx);
void	new_sphere(t_mlx *mlx, int trans, t_mtrx mt[MAX_TRANSF]);
void	add_obj_to_list(t_obj obj, t_objlist **list);

#endif