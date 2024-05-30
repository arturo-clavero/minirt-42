/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:46:44 by arturo            #+#    #+#             */
/*   Updated: 2024/05/30 12:58:29 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	parsing(t_pars **pars)
{
	add_cam_parsing(pars);
	add_sphere_parsing(pars);
	add_plane_parsing(pars);
	add_cylinder_parsing(pars);
	add_amb_light_parsing(pars);
	add_dif_light_parsing(pars);
	add_spec_light_parsing(pars);
}
