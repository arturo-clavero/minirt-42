/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 02:16:02 by arturo            #+#    #+#             */
/*   Updated: 2024/07/23 16:20:07 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "header.h"

void	init_scene(t_mlx *mlx);
void	init_viewport(t_mlx *mlx);
int		find_intersection(t_ray *parent_ray, t_mlx *mlx);
void	clean(t_mlx *mlx);
void	clean_ray(t_ray *ray);

#endif