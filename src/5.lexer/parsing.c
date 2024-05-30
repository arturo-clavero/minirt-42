/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:46:44 by arturo            #+#    #+#             */
/*   Updated: 2024/05/30 12:12:26 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	add_cam_parsing(t_pars **pars)
{
	t_elem	elem;
	float	len;

	elem.type = CAMERA;
	create_tupple(&elem.center, 0, 0, -10);
	create_vector(&elem.orientation, 0, 0, 1);
	len = sqrtf(dot_product(elem.orientation, elem.orientation));
	if (len > 1 + EPSILON || len < 1 - EPSILON)
	{
		printf("cam orientation not normalised (%f)\n", len);
		exit(2);
	}
	elem.fov_in_deg = 90;
	add_element_to_pars_list(elem, pars);
}

void	add_cylinder_parsing(t_pars **pars)
{
	t_elem	elem;

	elem.type = CYLINDER;
	create_tupple(&elem.center, 0, 0, 0);
	create_vector(&elem.orientation, 0, 0, 1);
	elem.diameter = 2;
	elem.height = 2;
	create_vector(&elem.color_range255, 0, 255, 0);
	add_element_to_pars_list(elem, pars);
}

void	add_sphere_parsing(t_pars **pars)
{
	t_elem	elem;

	elem.type = SPHERE;
	create_tupple(&elem.center, 2, 0, 0);
	elem.diameter = 5;
	create_vector(&elem.color_range255, 0, 0, 255);
	add_element_to_pars_list(elem, pars);
}

void	add_plane_parsing(t_pars **pars)
{
	t_elem	elem;
	float	len;

	elem.type = PLANE;
	create_tupple(&elem.center, 0, 0, -20);
	create_vector(&elem.orientation, 0, 0, 1);
	len = sqrtf(dot_product(elem.orientation, elem.orientation));
	if (len > 1 + EPSILON || len < 1 - EPSILON)
	{
		printf("plane orientation not normalised (%f)\n", len);
		exit(2);
	}
	create_vector(&elem.color_range255, 255, 255, 255);
	add_element_to_pars_list(elem, pars);
}

void	add_amb_light_parsing(t_pars **pars)
{
	t_elem	elem;

	elem.type = AMBIENT;
	elem.brightness = 0.2;
	create_tupple(&elem.color_range255, 255, 255, 255);
	add_element_to_pars_list(elem, pars);
}

void	add_dif_light_parsing(t_pars **pars)
{
	t_elem	elem;

	elem.type = DIFFUSE;
	elem.brightness = 1;
	create_tupple(&elem.center, -1, 0, -5);
	add_element_to_pars_list(elem, pars);
}

void	add_spec_light_parsing(t_pars **pars)
{
	t_elem	elem;

	elem.type = SPECULAR;
	elem.brightness = 1;
	elem.shine = 200;
	add_element_to_pars_list(elem, pars);
}

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
